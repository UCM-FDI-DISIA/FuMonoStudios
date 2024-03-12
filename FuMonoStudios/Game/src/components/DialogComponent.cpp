#include "DialogComponent.h"
#include "../architecture/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/Font.h"
#include "../sdlutils/Texture.h"
#include "Dialog_Manager.h"
#include "Transform.h"
#include "Render.h"

DialogComponent::DialogComponent(DialogManager* manager): mTr_(nullptr), mRend_(nullptr),
	dialogueWidth_(sdlutils().width() - 335),dialogueIndex_(1),mTexture_(nullptr)
{
	mDialogMngr_ = manager;
	mFont_ = new Font("recursos/fonts/ARIAL.ttf", 40);
}

DialogComponent::~DialogComponent()
{
	delete mFont_;
}

void DialogComponent::initComponent()
{
	mTr_ = ent_->getComponent<Transform>();
	assert(mTr_ != nullptr);
	mRend_ = ent_->getComponent<RenderImage>();
	assert(mRend_ != nullptr);
	setCurrentDialogue();
}

void DialogComponent::update()
{
	//Escritura caracter a caracter
	if (sdlutils().virtualTimer().currTime() > lastTimePaused_ + 40) { // este 40 en mejor sitio
		setCurrentDialogue();
		//avance al siguiente caracter
		if(dialogueIndex_ < mDialogMngr_->getCurrentDialog().size())
			dialogueIndex_++;
		lastTimePaused_ = sdlutils().virtualTimer().currTime();
	}
	//Saltar dialogo pasando al siguiente
	if (ih().isKeyDown(SDL_SCANCODE_SPACE)&&
		dialogueIndex_ == mDialogMngr_->getCurrentDialog().size()) {
		mDialogMngr_->nextDialog();
		dialogueIndex_ = 1;
	}
}

void DialogComponent::setCurrentDialogue()
{
	if (mTexture_ != nullptr) {
		delete mTexture_;
		mTexture_ = nullptr;
	}
	mTexture_ = new Texture(sdlutils().renderer(), mDialogMngr_->getCurrentDialog().substr(0,dialogueIndex_),
		*mFont_, build_sdlcolor(0xffffffffff), dialogueWidth_);
	mRend_->setTexture(mTexture_);
	mTr_->setWidth(mTexture_->width());
	mTr_->setHeith(mTexture_->height());
}

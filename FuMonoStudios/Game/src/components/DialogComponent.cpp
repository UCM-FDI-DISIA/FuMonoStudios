#include "DialogComponent.h"
#include "../architecture/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/Font.h"
#include "../sdlutils/Texture.h"
#include "Dialog_Manager.h"
#include "Transform.h"
#include "Render.h"

DialogComponent::DialogComponent(DialogManager* manager): mTr_(nullptr), mRend_(nullptr),
	dialogueWidth_(sdlutils().width() - 300),dialogueIndex(1),textTexture_(nullptr)
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
	if (sdlutils().virtualTimer().currTime() > lasTimePaused + 40) { // este 40 en mejor sitio
		setCurrentDialogue();
		//avance al siguiente caracter
		if(dialogueIndex < mDialogMngr_->GetCurrentDialog().size())
			dialogueIndex++;
		lasTimePaused = sdlutils().virtualTimer().currTime();
	}
	//Saltar dialogo pasando al siguiente
	if (ih().isKeyDown(SDL_SCANCODE_SPACE)&&
		dialogueIndex == mDialogMngr_->GetCurrentDialog().size()) {
		mDialogMngr_->NextDialog();
		dialogueIndex = 1;
	}
}

void DialogComponent::setCurrentDialogue()
{
	if (textTexture_ != nullptr) {
		delete textTexture_;
		textTexture_ = nullptr;
	}
	textTexture_ = new Texture(sdlutils().renderer(), mDialogMngr_->GetCurrentDialog().substr(0,dialogueIndex), *mFont_, build_sdlcolor(0xffffffffff), dialogueWidth_);
	mRend_->setTexture(textTexture_);
	mTr_->setWidth(textTexture_->width());
	mTr_->setHeith(textTexture_->height());
}

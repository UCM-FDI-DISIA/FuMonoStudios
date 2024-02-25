#include "DialogComponent.h"
#include "Transform.h"
#include "Render.h"
#include "../architecture/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/Font.h"

DialogComponent::DialogComponent(DialogManager* manager): mTr_(nullptr), mRend_(nullptr),
	dialogueWidth_(sdlutils().width() - 300),dialogueIndex(1),textTexture_(nullptr)
{
	mDialogMngr_ = manager;
	mFont_ = new Font("resources/fonts/ARIAL.ttf", 40);
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
	if (sdlutils().virtualTimer().currTime() > lasTimePaused + 40) {
		//mDialogMngr_->NextDialog();
		setCurrentDialogue();
		if(dialogueIndex < mDialogMngr_->GetCurrentDialog().size())
			dialogueIndex++;
		lasTimePaused = sdlutils().virtualTimer().currTime();
	}
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
	Texture* muchoTexto = new Texture(sdlutils().renderer(), mDialogMngr_->GetCurrentDialog().substr(0,dialogueIndex), *mFont_, build_sdlcolor(0xffffffffff), dialogueWidth_);
	mRend_->setTexture(muchoTexto);
	mTr_->setWidth(muchoTexto->width());
	mTr_->setHeith(muchoTexto->height());
}

#include "DialogComponent.h"
#include "Transform.h"
#include "Render.h"
#include "../architecture/Entity.h"
#include "../sdlutils/InputHandler.h"

DialogComponent::DialogComponent(DialogManager* manager): mTr_(nullptr), mRend_(nullptr),
	dialogueWidth_(sdlutils().width() - 200),dialogueIndex(0)
{
	mDialogMngr_ = manager;
}

void DialogComponent::initComponent()
{
	mTr_ = ent_->getComponent<Transform>();
	mRend_ = ent_->getComponent<RenderImage>();
}

void DialogComponent::update()
{
	if (ih().isKeyDown(SDL_SCANCODE_SPACE) && sdlutils().virtualTimer().currTime() > lasTimePaused + 500) {
		mDialogMngr_->NextDialog();
		Font fuente("resources/fonts/ARIAL.ttf", 20);
		Texture* muchoTexto = new Texture(sdlutils().renderer(), mDialogMngr_->GetCurrentDialog(),fuente , build_sdlcolor(0xffffffffff), dialogueWidth_);
		mRend_->setTexture(muchoTexto);
		mTr_->setWidth(muchoTexto->width());
		mTr_->setHeith(muchoTexto->height());
		lasTimePaused = sdlutils().virtualTimer().currTime();
	}
}

#include "RenderWithLight.h"
#include "../architecture/Component.h"
#include "Transform.h"
#include "../architecture/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "Clickeable.h"

RenderWithLight::RenderWithLight() : mTexture_(nullptr), mTr_(nullptr), ownsTexture_() { lTexture_ = &sdlutils().images().at("luz"); }

RenderWithLight::RenderWithLight(Texture* img) : mTexture_(img), mTr_(nullptr), ownsTexture_() { lTexture_ = &sdlutils().images().at("luz"); }

RenderWithLight::~RenderWithLight() {
}

void RenderWithLight::initComponent() {
	mTr_ = ent_->getComponent<Transform>();
	assert(mTr_ != nullptr);
}

void RenderWithLight::render() const {
	auto& ihdlr = ih();

	SDL_Point point{ ihdlr.getMousePos().first, ihdlr.getMousePos().second };

	Vector2D pos = mTr_->getPos();

	SDL_Rect mRect_ = build_sdlrect(pos, mTr_->getWidth(), mTr_->getHeigth());
	if (SDL_PointInRect(&point, &mRect_)) {
		pos = pos - Vector2D(10, 10);
		lTexture_->render(build_sdlrect(pos, mTr_->getWidth() + 20, mTr_->getHeigth() + 20), mTr_->getRotation());

		pos = pos + Vector2D(10, 10);
	}

	mTexture_->render(build_sdlrect(pos, mTr_->getWidth(), mTr_->getHeigth()), mTr_->getRotation());
}

void RenderWithLight::setTexture(Texture* texture)
{
	mTexture_ = texture;
}

const Texture* RenderWithLight::getTexture() {
	return mTexture_;
}

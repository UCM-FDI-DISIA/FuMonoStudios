#include "Render.h"
#include "../architecture/Component.h"
#include "Transform.h"
#include "../architecture/Entity.h"

RenderImage::RenderImage() : mTexture_(nullptr), mTr_(nullptr), ownsTexture_() {}

RenderImage::RenderImage(Texture* img) : mTexture_(img),mTr_(nullptr),ownsTexture_() {}

RenderImage::~RenderImage() {
}

void RenderImage::initComponent() {
	mTr_ = ent_->getComponent<Transform>();
	assert(mTr_ != nullptr);
}

void RenderImage::render() const {
	if (mTexture_ != nullptr)
		mTexture_->render(mTr_->getRect(), mTr_->getRotation());
}

void RenderImage::setTexture(Texture* texture)
{
	mTexture_ = texture;
}

const Texture* RenderImage::getTexture() {
	return mTexture_;
}

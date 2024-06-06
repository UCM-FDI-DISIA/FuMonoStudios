#include "Render.h"
#include <architecture/Component.h>
#include <components/Transform.h>
#include <architecture/Entity.h>

RenderImage::RenderImage():RenderImage(nullptr){

}

RenderImage::RenderImage(Texture* img) : mTr_(nullptr), currentTextureIndx_(0){
	texturesVector_.push_back(img);
}

RenderImage::RenderImage(const std::vector<Texture*>& textures): RenderImage(textures,0)
{

}

RenderImage::RenderImage(const std::vector<Texture*>& textures, int startIndx): mTr_(nullptr)
{
	texturesVector_ = textures;
	currentTextureIndx_ = startIndx;
}

RenderImage::~RenderImage() {
}

void RenderImage::initComponent() {
	mTr_ = ent_->getComponent<Transform>();
	assert(mTr_ != nullptr);
}

void RenderImage::render() const {

	assert(texturesVector_.size() > 0);
	if (texturesVector_[currentTextureIndx_] != nullptr)
		texturesVector_[currentTextureIndx_]->render(mTr_->getRect(), mTr_->getRotation(), nullptr, mTr_->getFlip());

}

Texture* RenderImage::getCurrentTexture() {
	return texturesVector_[currentTextureIndx_];
}

std::vector<Texture*>* RenderImage::getVector() {
	return &texturesVector_;
}

void RenderImage::nextTexture()
{
	if (currentTextureIndx_ < texturesVector_.size()-1) {
		currentTextureIndx_++;
	}
	//version cirular
	//currentTextureIndx_ = (currentTextureIndx_ + 1) % texturesVector_.size();
}

void RenderImage::previousTexture()
{
	if (currentTextureIndx_ > 0) {
		currentTextureIndx_--;
	}
}
void RenderImage::setNumberTexture(int i) {
	currentTextureIndx_ = i;
}


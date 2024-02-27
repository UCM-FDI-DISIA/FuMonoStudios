#include "Render.h"
#include "../architecture/Component.h"
#include "Transform.h"
#include "../architecture/Entity.h"

RenderImage::RenderImage(Texture* img) : myTexture(img),myTransform(nullptr),ownsTexture_() {}

RenderImage::~RenderImage() {
}

void RenderImage::initComponent() {
	myTransform = ent_->getComponent<Transform>();
	assert(myTransform != nullptr);
}

void RenderImage::render() const {
	myTexture->render(myTransform->getRect());
}

void RenderImage::setTexture(Texture* texture)
{
	myTexture = texture;
}

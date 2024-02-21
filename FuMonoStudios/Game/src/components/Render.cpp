#include "Render.h"
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include <SDL.h>
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../architecture/Entity.h"

RenderImage::RenderImage(Texture* img) : myTexture(img),myTransform(nullptr) {}

RenderImage::~RenderImage() {}

void RenderImage::initComponent() {
	myTransform = ent_->getComponent<Transform>();
	assert(myTransform != nullptr);
}

void RenderImage::render() const {
	myTexture->render(*myTransform->getRect());
}
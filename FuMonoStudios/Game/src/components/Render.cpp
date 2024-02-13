#include "Render.h"
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include <SDL.h>
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

RenderImage::RenderImage(Texture* img) : myTexture(img) {}

RenderImage::~RenderImage() {}

void RenderImage::initComponent(Transform* trans) {
	myTransform = trans;
}

void RenderImage::render() const {
	myTexture->render(*myTransform->getRect());
}
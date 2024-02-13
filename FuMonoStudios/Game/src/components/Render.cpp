#include "Render.h"
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include <SDL.h>
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../architecture/Entity.h"

RenderImage::RenderImage(Texture* img) : myTexture(img) {}

RenderImage::~RenderImage() {}

void RenderImage::initComponent() {
	myTransform = ent_->getComponent<Transform>(ecs::cmp::TRANSFORM);
}

void RenderImage::render() const {
	myTexture->render(*myTransform->getRect());
}
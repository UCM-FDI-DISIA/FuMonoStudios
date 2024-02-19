#include "Transform.h"
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../architecture/Entity.h"

Transform::Transform(float x, float y, float w, float h) : Component(), worldPosition(x,y), width(w), height(h){
	auto& sdl = *SDLUtils::instance();

	rect = new SDL_Rect();
	rect->h = h;
	rect->w = w;
	rect->x = x;
	rect->y = y;
	// Damos valor a la relativePosition
	if (ent_ && ent_->getParent()) {
		Transform* parentTransform = ent_->getParent()->getComponent<Transform>();
		if (parentTransform) {
			relativePosition = Vector2D(worldPosition.getX() - parentTransform->getPos().getX(), worldPosition.getY() - parentTransform->getPos().getY());
		}
	}

#ifdef _DEBUG
	renderer = sdl.renderer();
#endif // _DEBUG

}

Transform::~Transform() {

}

void Transform::update() {
#ifdef _DEBUG

	//se actualiza la posición del render del objeto continuamente
	rect->x = worldPosition.getX();

	rect->y = worldPosition.getY();

	//std::cout << "Me transformo\n";
#endif // _DEBUG
}

void Transform::render() const {
#ifdef _DEBUG
	SDL_SetRenderDrawColor(renderer, 100, 100, 0, 255);
	//std::cout << "Me renderizo\n";
	SDL_RenderDrawRect(renderer, rect);
#endif // _DEBUG
}

//Cambia la posicion del objeto
void Transform::setPos(Vector2D& pos)
{
	worldPosition = pos;
	if (ent_ && ent_->getParent()) {
		Transform* parentTransform = ent_->getParent()->getComponent<Transform>();
		if (parentTransform) {
			relativePosition = Vector2D(pos.getX() - parentTransform->getPos().getX(), pos.getY() - parentTransform->getPos().getY());
		}
	}
}

//Cambia la posicion del objeto
void Transform::setPos(float x, float y) {
	worldPosition = Vector2D(x, y);
	if (ent_ && ent_->getParent()) {
		Transform* parentTransform = ent_->getParent()->getComponent<Transform>();
		if (parentTransform) {
			relativePosition = Vector2D(x - parentTransform->getPos().getX(), y - parentTransform->getPos().getY());
		}
	}
}

//Cambia la posicion relativa del objeto
void Transform::setRelativePos(Vector2D& relativePos) {
	relativePosition = relativePos;
	if (ent_ && ent_->getParent()) {
		Transform* parentTransform = ent_->getParent()->getComponent<Transform>();
		if (parentTransform) {
			worldPosition = parentTransform->getPos() + relativePos;
		}
	}
}

//Cambia la posicion relativa del objeto
void Transform::setRelativePos(float x, float y) {
	relativePosition = Vector2D(x, y);
	if (ent_ && ent_->getParent()) {
		Transform* parentTransform = ent_->getParent()->getComponent<Transform>();
		if (parentTransform) {
			worldPosition = parentTransform->getPos() + relativePosition;
		}
	}
}

SDL_Rect* Transform::getRect() const {
	return rect;
}
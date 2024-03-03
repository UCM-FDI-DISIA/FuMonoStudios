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
	if (parent) {
		relativePosition = Vector2D(worldPosition.getX() - parent->getPos().getX(), worldPosition.getY() - parent->getPos().getY());
	}

#ifdef _DEBUG
	renderer = sdl.renderer();
#endif // _DEBUG

}

Transform::~Transform() {

}

void Transform::update() {
#ifdef _DEBUG

	//se actualiza la posici�n del render del objeto continuamente
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

std::vector<Transform*> Transform::getChildren() const {
	return children;
}

Transform* Transform::getParent() const {
	return parent;
}

// Los objetos solo pueden tener un �nico padre
void Transform::setParent(Transform* newParent) {
	if (parent != newParent) {
		parent = newParent;
		// Update relative pos				
	}
}

void Transform::addChild(Transform* child) {
	children.push_back(child);
	child->setParent(this);
}

void Transform::removeChild(Transform* child) {
	auto it = std::find(children.begin(), children.end(), child);
	if (it != children.end()) {
		children.erase(it);
		child->setParent(nullptr);
	}
}

//Cambia la posicion del objeto
void Transform::setPos(Vector2D& pos)
{
	worldPosition = pos;
	if (parent) {
		relativePosition = Vector2D(pos.getX() - parent->getPos().getX(), pos.getY() - parent->getPos().getY());
	}
}

Vector2D Transform::getCenter() const {
	return Vector2D(position.getX() - (width / 2), position.getY() - (height / 2));
}

//Devuelve la posici�n relativa
Vector2D Transform::getRelPos() const {
	return position;
}

//Cambia la posicion relativa del objeto
void Transform::setRelativePos(Vector2D& relativePos) {
	relativePosition = relativePos;
	if (parent) {
		worldPosition = parent->getPos() + relativePos;
	}
}

//Cambia la posicion relativa del objeto
void Transform::setRelativePos(float x, float y) {
	relativePosition = Vector2D(x, y);
	if (parent) {
		worldPosition = parent->getPos() + relativePosition;
	}
}

SDL_Rect* Transform::getRect() const {
	return rect;
}
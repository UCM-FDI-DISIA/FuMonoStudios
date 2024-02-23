#include "Transform.h"
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../architecture/Entity.h"

Transform::Transform(float x, float y, float w, float h) : Component(), position(x,y), width(w), height(h), parent(nullptr) {
	auto& sdl = *SDLUtils::instance();

#ifdef _DEBUG
	renderer = sdl.renderer();
#endif // _DEBUG

}

Transform::~Transform() {
}

void Transform::update() {
}

void Transform::render() const {
#ifdef _DEBUG
	SDL_SetRenderDrawColor(renderer, 100, 100, 0, 255);
	//std::cout << "Me renderizo\n";
	SDL_RenderDrawRect(renderer, &getRect());
#endif // _DEBUG
}


Transform* Transform::getParent() const {
	return parent;
}

// Los objetos solo pueden tener un único padre
void Transform::setParent(Transform* newParent) {
	if (parent != newParent) {
		parent = newParent;
		// Update relative pos				
	}
}


//Cambia la posicion del objeto desde una perspectiva global
void Transform::setPos(Vector2D& pos)
{
	position = pos;
}

//Cambia la posicion del objeto desde una perspectiva global
void Transform::setPos(float x, float y) {
	Vector2D newPos = Vector2D(x, y);
	setPos(newPos);
}


Vector2D Transform::getPos() const
{
	Vector2D pos = position;
	Transform* aux = parent;
	while (aux != nullptr) {
		pos = pos + aux->position;
		aux = parent->parent;
	}
	return pos;
}

Vector2D Transform::getRelPos() {
	return position;
}

SDL_Rect& Transform::getRect()const{
	Vector2D pos = getPos();
	SDL_Rect rect = build_sdlrect(pos, width, height);
	return rect;
}
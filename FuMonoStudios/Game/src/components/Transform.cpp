#include "Transform.h"
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../architecture/Entity.h"

Transform::Transform(float x, float y, float w, float h) : Component(), position(x,y), width(w), height(h){
	auto& sdl = *SDLUtils::instance();

	rect = new SDL_Rect();
	rect->h = h;
	rect->w = w;
	rect->x = x;
	rect->y = y;

#ifdef _DEBUG
	renderer = sdl.renderer();
#endif // _DEBUG

}

Transform::~Transform() {

}

void Transform::update() {
#ifdef _DEBUG

	//se actualiza la posición del render del objeto continuamente
	rect->x = position.getX();

	rect->y = position.getY();

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

// Los objetos solo pueden tener un único padre
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
	// Calculamos el movimiento del padre para añadirselo a todos los hijos

	if (parent) {
		position = parent->position + pos;
	}
	else {
		position = pos;
	}

	//std::cout << "Posicion: " << parent << position << std::endl;

	for (auto& child : children) {
		child->setPos(child->position);
		//std::cout << "CHILD";
	}
}

//Cambia la posicion del objeto
void Transform::setPos(float x, float y) {
	Vector2D newPos = Vector2D(x, y);
	setPos(newPos);
}

SDL_Rect* Transform::getRect() const {
	return rect;
}
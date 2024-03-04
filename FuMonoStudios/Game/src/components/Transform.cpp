#include "Transform.h"
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../architecture/Entity.h"
#include "../sdlutils/InputHandler.h"

Transform::Transform(float x, float y, float w, float h) : Component(), position(x, y), width(w), height(h), parent(nullptr) {
	auto& sdl = *SDLUtils::instance();

#ifdef _DEBUG
	renderer = sdl.renderer();
#endif // _DEBUG

}

Transform::~Transform() {
	/// <summary>
	/// destruimos la referencia que esta en su padre
	/// </summary>
	if(parent) parent->childs.erase(parentListIt);
	/// <summary>
	/// AL destruir un transform padre destruimos los hijos de este
	/// </summary>
	for (auto& c : childs) {
		c->ent_->setAlive(false);
		//puntero a nulo por seguridad
		c->parent = nullptr;
	}
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

// Los objetos solo pueden tener un �nico padre
void Transform::setParent(Transform* newParent) {
	if (parent != newParent) {
		parent = newParent;
		parent->childs.push_back(this);
		parentListIt = parent->childs.end();
		parentListIt--;
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

//Devuelve la posici�n en el mundo
Vector2D Transform::getPos() const
{
	Vector2D pos = position;
	Transform* aux = parent;

	//Bucle que itera hasta llegar al primer padre para tener la posici�n en el mundo
	while (aux != nullptr) {
		pos = pos + aux->position;
		aux = parent->parent;
	}
	return pos;
}

Vector2D Transform::getCenter() const {
	return Vector2D(position.getX() - (width / 2), position.getY() - (height / 2));
}

//Devuelve la posici�n relativa
Vector2D Transform::getRelPos() const {
	return position;
}

//Devuelve el Rect en el mundo
SDL_Rect& Transform::getRect()const {
	Vector2D pos = getPos();
	SDL_Rect rect = build_sdlrect(pos, width, height);
	return rect;
}

bool Transform::getIfPointerIn() const {
	auto& ihdlr = ih();

	SDL_Point point{ ihdlr.getMousePos().first, ihdlr.getMousePos().second };

	return SDL_PointInRect(&point, &getRect());
}
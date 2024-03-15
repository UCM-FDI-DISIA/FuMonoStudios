#include "Transform.h"
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../architecture/Entity.h"
#include "../sdlutils/InputHandler.h"

Transform::Transform(float x, float y, float w, float h) : Component(), position_(x, y), width_(w), height_(h), scale_(1),parentTr_(nullptr) {
	auto& sdl = *SDLUtils::instance();

#ifdef _DEBUG
	renderer_ = sdl.renderer();
#endif // _DEBUG

}

Transform::~Transform() {
	/// <summary>
	/// destruimos la referencia que esta en su padre
	/// </summary>
	if(parentTr_) parentTr_->childsTr_.erase(parentListIt_);
	/// <summary>
	/// AL destruir un transform padre destruimos los hijos de este
	/// </summary>
	for (auto& c : childsTr_) {
		c->ent_->setAlive(false);
		//puntero a nulo por seguridad
		c->parentTr_ = nullptr;
	}
}

void Transform::update() {
}

void Transform::render() const {
#ifdef _DEBUG
	SDL_SetRenderDrawColor(renderer_, 100, 100, 0, 255);
	//std::cout << "Me renderizo\n";
	SDL_RenderDrawRect(renderer_, &getRect());
#endif // _DEBUG
}

Transform* Transform::getParent() const {
	return parentTr_;
}

// Los objetos solo pueden tener un unico padre
void Transform::setParent(Transform* newParent) {
	if (parentTr_ != newParent) {
		parentTr_ = newParent;
		parentTr_->childsTr_.push_back(this);
		parentListIt_ = parentTr_->childsTr_.end();
		parentListIt_--;
		// Update relative pos				
	}
}


//Cambia la posicion del objeto desde una perspectiva global
void Transform::setPos(Vector2D& pos)
{
	position_ = pos;
}

//Cambia la posicion del objeto desde una perspectiva global
void Transform::setPos(float x, float y) {
	Vector2D newPos = Vector2D(x, y);
	setPos(newPos);
}

//Devuelve la posici�n en el mundo
Vector2D Transform::getPos() const
{
	Vector2D pos = position_;
	Transform* aux = parentTr_;

	//Bucle que itera hasta llegar al primer padre para tener la posici�n en el mundo
	while (aux != nullptr) {
		pos = pos + aux->position_;
		aux = parentTr_->parentTr_;
	}
	return pos;
}

Vector2D Transform::getCenter() const {
	return Vector2D(position_.getX() + ((width_ * scale_) / 2), position_.getY() + ((height_ * scale_) / 2));
}

//Devuelve la posici�n relativa
Vector2D Transform::getRelPos() const {
	return position_;
}

//Devuelve el Rect en el mundo
SDL_Rect& Transform::getRect()const {
	Vector2D pos = getPos();
	SDL_Rect rect = build_sdlrect(pos, width_ * scale_, height_ * scale_);
	return rect;
}

bool Transform::getIfPointerIn() const {
	auto& ihdlr = ih();

	SDL_Point point{ ihdlr.getMousePos().first, ihdlr.getMousePos().second };

	return SDL_PointInRect(&point, &getRect());
}
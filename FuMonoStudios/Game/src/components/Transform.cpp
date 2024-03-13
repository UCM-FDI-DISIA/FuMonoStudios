#include "Transform.h"
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../architecture/Entity.h"
#include "../sdlutils/InputHandler.h"

Transform::Transform(float x, float y, float w, float h) : Component(), 
position_(x, y), width_(w), height_(h), scale_(1), trueScale_(1),parentTr_(nullptr) {
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

// Los objetos solo pueden tener un �nico padre
void Transform::setParent(Transform* newParent) {
	if (parentTr_ != newParent) {
		parentTr_ = newParent;
		parentTr_->childsTr_.push_back(this);
		parentListIt_ = parentTr_->childsTr_.end();
		parentListIt_--;
		// Update relative pos	
		relPos_ = position_;
	}
}

void Transform::setPosDragging(Vector2D cursorPos, float differenceX, float differenceY) 
{
	float porcentaje = ((trueScale_ * 100) / scale_) / 100;

	Vector2D pos = Vector2D(cursorPos.getX() - (differenceX * porcentaje),
					cursorPos.getY() - (differenceY * porcentaje));


	std::cout << trueScale_ << std::endl;
	position_ = pos;

	// mueve las posiciones relativas de los hijos al cambiar de escala
	for (Transform* trCh : childsTr_)
	{
		trCh->setPos((trCh->getRelPos() * depth_).getX(),
			(trCh->getRelPos() * depth_).getY());
	}

	if (usingDepth_)
	{
		updateDepth();
	}
}

void Transform::setScale(float Scale) {
	scale_ = Scale;
	if (!usingDepth_)
		trueScale_ = scale_;
}

void Transform::activateDepth() {
		usingDepth_ = true;
		updateDepth();
}

void Transform::updateDepth() {
	//función que calcula el depth
	depth_ = (getCenter().getY() * 0.07) + 40;
	if (depth_ > 100)
		depth_ = 100;
	depth_ = depth_ / 100; // para que quede como porcentaje
	trueScale_ = scale_ * depth_;

	// esto actualiza el scale de cada transform
	for (Transform* chTr : childsTr_)
	{
		float porcentaje = ((trueScale_ * 100) / scale_) / 100;
		chTr->setTrueScale(porcentaje * chTr->getOriginalScale());
	}
}

//Cambia la posicion del objeto desde una perspectiva global
void Transform::setPos(Vector2D& pos)
{
	position_ = pos;

	// mueve las posiciones relativas de los hijos al cambiar de escala
	for (Transform* trCh : childsTr_)
	{
		trCh->setPos((trCh->getRelPos() * depth_).getX(), 
			(trCh->getRelPos() * depth_).getY());
	}

	if (usingDepth_)
	{
		updateDepth();
	}
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
	return Vector2D(position_.getX() + ((width_ * trueScale_) / 2), position_.getY() + ((height_ * scale_) / 2));
}

//Devuelve la posici�n relativa
Vector2D Transform::getRelPos() const {
	return relPos_;
}

//Devuelve el Rect en el mundo
SDL_Rect& Transform::getRect()const {
	Vector2D pos = getPos();
	SDL_Rect rect = build_sdlrect(pos, width_ * trueScale_, height_ * trueScale_);
	return rect;
}

bool Transform::getIfPointerIn() const {
	auto& ihdlr = ih();

	SDL_Point point{ ihdlr.getMousePos().first, ihdlr.getMousePos().second };

	return SDL_PointInRect(&point, &getRect());
}
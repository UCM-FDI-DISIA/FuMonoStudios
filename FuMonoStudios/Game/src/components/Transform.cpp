#include "Transform.h"
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"

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

void Transform::setPos(Vector2D& pos)
{
	position = pos;
	// hay que ver como acceder a los métodos de la entidad para usar el getParent y poder obtener la posRelativa
	//relativePosition = pos + this->ent_
}

void Transform::setPos(float x, float y)
{
	position = Vector2D(x, y);
}

SDL_Rect* Transform::getRect() const {
	return rect;
}
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

void Transform::Move(std::pair<float,float> pos) {

	position.set(pos.first, pos.second);

	rect->x = pos.first - (rect->w / 2);

	rect->y = pos.second - (rect->h / 2);

}

void Transform::Move(float x, float y) {

	position.set(x, y);

	rect->x = x - (rect->w / 2);

	rect->y = y - (rect->h / 2);

}

void Transform::update() {
#ifdef _DEBUG
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
}

void Transform::setPos(float x, float y)
{
	position = Vector2D(x, y);
}

SDL_Rect* Transform::getRect() const {
	return rect;
}
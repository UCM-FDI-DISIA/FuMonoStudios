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
	renderer = sdl.renderer();
}

Transform::~Transform() {

}

void Transform::Move(std::pair<float,float> pos) {

}

void Transform::update() {
#ifdef _DEBUG
	std::cout << "Me transformo\n";
#endif // _DEBUG
}

void Transform::render() const {
#ifdef _DEBUG
	SDL_SetRenderDrawColor(renderer, 100, 100, 0, 255);
	std::cout << "Me renderizo\n";
	SDL_RenderDrawRect(renderer, rect);
#endif // _DEBUG
}

SDL_Rect* Transform::getRect() const {
	return rect;
}
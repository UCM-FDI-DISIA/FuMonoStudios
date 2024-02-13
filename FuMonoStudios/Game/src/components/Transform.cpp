#include "Transform.h"
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"

Transform::Transform(float x, float y, float w, float h) : Component(), position(x,y), width(w), height(h){
	auto& sdl = *SDLUtils::instance();

	getRect = new SDL_Rect();
	getRect->h = h;
	getRect->w = w;
	getRect->x = x;
	getRect->y = y;
	renderer = sdl.renderer();
}

Transform::~Transform() {

}

void Transform::Move(std::pair<float,float> pos) {

}

void Transform::update() {
#ifdef DEBUG
	std::cout << "Me transformo\n";
#endif // DEBUG
}

void Transform::render() const {
#ifdef _DEBUG
	SDL_SetRenderDrawColor(renderer, 100, 100, 0, 255);
	std::cout << "Me renderizo\n";
	SDL_RenderDrawRect(renderer, getRect);
#endif // _DEBUG
}
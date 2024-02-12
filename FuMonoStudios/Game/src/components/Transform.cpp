#include "Transform.h"
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"

Transform::Transform(float x, float y, float w, float h) : Component(), position(x,y), width(w), height(h){
	getRect->h = h;
	getRect->w = w;
	getRect->x = x;
	getRect->y = y;
}

Transform::~Transform() {

}

void Transform::Move(std::pair<float,float> pos) {

}

void Transform::update() {

}

void Transform::render() const {
	SDL_RenderFillRect(window, getRect);
}
#pragma once
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include <SDL.h>
#include "../sdlutils/SDLUtils.h"

class Transform : public ecs::Component 
{
public:
	Transform(float x, float y, float w, float h);
	~Transform();
	void Move(std::pair<float, float> pos);
	SDL_Rect* getRect() const;
	void update();
	void render() const;
private:
	Vector2D position;
	float width;
	float height;
	SDL_Rect* rect;
	SDL_Renderer* renderer;
};


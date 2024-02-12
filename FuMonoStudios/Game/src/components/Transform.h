#pragma once
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include <SDL.h>

class Transform : public ecs::Component 
{
private:
	Vector2D position;
	float width;
	float height;
	SDL_Rect* getRect;
	SDL_Renderer* window;
public:
	Transform(float x, float y, float w, float h);
	~Transform();
	void Move(std::pair<float, float> pos);
	void update();
	void render() const;
};


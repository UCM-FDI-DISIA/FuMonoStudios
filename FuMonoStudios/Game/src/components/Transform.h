#pragma once
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include <SDL.h>
#include "../sdlutils/SDLUtils.h"

class Transform : public ecs::Component 
{
public:
	__CMP_DECL__(ecs::cmp::TRANSFORM)
	Transform(float x, float y, float w, float h);
	~Transform();
	void Move(std::pair<float, float> pos);

	void Move(float x, float y);

	SDL_Rect* getRect() const;
	void update();
	void render() const;


	void setPos(Vector2D& pos);
	void setPos(float x, float y);

	Vector2D getPos() { return position; };
	float getWidth() { return width; };
	float getHeith() { return height; };

private:
	Vector2D position;
	float width;
	float height;
	/*
	Segun tengo entendido no sale tan caro crear y destruir un sdl rect y
	puede llegar a ser mucho mas arriesgado hacer que el propio transform tenga que
	actualizar dos datos iguales cuado con accesores podr�a llegar a ser mucho mas sencillo
	*/
	SDL_Rect* rect;
#ifdef _DEBUG
	SDL_Renderer* renderer;
#endif // _DEBUG

};


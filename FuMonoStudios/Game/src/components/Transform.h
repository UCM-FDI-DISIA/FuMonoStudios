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


	SDL_Rect* getRect() const;
	void update();
	void render() const;

	std::vector<Transform*> getChildren() const;
	Transform* getParent() const;
	void setParent(Transform* newParent);
	void addChild(Transform* child);
	void removeChild(Transform* child);

	void setPos(Vector2D& pos);
	void setPos(float x, float y);
	void setRelativePos(Vector2D& pos);
	void setRelativePos(float x, float y);

	Vector2D getPos() { return worldPosition; };
	Vector2D getRelativePos() { return relativePosition; };
	float getWidth() { return width; };
	float getHeith() { return height; };

private:
	Vector2D worldPosition; // es la posicion en el mundo
	Vector2D relativePosition; // es la posicion con respecto a la position del padre
	float width;
	float height;
	/*
	Segun tengo entendido no sale tan caro crear y destruir un sdl rect y
	puede llegar a ser mucho mas arriesgado hacer que el propio transform tenga que
	actualizar dos datos iguales cuado con accesores podría llegar a ser mucho mas sencillo
	*/
	SDL_Rect* rect;
	Transform* parent;
	std::vector<Transform*> children;
#ifdef _DEBUG
	SDL_Renderer* renderer;
#endif // _DEBUG

};


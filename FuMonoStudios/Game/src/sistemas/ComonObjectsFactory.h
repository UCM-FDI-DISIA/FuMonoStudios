#pragma once
#include <string>
#include "../architecture/Scene.h"
#include "../architecture/Entity.h"
class ComonObjectsFactory
{
public:
	ComonObjectsFactory(){};
	~ComonObjectsFactory(){};
	/// <summary>
	/// crea un objeto que contiene texto
	/// </summary>
	/// <param name="scene"></param>
	/// <param name="text"></param>
	/// <param name="fontSize"></param>
	/// <param name="pos"></param>
	/// <returns></returns>
	ecs::Entity* createLabel(ecs::Scene* scene,const Vector2D& pos,const std::string& text, int fontSize, SDL_Color textColor = build_sdlcolor(0x000000ff));
};


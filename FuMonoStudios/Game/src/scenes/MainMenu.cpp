#include "MainMenu.h"
#include "../architecture/Entity.h"
#include <iostream>
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/Render.h"

ecs::MainMenu::MainMenu()
{
	init();
}

ecs::MainMenu::~MainMenu()
{
}

void ecs::MainMenu::init()
{
	std::cout << "Hola Menu" << std::endl;
	sdlutils().clearRenderer();

	

	Entity* Titulo = addEntity();
	Texture* sujetaplazas = &sdlutils().images().at("title");
	Transform* e = Titulo->addComponent<Transform>(ecs::cmp::TRANSFORM, 0.0f, 0.0f, sujetaplazas->width(), sujetaplazas->height());
	RenderImage* nachos = Titulo->addComponent<RenderImage>(ecs::cmp::IMAGE, sujetaplazas);

	Texture* porros = &sdlutils().images().at("press");
	Entity* Boton = addEntity();
	Transform* wakamole = Boton->addComponent<Transform>(ecs::cmp::TRANSFORM, 960.0f, 480.0f, porros->width(), porros->height());
	RenderImage* salsa = Boton->addComponent<RenderImage>(ecs::cmp::IMAGE, porros);
}

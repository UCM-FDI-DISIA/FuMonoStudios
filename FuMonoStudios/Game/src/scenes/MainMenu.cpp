#include "MainMenu.h"
#include "../architecture/Entity.h"
#include <iostream>
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/Render.h"
#include "../components/Clickeable.h"
#include "../architecture/Game.h"

//ecs::MainMenu::MainMenu()
//{
//	init();
//}

ecs::MainMenu::MainMenu() : Scene() {

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
	Transform* e = Titulo->addComponent<Transform>(0.0f, 0.0f, sujetaplazas->width(), sujetaplazas->height());
	RenderImage* nachos = Titulo->addComponent<RenderImage>(sujetaplazas);

	Texture* porros = &sdlutils().images().at("press");
	Entity* Boton = addEntity();
	
	Transform* wakamole = Boton->addComponent<Transform>(960.0f, 480.0f, porros->width(), porros->height());
	RenderImage* salsa = Boton->addComponent<RenderImage>(porros);

	auto clicker = Boton->addComponent<Clickeable>();
	/*Boton->addComponent<Trigger>();
	Boton->getComponent<Trigger>()->addCallback([]() {

		std::cout << "Tocando" << std::endl;

		});*/

	/*void Aux(Game * game) {

		

		(*game).loadScene(ecs::sc::MAIN_SCENE);

	}*/

	Callback cosa = []() {
		std::cout << "Click" << std::endl;
		gm().writeMessage();

	};
	clicker->addEvent(cosa);
}

void ecs::MainMenu::changeToMainScene() {

	//game().loadScene(ecs::sc::MAIN_SCENE);

}

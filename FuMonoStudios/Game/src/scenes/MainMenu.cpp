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

	Font* fuente = new Font("recursos/fonts/ARIAL.ttf", 50);

	Entity* Titulo = addEntity();
	Texture* texturaTitulo = &sdlutils().images().at("title");
	Transform* transformTitulo = Titulo->addComponent<Transform>(0.0f, 0.0f, texturaTitulo->width(), texturaTitulo->height());
	RenderImage* renderTitulo = Titulo->addComponent<RenderImage>(texturaTitulo);
	Titulo->addComponent<DragAndDrop>();

	Texture* texturaBoton = new Texture(sdlutils().renderer(), "Pulse El Bot�n", *fuente, build_sdlcolor(0x000000ff));
	Entity* BotonPress = addEntity();
	
	Transform* transformBoton = BotonPress->addComponent<Transform>(260.0f, 480.0f, texturaBoton->width(), texturaBoton->height());
	RenderImage* renderBoton = BotonPress->addComponent<RenderImage>(texturaBoton);

	auto clickerPress = BotonPress->addComponent<Clickeable>();

	/*Boton->addComponent<Trigger>();
	Boton->getComponent<Trigger>()->addCallback([]() {

		std::cout << "Tocando" << std::endl;

		});*/

	/*void Aux(Game * game) {

		

		(*game).loadScene(ecs::sc::MAIN_SCENE);

	}*/
	CallbackClickeable funcPress = [this]() {
		gm().changeScene(ecs::sc::MENU_SCENE, ecs::sc::EXPLORE_SCENE);

	};
	clickerPress->addEvent(funcPress);
}

void ecs::MainMenu::changeToMainScene() {

	//game().loadScene(ecs::sc::MAIN_SCENE);

}

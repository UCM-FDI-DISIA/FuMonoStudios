#include "ExplorationScene.h"
#include "../architecture/Entity.h"
#include <iostream>
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/Render.h"
#include "../components/Clickeable.h"
#include "../components/DragAndDrop.h"
#include "../components/Trigger.h"
#include "../architecture/Game.h"
#include <string>
#include "../sdlutils/Texture.h"
#include "../components/DialogComponent.h"

ecs::ExplorationScene::ExplorationScene() :Scene(), map(this)
{
}

ecs::ExplorationScene::~ExplorationScene()
{
}

void ecs::ExplorationScene::init()
{
	std::cout << "Hola Exploracion" << std::endl;
	//sdlutils().clearRenderer();
	// Caja CLicker
	/*Entity* Prueba2 = addEntity();
	Texture* sujetaplazas = &sdlutils().images().at("boxTest");
	float scale = 0.2;
	Transform* e = Prueba2->addComponent<Transform>(700.0f, 100.0f, sujetaplazas->width() * scale, sujetaplazas->height() * scale);
	RenderImage* nachos = Prueba2->addComponent<RenderImage>(sujetaplazas);
	auto clicker = Prueba2->addComponent<Clickeable>();
	Prueba2->addComponent<Trigger>();

		//TODO: probar que con un boton se puedan cargar otras escenas
	CallbackClickeable cosa = [this]() {
		map.navigate("Artemisa");
		sdlutils().clearRenderer();
		map.renderBackGround();
		};
	clicker->addEvent(cosa);*/





	/*auto boxBg = addEntity();
	auto bgTr = boxBg->addComponent<Transform>(100, sdlutils().height() - 200, sdlutils().width()-200, 200);
	boxBg->addComponent<RenderImage>(&sdlutils().images().at("placeHolder"));

	auto dialogoBox = addEntity();
	auto textTr = dialogoBox->addComponent<Transform>(20, 20,100,100);
	textTr->setParent(bgTr);
	dialogoBox->addComponent<RenderImage>();
	dialogoBox->addComponent<DialogComponent>(&dialogMngr_);*/


	/*Texture* texturaBoton = &sdlutils().images().at("press");
	Entity* BotonPress = addEntity();

	Transform* transformBoton = BotonPress->addComponent<Transform>(260.0f, 480.0f, texturaBoton->width(), texturaBoton->height());
	RenderImage* renderBoton = BotonPress->addComponent<RenderImage>(texturaBoton);

	auto clickerPress = BotonPress->addComponent<Clickeable>();
	Callback funcPress = [](Entity* a) {
		gm().changeScene(ecs::sc::EXPLORE_SCENE, ecs::sc::MAIN_SCENE);
	};
	clickerPress->add*ent(funcPress);*/
}

void ecs::ExplorationScene::render()
{
	map.renderBackGround();
	Scene::render();
}

#include "MainScene.h"
#include "../architecture/Entity.h"
#include <iostream>
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/Render.h"
#include "../components/Clickeable.h"
#include "../components/DragAndDrop.h"


ecs::MainScene::MainScene()
{
	
}

ecs::MainScene::~MainScene()
{
}

void ecs::MainScene::init()
{
	std::cout << "Hola Main"<<std::endl;
	sdlutils().clearRenderer(build_sdlcolor(0xFFFFFFFF));
	//crear objetos
	
	//Entidad para probar el transform
	

	/*
	Entity* Prueba = addEntity();
	Transform* wakamole = Prueba->addComponent<Transform>(ecs::cmp::TRANSFORM, 200.0f, 25.0f, 300.0f, 500.0f);
	*/
	Entity* Prueba2 = addEntity();
	Texture* sujetaplazas = &sdlutils().images().at("placeHolder");
	Transform* e = Prueba2->addComponent<Transform>(ecs::cmp::TRANSFORM, 200.0f, 100.0f, sujetaplazas->width(), sujetaplazas->height());
	RenderImage* nachos = Prueba2->addComponent<RenderImage>(ecs::cmp::IMAGE, sujetaplazas);
	auto clicker = Prueba2->addComponent<Clickeable>(ecs::cmp::CLICKEABLE);
	Callback cosa = []() {std::cout << "Click" << std::endl; };
	clicker->addEvent(cosa);

	Entity* Prueba3 = addEntity(layer::BACKGROUND);
	auto tr = Prueba3->addComponent<Transform>(ecs::cmp::TRANSFORM, 100.0f, 100.0f, sujetaplazas->width(), sujetaplazas->height());
	auto rd = Prueba3->addComponent<RenderImage>(ecs::cmp::IMAGE,sujetaplazas);
	Prueba3->addComponent<DragAndDrop>(ecs::cmp::DRAGANDDROP);
}



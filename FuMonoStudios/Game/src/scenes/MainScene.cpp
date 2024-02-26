#include "MainScene.h"
#include "../architecture/Entity.h"
#include <iostream>
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/Render.h"
#include "../components/Clickeable.h"
#include "../components/DragAndDrop.h"
#include "../components/Trigger.h"
#include "../components//Gravity.h"
#include "../architecture/Game.h"


ecs::MainScene::MainScene():Scene()
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
	
	Texture* sujetaplazas = &sdlutils().images().at("boxTest");
	float scale = 0.2;

	/*
	Entity* Prueba2 = addEntity();
	
	Transform* e = Prueba2->addComponent<Transform>(700.0f, 100.0f, sujetaplazas->width() * scale, sujetaplazas->height() * scale);
	RenderImage* nachos = Prueba2->addComponent<RenderImage>(sujetaplazas);
	//Gravity* gravityComp = Prueba2->addComponent<Gravity>(10);
	auto clicker = Prueba2->addComponent<Clickeable>();
	Prueba2->addComponent<Trigger>();

	Prueba2->getComponent<Trigger>()->addCallback([]() {

		std::cout << "Activar Evento P2" << std::endl;
	});
	*/
	// Caja CLicker
	


	// Dragable Box
	Entity* Prueba3 = addEntity(layer::BACKGROUND);
	Transform* tr = Prueba3->addComponent<Transform>(100.0f, 100.0f, sujetaplazas->width() * scale, sujetaplazas->height() * scale);
	RenderImage* rd = Prueba3->addComponent<RenderImage>(sujetaplazas);
	Gravity* gravityComp3 = Prueba3->addComponent<Gravity>();
	Prueba3->addComponent<DragAndDrop>();
	Prueba3->getComponent<Trigger>()->addCallback([]() {

		std::cout << "Activar Evento P3" << std::endl;

		});

	// Dragable Box2
	Entity* Prueba4 = addEntity(layer::DEFAULT);
	Transform* tr4 = Prueba4->addComponent<Transform>(250.0f, 250.0f, sujetaplazas->width() * scale, sujetaplazas->height() * scale);
	RenderImage* rd4 = Prueba4->addComponent<RenderImage>(sujetaplazas);
	Gravity* gravityComp4 = Prueba4->addComponent<Gravity>();
	Prueba4->addComponent<DragAndDrop>();
	Prueba4->getComponent<Trigger>()->addCallback([]() {

		std::cout << "Activar Evento P4" << std::endl;

		});


	// Sello
	Entity* selloPrueba = addEntity(layer::BACKGROUND);
	Texture* selloTexture = &sdlutils().images().at("selloTest");
	Transform* trSello = selloPrueba->addComponent<Transform>(100.0f, 100.0f, selloTexture->width() * scale, selloTexture->height() * scale);
	RenderImage* rd1 = selloPrueba->addComponent<RenderImage>(selloTexture);
	
	// Posición Relativa
	trSello->setParent(tr);
	//tr->addChild(trSello);
	//trSello->setRelativePos(100.0f, 100.0f);
	//tr->setPos(100.0f, 400.0f);
	//TODO: probar que con un boton se puedan cargar otras escenas
	Callback cosa = [Prueba3]() {
		Prueba3->setAlive(false);
	};
	//clicker->addEvent(cosa);
}



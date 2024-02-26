#include "MainScene.h"
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
#include "../components/PackageChecker.h"
#include "../components/Paquete.h"
#include "../components/Herramientas.h"

ecs::MainScene::MainScene():Scene()
{
	
}

ecs::MainScene::~MainScene()
{
}


void sellar(ecs::Entity* ent) {
	std::cout << "HOLA";
}

void ecs::MainScene::init()
{
	std::cout << "Hola Main" << std::endl;
	sdlutils().clearRenderer(build_sdlcolor(0xFFFFFFFF));
	//crear objetos
	/*
	// Caja CLicker
	Entity* Prueba2 = addEntity();
	Texture* sujetaplazas = &sdlutils().images().at("boxTest");
	float scale = 0.2;
	Transform* e = Prueba2->addComponent<Transform>(700.0f, 100.0f, sujetaplazas->width() * scale, sujetaplazas->height() * scale);
	RenderImage* nachos = Prueba2->addComponent<RenderImage>(sujetaplazas);
	auto clicker = Prueba2->addComponent<Clickeable>();
	Prueba2->addComponent<Trigger>();

	Prueba2->getComponent<Trigger>()->addCallback([]() {

		std::cout << "Activar Evento P2" << std::endl;

		});

	//TODO: probar que con un boton se puedan cargar otras escenas
	Callback cosa = []() {
		std::cout << "Click" << std::endl;
	};
	clicker->addEvent(cosa);

	// Dragable Box
	Entity* Prueba3 = addEntity(layer::BACKGROUND);
	Transform* tr = Prueba3->addComponent<Transform>(100.0f, 100.0f, sujetaplazas->width() * scale, sujetaplazas->height() * scale);
	RenderImage* rd = Prueba3->addComponent<RenderImage>(sujetaplazas);
	Prueba3->addComponent<DragAndDrop>();
	Prueba3->getComponent<Trigger>()->addCallback([]() {

		std::cout << "Activar Evento P3" << std::endl;

		});

	// Sello
	Entity* selloPrueba = addEntity(layer::DEFAULT);
	Texture* selloTexture = &sdlutils().images().at("selloTest");
	Transform* trSello = selloPrueba->addComponent<Transform>(700.0f, 100.0f, selloTexture->width() * scale, selloTexture->height() * scale);
	RenderImage* rd1 = selloPrueba->addComponent<RenderImage>(selloTexture);

	// Posición Relativa
	e->addChild(trSello);
	trSello->setRelativePos(100.0f, 100.0f);*/

	float scale = 0.2;

	//Paquete de prueba
	Entity* Paquet = addEntity(layer::BACKGROUND);
	Texture* texturaPaquet = &sdlutils().images().at("boxTest");
	Transform* trPq = Paquet->addComponent<Transform>(100.0f, 100.0f, texturaPaquet->width() * scale, texturaPaquet->height() * scale);
	RenderImage* rd = Paquet->addComponent<RenderImage>(texturaPaquet);
	Trigger* trgPq = Paquet->addComponent<Trigger>();
	Paquete* pqPq = Paquet->addComponent<Paquete>(Paquete::Demeter, Paquete::C1, Paquete::Alimento, 
		true, Paquete::Bajo, 20, false, false);
	DragAndDrop* drgPq = Paquet->addComponent<DragAndDrop>();

	// Sellador calle
	Entity* sellador = addEntity(layer::BACKGROUND);
	Texture* selladorTextura = &sdlutils().images().at("selladorTest");
	Transform* trSellador = sellador->addComponent<Transform>(700, 700, selladorTextura->width() * scale, selladorTextura->height() * scale);
	Herramientas* herrSellador = sellador->addComponent<Herramientas>();
	Trigger* trgSellador = sellador->addComponent<Trigger>();
	trgSellador->addCallback([](ecs::Entity* entRec) {
		std::cout << " hola";
		});
	sellador->addComponent<RenderImage>(selladorTextura);
	sellador->addComponent<DragAndDrop>();

	//Tubería
	Entity* tuberia = addEntity();
	Transform* trTub = tuberia->addComponent<Transform>(500, 100, 50, 50);
	Trigger* trgTub = tuberia->addComponent<Trigger>();
	PackageChecker* checker = tuberia->addComponent<PackageChecker>(Paquete::Demeter);
	trgTub->addCallback([checker](ecs::Entity* entRec) {
		if (entRec->getComponent<Paquete>() != nullptr) {
			if (checker->checkPackage(entRec->getComponent<Paquete>())) {
				std::cout << "WAA!  YA MADE IT!\n";
			}
			else {
				std::cout << "NUH UH\n";
			}
		}
		});

	//Tubería2
	/*Entity* tuber2 = addEntity();
	Transform* trTb2 = tuber2->addComponent<Transform>(700, 100, 50, 50);
	Trigger* trgTb2 = tuber2->addComponent<Trigger>();
	PackageChecker* che = tuber2->addComponent<PackageChecker>(Paquete::Demeter);
	trgTb2->addCallback([&che, &pqPq]() {
		if (che->checkPackage(pqPq)) {
			std::cout << "WAA!  YA MADE IT!\n";
		}
		else {
			std::cout << "NUH UH\n";
		}
		});*/
}
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
#include "../components/MultipleTextures.h"


void ecs::MainScene::createManual()
{
	Entity* manual = addEntity();
	Texture* manualTexture = &sdlutils().images().at("bookTest");
	Texture* manualTexture2 = &sdlutils().images().at("placeHolder");
	float scale = 0.075;
	Transform* manualTransform = manual->addComponent<Transform>(500.0f, 500.0f, manualTexture->width() * scale, manualTexture->height() * scale);
	RenderImage* manualRender = manual->addComponent<RenderImage>(manualTexture);
	manual->addComponent<DragAndDrop>();
	MultipleTextures* patata = manual->addComponent<MultipleTextures>();
	patata->addTexture(manualTexture);
	patata->addTexture(manualTexture2);
	patata->initComponent();


	Entity* button = addEntity(ecs::layer::FOREGROUND);
	Texture* buttonTexture = &sdlutils().images().at("flechaTest");
	float buttonScale = 0.15;
	Transform* buttonTransform = button->addComponent<Transform>(100, 300, buttonTexture->width() * buttonScale, buttonTexture->height() * buttonScale);
	RenderImage* buttonRender = button->addComponent<RenderImage>(buttonTexture);
	buttonTransform->setParent(manualTransform);
	button->addComponent<Clickeable>();
	button->getComponent<Clickeable>()->addEvent([patata](Entity* e) {

		patata->nextTexture();
	});

	Entity* button2 = addEntity(ecs::layer::FOREGROUND);
	Transform* buttonTransform2 = button2->addComponent<Transform>(400, 300, buttonTexture->width() * buttonScale, buttonTexture->height() * buttonScale);
	RenderImage* buttonRender2 = button2->addComponent<RenderImage>(buttonTexture);
	buttonTransform2->setParent(manualTransform);
	button2->addComponent<Clickeable>();
	button2->getComponent<Clickeable>()->addEvent([patata](Entity* e) {

		patata->previousTexture();
		});
}

ecs::MainScene::MainScene():Scene()
{
	
}

ecs::MainScene::~MainScene()
{
}

void ecs::MainScene::init()
{
	std::cout << "Hola Main" << std::endl;
	sdlutils().clearRenderer(build_sdlcolor(0xFFFFFFFF));
	//crear objetos

	float scale = 0.2;

	//Paquete de prueba
	Entity* Paquet = addEntity();
	Texture* texturaPaquet = &sdlutils().images().at("boxTest");
	Transform* trPq = Paquet->addComponent<Transform>(200.0f, 500.0f, texturaPaquet->width() * scale, texturaPaquet->height() * scale);
	RenderImage* rd = Paquet->addComponent<RenderImage>(texturaPaquet);
	Paquete* pqPq = Paquet->addComponent<Paquete>(Paquete::Demeter, Paquete::C1, Paquete::Alimento, 
		true, Paquete::Bajo, 20, false, false);
	DragAndDrop* drgPq = Paquet->addComponent<DragAndDrop>();

	// funcion que permite interactuar con herramientas
	Paquet->getComponent<Trigger>()->addCallback([Paquet](ecs::Entity* ent) {
		Herramientas* herrComp = ent->getComponent<Herramientas>();
		if (herrComp != nullptr) {
			herrComp->interact(Paquet);
		}
	});

	// Sellador calle A
	Entity* selloA = addEntity();
	Texture* selloATex = &sdlutils().images().at("selladorA");
	selloA->addComponent<Transform>(1200, 200, selloATex->width() * scale, selloATex->height() * scale);
	selloA->addComponent<DragAndDrop>();
	selloA->addComponent<RenderImage>(selloATex);
	Herramientas* herrSelladorA = selloA->addComponent<Herramientas>();
	herrSelladorA->setFunctionality(SelloCalleA);

	// Sellador calle B
	Entity* selloB = addEntity();
	Texture* selloBTex = &sdlutils().images().at("selladorB");
	selloB->addComponent<Transform>(1200, 300, selloBTex->width() * scale, selloBTex->height() * scale);
	selloB->addComponent<DragAndDrop>();
	selloB->addComponent<RenderImage>(selloBTex);
	Herramientas* herrSelladorB = selloB->addComponent<Herramientas>();
	herrSelladorB->setFunctionality(SelloCalleB);

	// Sellador calle C
	Entity* selloC = addEntity();
	Texture* selloCTex = &sdlutils().images().at("selladorC");
	selloC->addComponent<Transform>(1200, 400, selloCTex->width() * scale, selloCTex->height() * scale);
	selloC->addComponent<DragAndDrop>();
	selloC->addComponent<RenderImage>(selloCTex);
	Herramientas* herrSelladorC = selloC->addComponent<Herramientas>();
	herrSelladorC->setFunctionality(SelloCalleC);

	createManual();

	// Fondo
	Entity* Fondo = addEntity(ecs::layer::BACKGROUND);
	Fondo->addComponent<Transform>(0, 0, sdlutils().width(), sdlutils().height());
	Fondo->addComponent<RenderImage>(&sdlutils().images().at("fondoOficina"));

	//Demeter, Hefesto, Hestia, Artemisa, Hermes, Apolo, Poseidon, Erroneo
	Entity* tubDem = addEntity();
	tubDem->addComponent<Transform>(90, 0, 100, 150);
	Trigger* demTri = tubDem->addComponent<Trigger>();
	PackageChecker* demCheck = tubDem->addComponent<PackageChecker>(Paquete::Demeter);
	demTri->addCallback([demCheck](ecs::Entity* entRec) {
		if (entRec->getComponent<Paquete>() != nullptr) {
			if (demCheck->checkPackage(entRec->getComponent<Paquete>())) {
				std::cout << "WAA!  YA MADE IT!\n";
			}
			else {
				std::cout << "NUH UH\n";
			}
		}
		});

	Entity* tubHef = addEntity();
	tubHef->addComponent<Transform>(280, 0, 100, 150);
	tubHef->addComponent<Trigger>();
	PackageChecker* hefCheck = tubHef->addComponent<PackageChecker>(Paquete::Hefesto);

	Entity* tubHes = addEntity();
	tubHes->addComponent<Transform>(470, 0, 100, 150);
	tubHes->addComponent<Trigger>();
	PackageChecker* hesCheck = tubHes->addComponent<PackageChecker>(Paquete::Hestia);

	Entity* tubArt = addEntity();
	tubArt->addComponent<Transform>(660, 0, 100, 150);
	tubArt->addComponent<Trigger>();
	PackageChecker* artCheck = tubArt->addComponent<PackageChecker>(Paquete::Artemisa);
}
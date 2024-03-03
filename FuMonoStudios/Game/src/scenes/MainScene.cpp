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
#include "../components/PaqueteBuilder.h"
#include "../components/Herramientas.h"
#include "../components/MultipleTextures.h"
#include "../components/Gravity.h"
#include "../Time.h"


void ecs::MainScene::createManual()
{
	Entity* manual = addEntity(ecs::layer::MANUAL);
	Texture* manualTexture = &sdlutils().images().at("bookTest");
	Texture* manualTexture2 = &sdlutils().images().at("placeHolder");
	Texture* buttonTexture = &sdlutils().images().at("flechaTest");
	float scale = 0.075;
	Transform* manualTransform = manual->addComponent<Transform>(500.0f, 500.0f, manualTexture->width() * scale, manualTexture->height() * scale);
	manual->addComponent<Gravity>();
	RenderImage* manualRender = manual->addComponent<RenderImage>();
	manual->addComponent<DragAndDrop>();
	MultipleTextures* multTextures = manual->addComponent<MultipleTextures>();
	multTextures->addTexture(manualTexture);
	multTextures->addTexture(manualTexture2);
	multTextures->addTexture(buttonTexture);
	multTextures->initComponent();
	manualRender->setTexture(multTextures->getCurrentTexture());


	Entity* button = addEntity(ecs::layer::FOREGROUND);
	float buttonScale = 0.15;
	Transform* buttonTransform = button->addComponent<Transform>(400, 300, buttonTexture->width() * buttonScale, buttonTexture->height() * buttonScale);
	RenderImage* buttonRender = button->addComponent<RenderImage>(buttonTexture);
	buttonTransform->setParent(manualTransform);
	button->addComponent<Clickeable>();
	button->getComponent<Clickeable>()->addEvent([multTextures](Entity* e) {

		multTextures->nextTexture();
	});

	Entity* button2 = addEntity(ecs::layer::FOREGROUND);
	Transform* buttonTransform2 = button2->addComponent<Transform>(100, 300, buttonTexture->width() * buttonScale, buttonTexture->height() * buttonScale);
	RenderImage* buttonRender2 = button2->addComponent<RenderImage>(buttonTexture);
	buttonTransform2->setParent(manualTransform);
	button2->addComponent<Clickeable>();
	button2->getComponent<Clickeable>()->addEvent([multTextures](Entity* e) {

		multTextures->previousTexture();
	});

	
}

ecs::MainScene::MainScene():Scene(),fails(0),correct(0)
{

}

ecs::MainScene::~MainScene()
{
}

void ecs::MainScene::update()
{
	Scene::update();
	if(!timerPaused)
	{
		if (timer > 0) {
			timer -= Time::getDeltaTime();
			//std::cout << timer << std::endl;
		}
		else
			gm().requestChangeScene(ecs::sc::MAIN_SCENE, ecs::sc::MENU_SCENE);
	}
}

void ecs::MainScene::init()
{
	setTimer(10.0);
	timerPaused = false;

	std::cout << "Hola Main" << std::endl;
	sdlutils().clearRenderer(build_sdlcolor(0xFFFFFFFF));
	//crear objetos
	
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

	
	//TUBOS Demeter, Hefesto, Hestia, Artemisa, Hermes, Apolo, Poseidon, Erroneo

	float scaleTubos = 0.3f;
	Entity* tubDem = addEntity(ecs::layer::BACKGROUND);
	Texture* texturaDem = &sdlutils().images().at("tubo1");
	tubDem->addComponent<Transform>(120, -40, texturaDem->width() *scaleTubos, texturaDem->height()*scaleTubos);
	tubDem->addComponent<RenderImage>(texturaDem);
	Trigger* demTri = tubDem->addComponent<Trigger>();
	PackageChecker* demCheck = tubDem->addComponent<PackageChecker>(Paquete::Demeter);
	demTri->addCallback([this,demCheck](ecs::Entity* entRec) {
		if (entRec->getComponent<Paquete>() != nullptr) {
			if (demCheck->checkPackage(entRec->getComponent<Paquete>())) {
				std::cout << "the end is nigh\n";
				correct++;
			}
			else {
				std::cout << "NUH UH\n";
				fails++;
			}

		}
		else {
			std::cout << "eso no es un paquete gañan\n";
		}
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
	
	// Posici�n Relativa
	e->addChild(trSello);
	trSello->setRelativePos(100.0f, 100.0f);
}

void ecs::MainScene::createPaquete (int lv) {
	Entity* Paquet = addEntity ();
	Texture* texturaPaquet = &sdlutils ().images ().at ("boxTest");
	Transform* trPq = Paquet->addComponent<Transform> (700.0f, 700.0f, texturaPaquet->width () * 0.1, texturaPaquet->height () * 0.1);
	RenderImage* rd = Paquet->addComponent<RenderImage> (texturaPaquet);
	DragAndDrop* drgPq = Paquet->addComponent<DragAndDrop> ();
	Paquet->addComponent<Gravity> ();
	PaqueteBuilder a;
	a.PaqueteRND (lv, Paquet);
}

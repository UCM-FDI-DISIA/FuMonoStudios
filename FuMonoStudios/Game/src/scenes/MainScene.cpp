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
#include "../sistemas/PaqueteBuilder.h"
#include "../components/Herramientas.h"
#include "../components/MultipleTextures.h"
#include "../components/Gravity.h"
#include "../components/MoverTransform.h"
#include "../components/Time.h"
#include "../architecture/GameConstants.h"
#include "../components/SelfDestruct.h"
#include "../architecture/GeneralData.h"

ecs::MainScene::MainScene():Scene(),fails(0),correct(0), timerPaused(false), timerTexture(nullptr),timerEnt(nullptr)
{
	timeFont = new Font("recursos/fonts/ARIAL.ttf", 40);
	timer = MINIGAME_TIME;
}

ecs::MainScene::~MainScene()
{
}


void ecs::MainScene::update()
{
	Scene::update();
	if (!timerPaused)
	{
		if (timer > 0) {
			timer -= Time::getDeltaTime();
			updateTimer();
		}
		else
			gm().requestChangeScene(ecs::sc::MAIN_SCENE, ecs::sc::END_WORK_SCENE);
	}
}

void ecs::MainScene::init()
{
	std::cout << "Hola Main" << std::endl;
	sdlutils().clearRenderer(build_sdlcolor(0xFFFFFFFF));
	//crear objetos
	timer = MINIGAME_TIME;
	// Fondo
	Entity* Fondo = addEntity(ecs::layer::BACKGROUND);
	Fondo->addComponent<Transform>(0, 0, sdlutils().width(), sdlutils().height());
	Fondo->addComponent<RenderImage>(&sdlutils().images().at("fondoOficina"));

	createManual();

	initTexts();

	createPaquete(generalData().getPaqueteLevel());

	createTubo(Paquete::Hestia);
	createTubo(Paquete::Hefesto);
	createTubo(Paquete::Demeter);
	createTubo(Paquete::Artemisa);
	createTubo(Paquete::Hermes);
	createTubo(Paquete::Apolo);
	createTubo(Paquete::Poseidon);

	createSelladores();

	// papelera
	Entity* papelera = addEntity(ecs::layer::FOREGROUND);
	papelera->addComponent<Transform>(50, 650, 100, 150);
	papelera->addComponent<RenderImage>(&sdlutils().images().at("papelera"));
	Trigger* papTrig = papelera->addComponent<Trigger>();
	papTrig->addCallback([this](ecs::Entity* entRec) {
		Paquete* paqComp = entRec->getComponent<Paquete>();
		if (paqComp != nullptr)
		{
			if (paqComp->correcto())
			{
				generalData().wrongPackage();
				fails++;
			}
				
			else
			{ 
				generalData().correctPackage();
				correct++;
			}
				
			updateFailsText();
			entRec->setAlive(false);
			createPaquete(generalData().getPaqueteLevel());
		}
		});
}

void ecs::MainScene::createSelladores() {
	float scaleSelladores = 0.2f;

	// Sellador rojo (1)
	Entity* selloA = addEntity(layer::OFFICEELEMENTS);
	Texture* selloATex = &sdlutils().images().at("selladorA");
	Transform* selloATR = selloA->addComponent<Transform>(100, 300, selloATex->width(), selloATex->height());
	selloATR->setScale(scaleSelladores);
	selloA->addComponent<DragAndDrop>(true, [selloA]() {
		selloA->addComponent<MoverTransform>(Vector2D(100,300), 0.5, Easing::EaseOutCubic);
		});
	selloA->addComponent<RenderImage>(selloATex);
	Herramientas* herrSelladorA = selloA->addComponent<Herramientas>();
	herrSelladorA->setFunctionality(SelloCalleA);
	
	// Sellador azul (2)
	Entity* selloB = addEntity(layer::OFFICEELEMENTS);
	Texture* selloBTex = &sdlutils().images().at("selladorB");
	Transform* selloBTR = selloB->addComponent<Transform>(100, 410, selloBTex->width(), selloBTex->height());
	selloBTR->setScale(scaleSelladores);
	selloB->addComponent<DragAndDrop>(true, [selloB]() {
		selloB->addComponent<MoverTransform>(Vector2D(100, 410), 0.5, Easing::EaseOutCubic);
		});
	selloB->addComponent<RenderImage>(selloBTex);
	Herramientas* herrSelladorB = selloB->addComponent<Herramientas>();
	herrSelladorB->setFunctionality(SelloCalleB);

	// Sellador verde (3)
	Entity* selloC = addEntity(layer::OFFICEELEMENTS);
	Texture* selloCTex = &sdlutils().images().at("selladorC");
	Transform* selloCTR = selloC->addComponent<Transform>(100, 520, selloCTex->width(), selloCTex->height());
	selloCTR->setScale(scaleSelladores);
	selloC->addComponent<DragAndDrop>(true, [selloC]() {
		selloC->addComponent<MoverTransform>(Vector2D(100, 520), 0.5, Easing::EaseOutCubic);
		});
	selloC->addComponent<RenderImage>(selloCTex);
	Herramientas* herrSelladorC = selloC->addComponent<Herramientas>();
	herrSelladorC->setFunctionality(SelloCalleC);
}

void ecs::MainScene::createTubo(Paquete::Distrito dist) {
	float scaleTubos = 0.3f;
	
	Entity* tuboEnt = addEntity(ecs::layer::BACKGROUND);
	Texture* texTubo = &sdlutils().images().at("tubo" + std::to_string(dist + 1));
	Transform* tuboTr = tuboEnt->addComponent<Transform>(75 + (220 * dist), -40, texTubo->width(), texTubo->height());
	tuboTr->setScale(scaleTubos);
	tuboEnt->addComponent<RenderImage>(texTubo);
	Trigger* tuboTri = tuboEnt->addComponent<Trigger>();
	PackageChecker* tuboCheck = tuboEnt->addComponent<PackageChecker>(dist);
	tuboTri->addCallback([this, dist,tuboCheck](ecs::Entity* entRec) {
		//comprobamos si es un paquete
		Transform* entTr = entRec->getComponent<Transform>();
		if (entRec->getComponent<Paquete>() != nullptr) {
			if (tuboCheck->checkPackage(entRec->getComponent<Paquete>())) {
				entRec->removeComponent<Gravity>();
				entRec->addComponent<MoverTransform>( // animación básica del paquete llendose
					Vector2D(entTr->getPos().getX(), entTr->getPos().getY() - 600), 1.5, Easing::EaseOutCubic);
				entRec->addComponent<SelfDestruct>(1, [this]() {
					correct++;
					generalData().correctPackage();
					updateFailsText();
					createPaquete(0);
					});
			}
			else {
				entRec->removeComponent<Gravity>();
				entRec->addComponent<MoverTransform>( // animación básica del paquete llendose
					Vector2D(entTr->getPos().getX(), entTr->getPos().getY() - 600), 1.5, Easing::EaseOutCubic);
				entRec->addComponent<SelfDestruct>(1, [this]() {
					fails++;
					generalData().wrongPackage();
					updateFailsText();
					createPaquete(0);
					});
			}
			std::cout << "crazy! " << dist << std::endl;
		}
		});
}

void ecs::MainScene::createManual()
{
	Entity* manual = addEntity(ecs::layer::MANUAL);
	Texture* manualTexture = &sdlutils().images().at("book1");
	Texture* manualTexture2 = &sdlutils().images().at("book2");
	Texture* manualTexture3 = &sdlutils().images().at("book3");
	Texture* manualTexture4 = &sdlutils().images().at("book4");
	Texture* manualTexture5 = &sdlutils().images().at("book5");
	Texture* buttonTexture = &sdlutils().images().at("flechaTest");
	float scaleManual = 0.075;
	Transform* manualTransform = manual->addComponent<Transform>(500.0f, 500.0f, manualTexture->width(), manualTexture->height());
	manualTransform->setScale(scaleManual);
	manual->addComponent<Gravity>();
	RenderImage* manualRender = manual->addComponent<RenderImage>();
	manual->addComponent<DragAndDrop>(true);
	MultipleTextures* multTextures = manual->addComponent<MultipleTextures>();
	multTextures->addTexture(manualTexture);
	multTextures->addTexture(manualTexture2);
	multTextures->addTexture(manualTexture3);
	multTextures->addTexture(manualTexture4);
	multTextures->addTexture(manualTexture5);
	multTextures->initComponent();
	manualRender->setTexture(multTextures->getCurrentTexture());


	Entity* button = addEntity(ecs::layer::FOREGROUND);
	float buttonScale = 0.15;
	Transform* buttonTransform = button->addComponent<Transform>(400, 300, buttonTexture->width(), buttonTexture->height());
	buttonTransform->setScale(buttonScale);
	RenderImage* buttonRender = button->addComponent<RenderImage>(buttonTexture);
	buttonTransform->setParent(manualTransform);
	button->addComponent<Clickeable>();
	button->getComponent<Clickeable>()->addEvent([multTextures]() {

		multTextures->nextTexture();
		});

	Entity* button2 = addEntity(ecs::layer::FOREGROUND);
	Transform* buttonTransform2 = button2->addComponent<Transform>(100, 300, buttonTexture->width() * buttonScale, buttonTexture->height() * buttonScale);
	RenderImage* buttonRender2 = button2->addComponent<RenderImage>(buttonTexture);
	buttonTransform2->setParent(manualTransform);
	button2->addComponent<Clickeable>();
	button2->getComponent<Clickeable>()->addEvent([multTextures]() {

		multTextures->previousTexture();
		});
}

void ecs::MainScene::initTexts() {
	// inicializamos el timer
	timerEnt = addEntity(ecs::layer::UI);
	timerEnt->addComponent<Transform>(1250, 50, 200, 200);
	timerEnt->addComponent<RenderImage>();
	updateTimer();

	// creamos contador fallos y aciertos
	successEnt = addEntity(ecs::layer::UI);
	successEnt->addComponent<Transform>(1350, 250, 100, 100);
	successEnt->addComponent<RenderImage>();

	failsEnt = addEntity(ecs::layer::UI);
	failsEnt->addComponent<Transform>(1350, 350, 100, 100);
	failsEnt->addComponent<RenderImage>();

	updateFailsText();
}

void ecs::MainScene::updateTimer() {
	if (timerTexture != nullptr)
	{
		delete timerTexture;
		timerTexture = nullptr;
	}
		
	timerTexture = new Texture(sdlutils().renderer(), std::to_string((int)(timer)), *timeFont, build_sdlcolor(0x000000ff), 200);
	timerEnt->getComponent<RenderImage>()->setTexture(timerTexture);
}

void ecs::MainScene::updateFailsText() {
	if (successTexture != nullptr) {
		delete successTexture;
		successTexture = nullptr;
	}
	successTexture = new Texture(sdlutils().renderer(), "Aciertos: " + std::to_string(correct), *timeFont, build_sdlcolor(0x00ff00ff), 200);
	successEnt->getComponent<RenderImage>()->setTexture(successTexture);

	if (failsTexture != nullptr) {
		delete failsTexture;
		failsTexture = nullptr;
	}
	failsTexture = new Texture(sdlutils().renderer(), "Fallos: " + std::to_string(fails), *timeFont, build_sdlcolor(0xff0000ff), 200);
	failsEnt->getComponent<RenderImage>()->setTexture(failsTexture);
}

void ecs::MainScene::createPaquete (int lv) {
	float paqueteScale = 0.25f;
	Entity* paqEnt = addEntity (ecs::layer::PACKAGE);
	Texture* texturaPaquet = &sdlutils ().images ().at ("boxTest");
	Transform* trPq = paqEnt->addComponent<Transform> (1600.0f, 600.0f, texturaPaquet->width (), texturaPaquet->height ());
	trPq->setScale(paqueteScale);
	RenderImage* rd = paqEnt->addComponent<RenderImage> (texturaPaquet);
	paqEnt->addComponent<Gravity>();
	DragAndDrop* drgPq = paqEnt->addComponent<DragAndDrop>(true);
	PaqueteBuilder a;
	a.PaqueteRND (lv, paqEnt);

	// añadimos que pueda ser interactuado por selladores
	paqEnt->getComponent<Trigger>()->addCallback([paqEnt](ecs::Entity* entRec) {
		Herramientas* herrEnt = entRec->getComponent<Herramientas>();
		if (herrEnt != nullptr)
		{
			herrEnt->interact(paqEnt);
		}
		});

	paqEnt->addComponent<MoverTransform>(Vector2D(1200,600), 1, EaseOutBack);
}
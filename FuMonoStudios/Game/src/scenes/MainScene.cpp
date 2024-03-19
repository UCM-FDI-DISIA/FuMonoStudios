#include "MainScene.h"
#include "../architecture/Entity.h"
#include <iostream>
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/Render.h"
#include "../components/Clickeable.h"
#include "../components/DragAndDrop.h"
#include "../components/Trigger.h"
#include "../components/Wrap.h"
#include "../architecture/Game.h"
#include <string>
#include <list>
#include "../sdlutils/Texture.h"
#include "../components/PackageChecker.h"
#include "../sistemas/PaqueteBuilder.h"
#include "../components/Herramientas.h"
#include "../components/MultipleTextures.h"
#include "../components/Gravity.h"
#include "../components/MoverTransform.h"
#include "../architecture/Time.h"
#include "../architecture/GameConstants.h"
#include "../components/SelfDestruct.h"
#include "../architecture/GeneralData.h"
#include "../sistemas/ComonObjectsFactory.h"
#include "../components/Depth.h"

ecs::MainScene::MainScene():Scene(),fails_(0),correct_(0), timerPaused_(false), timerTexture_(nullptr),timerEnt_(nullptr)
{
	timeFont_ = new Font("recursos/fonts/ARIAL.ttf", 30);
	timer_ = MINIGAME_TIME;
}

ecs::MainScene::~MainScene()
{
}


void ecs::MainScene::update()
{
	Scene::update();
	if (!timerPaused_)
	{
		if (timer_ > 0) {
			timer_ -= Time::getDeltaTime();

			// actualizamos el timer 1 vez por seg
			//if (timer_ - int(timer_) < 0.007)
			updateTimer();

			std::cout << timer_ - int(timer_) << std::endl;
			minutes += timeMultiplier * 1;
			hours += timeMultiplier * 0.01666;
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
	timer_ = MINIGAME_TIME;
	// Fondo
	Entity* Fondo = addEntity(ecs::layer::BACKGROUND);
	Fondo->addComponent<Transform>(0, 0, sdlutils().width(), sdlutils().height());
	Fondo->addComponent<RenderImage>(&sdlutils().images().at("fondoOficina"));

	createManual();

	createClock();

	initTexts();

	createPaquete(generalData().getPaqueteLevel());

	for (int i = 0; i < 7; i++) {
		createTubo((Paquete::Distrito)i);
	}

	createSelladores();
  
  	//cinta envolver
	Entity* cinta = addEntity(ecs::layer::TAPE);
	cinta->addComponent<Transform>(560, 500, 100, 150);
	Texture* texturaCin = &sdlutils().images().at("cinta");
	RenderImage* rd = cinta->addComponent<RenderImage>(texturaCin);
	cinta->addComponent<Gravity>();
	cinta->addComponent<DragAndDrop>();

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
				fails_++;
			}
				
			else
			{ 
				generalData().correctPackage();
				correct_++;
			}
				
			updateFailsText();
			entRec->setAlive(false);
			createPaquete(generalData().getPaqueteLevel());
		}
		});
}

void ecs::MainScene::close() {
	ecs::Scene::close();
	generalData().updateMoney(correct_,fails_);
}

void ecs::MainScene::createClock() {
	Entity* clock = addEntity(layer::BACKGROUND);
	clock->addComponent<Transform>(1340, 510, 210, 140, 0);
	clock->addComponent<RenderImage>(&sdlutils().images().at("reloj"));
	clockCenter = clock->getComponent<Transform>()->getCenter();


	Entity* manecillaL = addEntity(layer::BACKGROUND);
	trManecillaL = manecillaL->addComponent<Transform>(1430, 555, 25, 40);
	manecillaL->addComponent<RenderImage>(&sdlutils().images().at("manecillaL"));

	Entity* manecillaS = addEntity(layer::BACKGROUND);
	trManecillaS = manecillaS->addComponent<Transform>(1435, 580, 25, 15, 0);
	manecillaS->addComponent<RenderImage>(&sdlutils().images().at("manecillaS"));
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
	Transform* selloCTR = selloC->addComponent<Transform>(100, 520, selloCTex->width()
, selloCTex->height());
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
			entRec->removeComponent<Gravity>();
			entRec->addComponent<MoverTransform>( // animación básica del paquete llendose
				entTr->getPos() + Vector2D(0, -600), 1.5, Easing::EaseOutCubic);
			entRec->addComponent<SelfDestruct>(1, [this]() {
				generalData().correctPackage();
				createPaquete(generalData().getPaqueteLevel());
				});
			if (tuboCheck->checkPackage(entRec->getComponent<Paquete>())) {
				correct_++;
			}
			else {
				fails_++;
			}
#ifdef _DEBUG
			updateFailsText();
#endif // _DEBUG

			std::cout << "crazy! " << dist << std::endl;
		}

		});
}

void ecs::MainScene::createManual()
{
	ComonObjectsFactory fact(this);
	Entity* manual = addEntity(ecs::layer::MANUAL);
	//se puede hacer un for
	Texture* manualTexture = &sdlutils().images().at("book1");
	Texture* manualTexture2 = &sdlutils().images().at("book2");
	Texture* manualTexture3 = &sdlutils().images().at("book3");
	Texture* manualTexture4 = &sdlutils().images().at("book4");
	Texture* manualTexture5 = &sdlutils().images().at("book5");
	Texture* buttonTexture = &sdlutils().images().at("flechaTest");

	std::vector<Texture*> bookTextures = {
		manualTexture,
		manualTexture2,
		manualTexture3,
		manualTexture4,
		manualTexture5
	};
	float scaleManual = 0.075;
	Transform* manualTransform = manual->addComponent<Transform>(500.0f, 500.0f, manualTexture->width(), manualTexture->height());
	manualTransform->setScale(scaleManual);
	RenderImage* manualRender = manual->addComponent<RenderImage>();
	manual->addComponent<Gravity>();
	manual->addComponent<DragAndDrop>(true);
	MultipleTextures* multTextures = manual->addComponent<MultipleTextures>(bookTextures);
	manualRender->setTexture(multTextures->getCurrentTexture());


	Vector2D buttonSize(100, 40);
	fact.setLayer(ecs::layer::FOREGROUND);

	auto next = [multTextures]() {multTextures->nextTexture();};
	auto right = fact.createImageButton(Vector2D(400, 300), buttonSize, buttonTexture, next);
	right->getComponent<Transform>()->setParent(manualTransform);

	auto previous = [multTextures]() {multTextures->previousTexture();};
	auto left = fact.createImageButton(Vector2D(100, 300), buttonSize, buttonTexture, previous);
	left->getComponent<Transform>()->setParent(manualTransform);

	manual->addComponent<Depth>();
}

void ecs::MainScene::initTexts() {
	// inicializamos el timer
	timerEnt_ = addEntity(ecs::layer::UI);
	timerEnt_->addComponent<Transform>(1250, 50, 200, 200);
	timerEnt_->addComponent<RenderImage>();
	updateTimer();
#ifdef _DEBUG


	// creamos contador fallos y aciertos
	successEnt_ = addEntity(ecs::layer::UI);
	successEnt_->addComponent<Transform>(1350, 250, 100, 100);
	successEnt_->addComponent<RenderImage>();

	failsEnt_ = addEntity(ecs::layer::UI);
	failsEnt_->addComponent<Transform>(1350, 350, 100, 100);
	failsEnt_->addComponent<RenderImage>();

	updateFailsText();
#endif // _DEBUG
}

void ecs::MainScene::updateTimer() {
	// numeros que aplicados hacen representar bien las horas y minutos
	float x = ((minutes - 15) / 9.55);
	float y = ((hours - 6) / 3.82);

	trManecillaL->setPos(clockCenter.getX() + offsetL.getX() + radiusManL * cos(x),
						clockCenter.getY() + offsetL.getY() + radiusManL * sin(x));
	trManecillaL->setRotation(90 + x * CONST_ROT);

	trManecillaS->setPos(clockCenter.getX() + offsetS.getX() + radiusManS * cos(y),
							clockCenter.getY() + offsetS.getY() + radiusManS * sin(y));
	trManecillaS->setRotation(y * CONST_ROT);

	//std::cout << "y: " << y << " x:" << x << std::endl;
	//std::cout << "horas " << hours << " minutes: " << minutes << std::endl;

	if (timerTexture_ != nullptr)
	{
		delete timerTexture_;
		timerTexture_ = nullptr;
	}
		
	timerTexture_ = new Texture(sdlutils().renderer(), std::to_string((int)(timer_)), *timeFont_, build_sdlcolor(0x000000ff), 200);
	timerEnt_->getComponent<RenderImage>()->setTexture(timerTexture_);
}

#ifdef _DEBUG
void ecs::MainScene::updateFailsText() {
	if (successTexture_ != nullptr) {
		delete successTexture_;
		successTexture_ = nullptr;
	}
	successTexture_ = new Texture(sdlutils().renderer(), "Aciertos: " + std::to_string(correct_), *timeFont_, build_sdlcolor(0x00ff00ff), 200);
	successEnt_->getComponent<RenderImage>()->setTexture(successTexture_);

	if (failsTexture_ != nullptr) {
		delete failsTexture_;
		failsTexture_ = nullptr;
	}
	failsTexture_ = new Texture(sdlutils().renderer(), "Fallos: " + std::to_string(fails_), *timeFont_, build_sdlcolor(0xff0000ff), 200);
	failsEnt_->getComponent<RenderImage>()->setTexture(failsTexture_);
}
#endif // _DEBUG

void ecs::MainScene::createPaquete (int lv) {
	float paqueteScale = 0.25f;
	Entity* paqEnt = addEntity (ecs::layer::PACKAGE);
	Texture* texturaPaquet = &sdlutils ().images ().at ("boxTest");

	Texture* texturaPaquet25 = &sdlutils().images().at("caja25");

	Texture* texturaPaquet50 = &sdlutils().images().at("caja50");

	Texture* texturaPaquet75 = &sdlutils().images().at("caja75");

	Texture* texturaPaquet100 = &sdlutils().images().at("caja100");

	Transform* trPq = paqEnt->addComponent<Transform> (1600.0f, 600.0f, texturaPaquet->width (), texturaPaquet->height ());
	trPq->setScale(paqueteScale);
	paqEnt->addComponent<Depth>();
	RenderImage* rd = paqEnt->addComponent<RenderImage> (texturaPaquet);
	paqEnt->addComponent<Gravity>();
	DragAndDrop* drgPq = paqEnt->addComponent<DragAndDrop>(true);
	std::list<int> route {pointRoute::LeftUp, pointRoute::MiddleUp, pointRoute::MiddleMid, pointRoute::MiddleDown, pointRoute::RightDown};

	MultipleTextures* multTexturesPaq = paqEnt->addComponent<MultipleTextures>();

	multTexturesPaq->addTexture(texturaPaquet);
	multTexturesPaq->addTexture(texturaPaquet25);
	multTexturesPaq->addTexture(texturaPaquet50);
	multTexturesPaq->addTexture(texturaPaquet75);
	multTexturesPaq->addTexture(texturaPaquet100);

	multTexturesPaq->initComponent();

	//Wrap debe ir despues del Transform, Trigger y Multitextures
	paqEnt->addComponent<Wrap>(20, 0, route);


	PaqueteBuilder a;
	a.paqueteRND (lv, paqEnt);

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
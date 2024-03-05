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
#include "../sistemas/PaqueteBuilder.h"
#include "../components/Herramientas.h"
#include "../components/MultipleTextures.h"
#include "../components/Gravity.h"
#include "../components/MoverTransform.h"
#include "../components/Time.h"
#include "../architecture/GameConstants.h"
#include "../components/SelfDestruct.h"

ecs::MainScene::MainScene():Scene(),fails(0),correct(0), timerPaused(false)
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
			gm().requestChangeScene(ecs::sc::MAIN_SCENE, ecs::sc::MENU_SCENE);
	}
}

void ecs::MainScene::init()
{
	std::cout << "Hola Main" << std::endl;
	sdlutils().clearRenderer(build_sdlcolor(0xFFFFFFFF));
	//crear objetos
	
	// Fondo
	Entity* Fondo = addEntity(ecs::layer::BACKGROUND);
	Fondo->addComponent<Transform>(0, 0, sdlutils().width(), sdlutils().height());
	Fondo->addComponent<RenderImage>(&sdlutils().images().at("fondoOficina"));

	createManual();

	initTexts();

	//Boton que genera Paquetes
	Texture* texturaBoton = &sdlutils ().images ().at ("press");
	Entity* BotonPress = addEntity ();
	Transform* transformBoton = BotonPress->addComponent<Transform> (0.0f, 500.0f, texturaBoton->width (), texturaBoton->height ());
	RenderImage* renderBoton = BotonPress->addComponent<RenderImage> (texturaBoton);
	auto clickerPress = BotonPress->addComponent<Clickeable> ();
	CallbackClickeable funcPress = [this]() {
		createPaquete(0);
		};
	clickerPress->addEvent(funcPress);
	
	
	//TUBOS Demeter, Hefesto, Hestia, Artemisa, Hermes, Apolo, Poseidon, Erroneo
	float scaleTubos = 0.3f;

	//TUBO DEMETER
	Entity* tubDem = addEntity(ecs::layer::BACKGROUND);
	Texture* texturaDem = &sdlutils().images().at("tubo1");
	tubDem->addComponent<Transform>(120, -40, texturaDem->width() *scaleTubos, texturaDem->height()*scaleTubos);
	tubDem->addComponent<RenderImage>(texturaDem);
	Trigger* demTri = tubDem->addComponent<Trigger>();
	PackageChecker* demCheck = tubDem->addComponent<PackageChecker>(Paquete::Demeter);
	// CALLBACK TUBO DEMETER
	demTri->addCallback([this,demCheck](ecs::Entity* entRec) {
		//comprobamos si es un paquete
		Transform* entTr = entRec->getComponent<Transform>();
		if (entRec->getComponent<Paquete>() != nullptr) {
			if (demCheck->checkPackage(entRec->getComponent<Paquete>())) {
				entRec->removeComponent<DragAndDrop>();
				entRec->removeComponent<Trigger>();
				entRec->removeComponent<Gravity>();
				entRec->addComponent<MoverTransform>( // animación básica del paquete llendose
					Vector2D(entTr->getPos().getX(), entTr->getPos().getY() + 300), 1, Easing::EaseOutCubic);
				correct++;
			}
			else {
				entRec->removeComponent<Gravity>();
				entRec->addComponent<MoverTransform>( // animación básica del paquete llendose
					Vector2D(entTr->getPos().getX(), entTr->getPos().getY() - 600), 1.5, Easing::EaseOutCubic);
				entRec->addComponent<SelfDestruct>(1, [this]() {
					fails++;
					updateFailsText();
					});
				
			}

		}
		});

	Entity* tubHef = addEntity();
	tubHef->addComponent<Transform>(340, 0, 100, 150);
	Trigger* hefTri = tubHef->addComponent<Trigger>();
	PackageChecker* hefCheck = tubHef->addComponent<PackageChecker>(Paquete::Hefesto);
	hefTri->addCallback([hefCheck](ecs::Entity* entRec) {
		if (entRec->getComponent<Paquete>() != nullptr) {
			if (hefCheck->checkPackage(entRec->getComponent<Paquete>())) {
				std::cout << "the end is a horse\n";
			}
			else {
				std::cout << "NUH UH2\n";
			}
		}
		else {
			//std::cout << "eso no es un paquete gañan\n";
		}
		});

	Entity* tubHes = addEntity();
	tubHes->addComponent<Transform>(560, 0, 100, 150);
	Trigger* hesTri = tubHes->addComponent<Trigger>();
	PackageChecker* hesCheck = tubHes->addComponent<PackageChecker>(Paquete::Hestia);
	hesTri->addCallback([hesCheck](ecs::Entity* entRec) {
		if (entRec->getComponent<Paquete>() != nullptr) {
			if (hesCheck->checkPackage(entRec->getComponent<Paquete>())) {
				std::cout << "egg is nigh\n";
			}
			else {
				std::cout << "NUH UH3\n";
			}
		}
		else {
			//std::cout << "eso no es un paquete gañan\n";
		}
		});

	Entity* tubArt = addEntity();
	tubArt->addComponent<Transform>(780, 0, 100, 150);
	Trigger* artTri = tubArt->addComponent<Trigger>();
	PackageChecker* artCheck = tubArt->addComponent<PackageChecker>(Paquete::Artemisa);
	artTri->addCallback([artCheck](ecs::Entity* entRec) {
		if (entRec->getComponent<Paquete>() != nullptr) {
			if (artCheck->checkPackage(entRec->getComponent<Paquete>())) {
				std::cout << "wacamole\n";
			}
			else {
				std::cout << "NUH UH4\n";
			}
		}
		else {
			//std::cout << "eso no es un paquete gañan\n";
		}
		});
	
}
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
	Transform* trPq = paqEnt->addComponent<Transform> (1600.0f, 600.0f, texturaPaquet->width () * paqueteScale, texturaPaquet->height () * paqueteScale);
	RenderImage* rd = paqEnt->addComponent<RenderImage> (texturaPaquet);
	paqEnt->addComponent<Gravity>();
	DragAndDrop* drgPq = paqEnt->addComponent<DragAndDrop>();
	PaqueteBuilder a;
	a.PaqueteRND (lv, paqEnt);

	paqEnt->addComponent<MoverTransform>(Vector2D(1200,600), 1, EaseOutBack);
}
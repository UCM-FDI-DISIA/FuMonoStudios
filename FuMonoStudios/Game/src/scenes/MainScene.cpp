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

ecs::MainScene::MainScene():Scene()
{
	
}

ecs::MainScene::~MainScene()
{
}

void ecs::MainScene::update()
{
	Scene::update();
	if (timer > 0) {
		timer -= Time::getDeltaTime();
		std::cout << timer << std::endl;
	}
}

void ecs::MainScene::init()
{
	std::cout << "Hola Main" << std::endl;
	sdlutils().clearRenderer(build_sdlcolor(0xFFFFFFFF));
	//crear objetos

	//Paquete de prueba (comentado, porque ahora hay un constructor de paquetes)
	/*
	Entity* Paquet = addEntity();
	Texture* texturaPaquet = &sdlutils().images().at("boxTest");
	Transform* trPq = Paquet->addComponent<Transform>(500.0f, 500.0f, texturaPaquet->width() * 0.1, texturaPaquet->height() * 0.1);
	RenderImage* rd = Paquet->addComponent<RenderImage>(texturaPaquet);
	Paquete* pqPq = Paquet->addComponent<Paquete>(Paquete::Demeter, Paquete::C1, Paquete::Alimento,
		true, Paquete::Bajo, 20, false, false);
	DragAndDrop* drgPq = Paquet->addComponent<DragAndDrop>();
	Paquet->addComponent<Gravity>();*/

	//createManual();

	//Boton que genera Paquetes
	Texture* texturaBoton = &sdlutils ().images ().at ("press");
	Entity* BotonPress = addEntity ();
	Transform* transformBoton = BotonPress->addComponent<Transform> (200.0f, 400.0f, texturaBoton->width (), texturaBoton->height ());
	RenderImage* renderBoton = BotonPress->addComponent<RenderImage> (texturaBoton);
	auto clickerPress = BotonPress->addComponent<Clickeable> ();
	Callback funcPress = [this](Entity* e) {
		createPaquete (0);
		};
	clickerPress->addEvent (funcPress);
	
	// Fondo
	Entity* Fondo = addEntity(ecs::layer::BACKGROUND);
	Fondo->addComponent<Transform>(0, 0, sdlutils().width(), sdlutils().height());
	Fondo->addComponent<RenderImage>(&sdlutils().images().at("fondoOficina"));

	createManual();

	//Paquete de prueba
	Entity* Paquet = addEntity();
	Texture* texturaPaquet = &sdlutils().images().at("boxTest");
	Transform* trPq = Paquet->addComponent<Transform>(500.0f, 500.0f, texturaPaquet->width() * 0.1, texturaPaquet->height() * 0.1);
	Paquet->addComponent<Gravity>();
	RenderImage* rd = Paquet->addComponent<RenderImage>(texturaPaquet);
	Paquete* pqPq = Paquet->addComponent<Paquete>(Paquete::Demeter, Paquete::C1, Paquete::Alimento,
		true, Paquete::Bajo, 20, false, false);
	DragAndDrop* drgPq = Paquet->addComponent<DragAndDrop>();
	

	

	

	
	//TUBOS Demeter, Hefesto, Hestia, Artemisa, Hermes, Apolo, Poseidon, Erroneo

	float scaleTubos = 0.3f;
	Entity* tubDem = addEntity(ecs::layer::BACKGROUND);
	Texture* texturaDem = &sdlutils().images().at("tubo1");
	tubDem->addComponent<Transform>(120, -40, texturaDem->width() *scaleTubos, texturaDem->height()*scaleTubos);
	tubDem->addComponent<RenderImage>(texturaDem);
	Trigger* demTri = tubDem->addComponent<Trigger>();
	PackageChecker* demCheck = tubDem->addComponent<PackageChecker>(Paquete::Demeter);
	demTri->addCallback([demCheck](ecs::Entity* entRec) {
		if (entRec->getComponent<Paquete>() != nullptr) {
			if (demCheck->checkPackage(entRec->getComponent<Paquete>())) {
				std::cout << "the end is nigh\n";
			}
			else {
				std::cout << "NUH UH\n";
			}

		}
		else {
			std::cout << "eso no es un paquete gañan\n";
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
				std::cout << "NUH UH\n";
			}
		}
		else {
			std::cout << "eso no es un paquete gañan\n";
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
				std::cout << "NUH UH\n";
			}
		}
		else {
			std::cout << "eso no es un paquete gañan\n";
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
				std::cout << "NUH UH\n";
			}
		}
		else {
			std::cout << "eso no es un paquete gañan\n";
		}
		});
	
}

void ecs::MainScene::createManual()
{
	Entity* manual = addEntity();
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
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
	button->getComponent<Clickeable>()->addEvent([patata]() {

		patata->nextTexture();
	});

	Entity* button2 = addEntity(ecs::layer::FOREGROUND);
	Transform* buttonTransform2 = button2->addComponent<Transform>(400, 300, buttonTexture->width() * buttonScale, buttonTexture->height() * buttonScale);
	RenderImage* buttonRender2 = button2->addComponent<RenderImage>(buttonTexture);
	buttonTransform2->setParent(manualTransform);
	button2->addComponent<Clickeable>();
	button2->getComponent<Clickeable>()->addEvent([patata]() {

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
	std::cout << "Hola Main"<<std::endl;
	sdlutils().clearRenderer(build_sdlcolor(0xFFFFFFFF));
	//crear objetos
	createManual();

	// Fondo
	Entity* Prueba2 = addEntity(ecs::layer::BACKGROUND);
	Prueba2->addComponent<Transform>(0, 0, sdlutils().width(), sdlutils().height());
	Prueba2->addComponent<RenderImage>(&sdlutils().images().at("fondoOficina"));
}


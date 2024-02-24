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

ecs::MainScene::MainScene():Scene()
{
	
}

ecs::MainScene::~MainScene()
{
}


void sellar() {
	std::cout << "fumas ganja";
}

void ecs::MainScene::init()
{
	std::cout << "Hola Main" << std::endl;
	sdlutils().clearRenderer(build_sdlcolor(0xFFFFFFFF));



}
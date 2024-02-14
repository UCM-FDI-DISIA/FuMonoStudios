#include "MainScene.h"
#include "../architecture/Entity.h"
#include <iostream>
#include "../sdlutils/SDLUtils.h"


ecs::MainScene::MainScene()
{
	Entity * obj = addEntity();
}

ecs::MainScene::~MainScene()
{
}

void ecs::MainScene::init()
{
	std::cout << "Hola Main"<<std::endl;
	sdlutils().clearRenderer(build_sdlcolor(0xFFFFFFFF));
	//crear objetos
}



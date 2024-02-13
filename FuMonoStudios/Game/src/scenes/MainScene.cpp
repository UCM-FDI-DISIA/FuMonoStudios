#include "MainScene.h"
#include "../architecture/Entity.h"
#include <iostream>
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"


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
	Entity* Prueba = addEntity();
	Transform* wakamole = Prueba->addComponent<Transform>(ecs::cmp::TRANSFORM, 10.0f, 10.0f, 200.0f, 100.0f);
}



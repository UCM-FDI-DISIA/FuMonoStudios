#include "ExplorationScene.h"

ecs::ExplorationScene::ExplorationScene()
{
}

ecs::ExplorationScene::~ExplorationScene()
{
}

void ecs::ExplorationScene::init()
{
	std::cout << "Hola Exploracion"<<std::endl;
	sdlutils().clearRenderer();
}

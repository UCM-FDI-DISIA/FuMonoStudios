#include "ExplorationScene.h"
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
#include "../components/DialogComponent.h"

ecs::ExplorationScene::ExplorationScene() :Scene(), map(this)
{
}

ecs::ExplorationScene::~ExplorationScene()
{
}

void ecs::ExplorationScene::init()
{
	std::cout << "Hola Exploracion" << std::endl;
}

void ecs::ExplorationScene::render()
{
	map.renderBackGround();
	Scene::render();
}

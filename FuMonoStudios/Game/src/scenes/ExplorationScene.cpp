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

ecs::ExplorationScene::ExplorationScene():Scene(), dialogMngr_()
{
	dialogMngr_.setDialogues("resources/dialogos/dialogo.txt");
}

ecs::ExplorationScene::~ExplorationScene()
{
}

void ecs::ExplorationScene::init()
{
	std::cout << "Hola Exploracion"<<std::endl;
	sdlutils().clearRenderer();
	auto boxBg = addEntity();
	auto bgTr = boxBg->addComponent<Transform>(100, sdlutils().height() - 200, sdlutils().width()-200, 200);
	boxBg->addComponent<RenderImage>(&sdlutils().images().at("placeHolder"));

	auto dialogoBox = addEntity();
	auto textTr = dialogoBox->addComponent<Transform>(20, 20,100,100);
	textTr->setParent(bgTr);
	dialogoBox->addComponent<RenderImage>();
	dialogoBox->addComponent<DialogComponent>(&dialogMngr_);
}

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
	Font fuente("resources/fonts/ARIAL.ttf", 40);

	Texture* muchoTexto = new Texture(sdlutils().renderer(), dialogMngr_.GetCurrentDialog(), fuente, build_sdlcolor(0xffffffffff), sdlutils().width()-200);
	auto dialogoBox = addEntity();
	auto textTr = dialogoBox->addComponent<Transform>(100, sdlutils().height()-200, muchoTexto->width(), 100);
	dialogoBox->addComponent<RenderImage>(muchoTexto);
	dialogoBox->addComponent<DialogComponent>(&dialogMngr_);
}

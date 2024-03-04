#include "EndWorkScene.h"
#include "../architecture/GeneralData.h"
#include "../architecture/Entity.h"
#include <string>
#include "../components/Transform.h"
#include "../components/Render.h"
EndWorkScene::EndWorkScene():Scene() {

}

EndWorkScene::~EndWorkScene() {

}


void EndWorkScene::init() {
	Font* fuente = new Font("recursos/fonts/ARIAL.ttf", 70);
	std::string msg = "Money: ";
	msg += std::to_string(GeneralData::instance()->getMoney());
	Texture* text = new Texture(sdlutils().renderer(), msg, *fuente, build_sdlcolor(0x000000ffff));
	auto dineros = addEntity();
	auto tr = dineros->addComponent<Transform>(0,0,text->width(),text->height());
	auto rend = dineros->addComponent<RenderImage>(text);
}
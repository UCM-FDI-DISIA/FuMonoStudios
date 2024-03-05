#include "EndWorkScene.h"
#include "../architecture/GeneralData.h"
#include "../architecture/Entity.h"
#include <string>
#include "../components/Transform.h"
#include "../components/Render.h"
#include "../sistemas/ComonObjectsFactory.h"
#include "../components/Paquete.h"
EndWorkScene::EndWorkScene():Scene() {

}

EndWorkScene::~EndWorkScene() {

}


void EndWorkScene::init() {
	ComonObjectsFactory objs;
	std::string msg = "Money: ";
	msg += std::to_string(GeneralData::instance()->getMoney());
	Vector2D pos(sdlutils().width()/2, sdlutils().height()-100);
	Vector2D dist(0, -300);
	objs.createLabel(this,pos, msg, 50);
	objs.createLabel(this, pos + dist, "Fails:", 50);
	objs.createLabel(this, pos + dist*2, "Corrects:", 50);
}
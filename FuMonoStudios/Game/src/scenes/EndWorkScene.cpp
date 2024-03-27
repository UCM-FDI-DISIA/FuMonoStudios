#include "EndWorkScene.h"
#include "../architecture/GeneralData.h"
#include "../architecture/Entity.h"
#include <string>
#include "../components/Transform.h"
#include "../components/Render.h"
#include "../sistemas/ComonObjectsFactory.h"
#include "../components/Paquete.h"
#include "../components/Clickeable.h"
#include "../architecture/Game.h"
EndWorkScene::EndWorkScene():Scene() {

}

EndWorkScene::~EndWorkScene() {

}


void EndWorkScene::init() {
	//generalData().updateMoney();
	std::string msg = "Money: ";
	msg += std::to_string(generalData().getMoney());
	Vector2D pos(sdlutils().width()/2, sdlutils().height()-400);
	Vector2D dist(0, -300);
	factory_->setLayer(ecs::layer::UI); 
	factory_->createLabel(pos, msg, 50);
	factory_->createLabel(pos + dist, "Fails: " + std::to_string(generalData().getFails()), 50);
	factory_->createLabel(pos + Vector2D(0, -400), "Corrects: " + std::to_string(generalData().getFails()), 50);
	auto call = []() {gm().requestChangeScene(ecs::sc::END_WORK_SCENE, ecs::sc::MENU_SCENE); };
	factory_->createTextuButton(pos + Vector2D(0, 70), "Return To menu", 50,call);
	generalData().resetFailsCorrects();
}
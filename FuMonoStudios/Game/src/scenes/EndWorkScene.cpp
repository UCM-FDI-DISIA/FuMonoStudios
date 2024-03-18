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
	font_ = new Font("recursos/fonts/ChocolateBold.ttf", 80);
}

EndWorkScene::~EndWorkScene() {
	delete font_;
}


void EndWorkScene::init() {
	//generalData().updateMoney();
	
	// Imagen recibo
	ecs::Entity* recibo = addEntity(ecs::layer::UI);
	Texture* reciboTex = &sdlutils().images().at("Recibo");
	Transform* reciboTR = recibo->addComponent<Transform>(sdlutils().width()/2 - reciboTex->height()/2,
		sdlutils().height() / 2 - reciboTex->height() / 2,
		reciboTex->width(), reciboTex->height());
	recibo->addComponent<RenderImage>(reciboTex);

	ComonObjectsFactory objs(this);

	objs.setLayer(ecs::layer::UI2); 

	Vector2D pos(sdlutils().width() / 2, sdlutils().height() - 230);

	Texture* moneyTex = new Texture(sdlutils().renderer(), std::to_string(generalData().getMoney()) + " $", *font_, build_sdlcolor(0x363740ff), 200);
	objs.createImage(pos, moneyTex);

	Texture* failsTex = new Texture(sdlutils().renderer(), "Fails: " + std::to_string(generalData().getFails()), *font_, build_sdlcolor(0x363740ff), 200);
	objs.createImage(pos + Vector2D(-200, -230), failsTex);

	Texture* correctTex = new Texture(sdlutils().renderer(), "Corrects: " + std::to_string(generalData().getCorrects()), *font_, build_sdlcolor(0x363740ff), 300);
	objs.createImage(pos + Vector2D(-200, -330), correctTex);

		auto call = []() {gm().requestChangeScene(ecs::sc::END_WORK_SCENE, ecs::sc::MENU_SCENE); };
	objs.createTextuButton(pos + Vector2D(340, 100), "Return To menu", 50,call);
	generalData().resetFailsCorrects();

}
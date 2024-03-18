#include "ConfigScene.h"
#include "../architecture/Entity.h"
#include <iostream>
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/Render.h"
#include "../components/Clickeable.h"
#include "../architecture/Game.h"
#include <string>
#include "../architecture/GeneralData.h"

//ecs::MainMenu::MainMenu()
//{
//	init();
//}

ecs::ConfigScene::ConfigScene() : Scene() {

}

ecs::ConfigScene::~ConfigScene()
{
}

void ecs::ConfigScene::init()
{
	std::cout << "Hola Config" << std::endl;
	sdlutils().clearRenderer();

	//Font* fuente = new Font("recursos/fonts/ARIAL.ttf", 50);

	Texture* texturaBoton = new Texture(sdlutils().renderer(), "Pulsa para volver al menu", sdlutils().fonts().at("arial50"), build_sdlcolor(0x000000ff));
	Entity* BotonPress = addEntity();

	Transform* transformBoton = BotonPress->addComponent<Transform>(400, 400, texturaBoton->width(), texturaBoton->height());
	RenderImage* renderBoton = BotonPress->addComponent<RenderImage>(texturaBoton);

	auto clickerPress = BotonPress->addComponent<Clickeable>();

	CallbackClickeable funcPress = [this]() {
		gm().requestChangeScene(ecs::sc::CONFIG_SCENE, ecs::sc::MENU_SCENE);

	};
	clickerPress->addEvent(funcPress);
	//Luis: esto que sea place holder hay que poner imagen
	// Texturas botones - y +
	Texture* texturaBoton2 = new Texture(sdlutils().renderer(), "(-)", sdlutils().fonts().at("arial50"), build_sdlcolor(0x000000ff));
	Texture* texturaBoton3 = new Texture(sdlutils().renderer(), "(+)", sdlutils().fonts().at("arial50"), build_sdlcolor(0x000000ff));

	// Boton cambio de pantalla
	screenModeTexture_ = new Texture(sdlutils().renderer(), "Cambiar modo de ventana", sdlutils().fonts().at("arial50"), build_sdlcolor(0x000000ff));
	screenModeEnt_ = addEntity();

	Transform* transformScreenMode = screenModeEnt_->addComponent<Transform>(500, 700, screenModeTexture_->width(), screenModeTexture_->height());
	RenderImage* renderScreenMode = screenModeEnt_->addComponent<RenderImage>(screenModeTexture_);

	auto clickerSecreenModeBoton = screenModeEnt_->addComponent<Clickeable>();

	CallbackClickeable funcScreenModeBoton = [this]() {
		sdlutils().toggleFullScreen();
	};
	clickerSecreenModeBoton->addEvent(funcScreenModeBoton);

	// Parametro de audio
	audioValueTexture_ = new Texture(sdlutils().renderer(), std::to_string(generalData().getParam(1)), sdlutils().fonts().at("arial50"), build_sdlcolor(0x000000ff));
	audioValueEnt_ = addEntity();

	Transform* transformAudioValue = audioValueEnt_->addComponent<Transform>(500, 600, audioValueTexture_->width(), audioValueTexture_->height());
	RenderImage* renderAudioValue = audioValueEnt_->addComponent<RenderImage>(audioValueTexture_);

	

	// Boton (-) para el parametro de audio
	Entity* BotonPress2 = addEntity();

	Transform* transformBoton2 = BotonPress2->addComponent<Transform>(400, 600, texturaBoton2->width(), texturaBoton2->height());
	RenderImage* renderBoton2 = BotonPress2->addComponent<RenderImage>(texturaBoton2);

	auto clickerPress2 = BotonPress2->addComponent<Clickeable>();

	CallbackClickeable funcPress2 = [this]() {
		generalData().changeParamID(1, false);
		//updateValue(audioValueTexture_, audioValueEnt_, 1);
		if (audioValueTexture_ != nullptr)
		{
			delete audioValueTexture_;
			audioValueTexture_ = nullptr;
		}

		audioValueTexture_ = new Texture(sdlutils().renderer(), std::to_string(generalData().getParam(1)), sdlutils().fonts().at("arial50"), build_sdlcolor(0x000000ff));
		audioValueEnt_->getComponent<RenderImage>()->setTexture(audioValueTexture_);

	};
	clickerPress2->addEvent(funcPress2);

	// Boton (+) para el parametro de audio
	Entity* BotonPress3 = addEntity();

	Transform* transformBoton3 = BotonPress3->addComponent<Transform>(600, 600, texturaBoton3->width(), texturaBoton3->height());
	RenderImage* renderBoton3 = BotonPress3->addComponent<RenderImage>(texturaBoton3);

	auto clickerPress3 = BotonPress3->addComponent<Clickeable>();

	CallbackClickeable funcPress3 = [this]() {
		generalData().changeParamID(1, true);
		//updateValue(audioValueTexture_, audioValueEnt_, 1);
		if (audioValueTexture_ != nullptr)
		{
			delete audioValueTexture_;
			audioValueTexture_ = nullptr;
		}

		audioValueTexture_ = new Texture(sdlutils().renderer(), std::to_string(generalData().getParam(1)), sdlutils().fonts().at("arial50"), build_sdlcolor(0x000000ff));
		audioValueEnt_->getComponent<RenderImage>()->setTexture(audioValueTexture_);
	};
	clickerPress3->addEvent(funcPress3);
}

//No usar de momento este método porque peta el programa aunque tenga la misma función que lo que pasa en los callbacks
void ecs::ConfigScene::updateValue(Texture* texture, Entity* entity, int index) {

	if (texture != nullptr)
	{
		delete texture;
		texture = nullptr;
	}

	texture = new Texture(sdlutils().renderer(), std::to_string(generalData().getParam(index)), sdlutils().fonts().at("arial50"), build_sdlcolor(0x000000ff));
	entity->getComponent<RenderImage>()->setTexture(texture);
}
//LUIS: Y si esto fuera un return to scene ????
void ecs::ConfigScene::changeToMenuScene() {

	//game().loadScene(ecs::sc::MAIN_SCENE);

}


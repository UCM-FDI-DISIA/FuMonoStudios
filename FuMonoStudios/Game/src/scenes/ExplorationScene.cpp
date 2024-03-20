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
#include "../sistemas/ComonObjectsFactory.h"

ecs::ExplorationScene::ExplorationScene() :Scene()
{

	dialogMngr_.setDialogues("recursos/dialogos/dialogo.txt");
	initPlacesDefaultMap();
	initDirectionsDefaultMap();
	actualPlace_ = &hestia;
	navigate("Hestia");
	createObjects("Hestia");
	rect_ = build_sdlrect(0, 0, sdlutils().width(), sdlutils().height());

}

ecs::ExplorationScene::~ExplorationScene()
{

}

void ecs::ExplorationScene::init()
{
	std::cout << "Hola Exploracion" << std::endl;
}

void ecs::ExplorationScene::initPlacesDefaultMap()
{
	//Demeter
	demeter = Lugar(&sdlutils().images().at("demeter"), true);

	//Hefesto
	hefesto = Lugar(&sdlutils().images().at("hefesto"), true);

	//Hestia
	hestia = Lugar(&sdlutils().images().at("hestia"), true);

	//Artemisa
	artemisa = Lugar(&sdlutils().images().at("artemisa"), true);

	//Hermes
	hermes = Lugar(&sdlutils().images().at("hermes"), false);

	//Apolo
	apolo = Lugar(&sdlutils().images().at("apolo"), false);

	//Posidon
	poseidon = Lugar(&sdlutils().images().at("poseidon"), false);
}

void ecs::ExplorationScene::initDirectionsDefaultMap()
{
	//demeter
	demeter.addDirections("Hermes", &hermes);
	demeter.addDirections("Hefesto", &hefesto);
	demeter.addDirections("Artemisa", &artemisa);

	//Hefesto
	hefesto.addDirections("Demeter", &demeter);
	hefesto.addDirections("Hestia", &hestia);
	hefesto.addDirections("Hermes", &hermes);

	//Hestia
	hestia.addDirections("Hefesto", &hefesto);
	hestia.addDirections("Artemisa", &artemisa);

	//Artemisa
	artemisa.addDirections("Demeter", &demeter);
	artemisa.addDirections("Hestia", &hestia);

	//hermes
	hermes.addDirections("Demeter", &demeter);
	hermes.addDirections("Hefesto", &hefesto);
	hermes.addDirections("Apolo", &apolo);

	//apolo
	apolo.addDirections("Hermes", &hermes);
	apolo.addDirections("Poseidon", &poseidon);

	//Poseidon
	poseidon.addDirections("Apolo", &apolo);
}

void ecs::ExplorationScene::render()
{
	actualPlace_->getTexture()->render(rect_);
	Scene::render();
}

void ecs::ExplorationScene::update() {
	Scene::update();

	if (!placeToGo.empty()) {

		int size = placeToGo.size();

		for (int i = 0; i < size; ++i) {
			navigate(placeToGo[i]);
			createObjects(placeToGo[i]);
			placeToGo.clear();
		}
		
	}
	
}

void ecs::ExplorationScene::navigate(std::string placeDir) // otro string sin const
{
	if (actualPlace_->navigate(placeDir))
		actualPlace_ = actualPlace_->getPlaceFromDirection(placeDir);
}

ecs::Entity* ecs::ExplorationScene::createNavegationsArrows(float x, float y, std::string placeDir, float scale)
{
	//para crear la flecha a hefesto

	ComonObjectsFactory factory(this);
	factory.setLayer(ecs::layer::FOREGROUND);
	Vector2D pos{ x, y };
	Texture* sujetaplazas = &sdlutils().images().at("cartel");
	Vector2D size{ sujetaplazas->width() * scale, sujetaplazas->height() * scale };
	
	CallbackClickeable cosa = [this, placeDir]() {
		if (actualPlace_->navigate(placeDir)) {
			actualPlace_->killObjects();
			placeToGo.push_back(placeDir);
			
		}
	};

	ecs::Entity* Arrow = factory.createImageButton(pos, size, sujetaplazas, cosa);

	factory.setLayer(ecs::layer::DEFAULT);
	
	return Arrow;

}

ecs::Entity* ecs::ExplorationScene::createCharacter(float x, float y, std::string character, float scale) {

	// Para Dani: El Personaje PlaceHolder que te he creado se compone del bot�n de press que al pulsarse te crea
// la caja de fondo y te empieza a renderizar el texto (ojo: si lo pulsas varias veces creas varias, esto lo puedes 
// solucionar sacando las entidades de box al h y comprobando si punteros a entidad son null o con un booleano que
// haga de flag)

// Para Dani: Aqu� le hacemos clickable y le ponemos como callback el m�todo funcPress

	ComonObjectsFactory factory(this);

	Vector2D pos{ x, y };
	Texture* texturaBoton = &sdlutils().images().at(character);
	Vector2D size{ texturaBoton->width() * scale, texturaBoton->height() * scale };
	
	CallbackClickeable funcPress = [this]() {
		//Esto ser�a la caja del fondo (lo de SDL que se ve)
		ecs::Entity* boxBg = addEntity();
		auto bgTr = boxBg->addComponent<Transform>(100, sdlutils().height() - 250, sdlutils().width() - 200, 200);
		boxBg->addComponent<RenderImage>(&sdlutils().images().at("cuadroDialogo"));
		actualPlace_->addObjects(boxBg);

		//Aqu� pillar�a el di�logo con el manager y crear�a la entidad que lo renderiza
		ecs::Entity* dialogoBox = addEntity();
		auto textTr = dialogoBox->addComponent<Transform>(80, 55, 100, 100);
		textTr->setParent(bgTr);
		dialogoBox->addComponent<RenderImage>();
		dialogoBox->addComponent<DialogComponent>(&dialogMngr_);
		actualPlace_->addObjects(dialogoBox);
	};

	ecs::Entity* BotonPress = factory.createImageButton(pos, size, textureCharacter, funcPress);
	
	return BotonPress;
}

void ecs::ExplorationScene::createObjects(std::string place) {

	if (place == "Demeter") {
		demeter.addObjects(createNavegationsArrows(100, 100, "Hefesto", 0.5));
		demeter.addObjects(createNavegationsArrows(700, 100, "Hermes", 0.5));
		demeter.addObjects(createNavegationsArrows(1300, 100, "Artemisa", 0.5));
		demeter.addObjects(createCharacter(300, 300, "pancracio", 0.25));


		//boton ir a trabajar
		ecs::Entity* botonTrabajar = addEntity();
		botonTrabajar->addComponent<Transform>(500, 500, 200, 100);
		botonTrabajar->addComponent<RenderImage>(&sdlutils().images().at("botonTrabajar"));
		auto clickableBotonTrabajar = botonTrabajar->addComponent<Clickeable>();
		CallbackClickeable funcPress = [this]() {
			gm().requestChangeScene(ecs::sc::EXPLORE_SCENE, ecs::sc::MAIN_SCENE);
		};
		clickableBotonTrabajar->addEvent(funcPress);
		demeter.addObjects(botonTrabajar);
	}
	else if (place == "Hefesto")
	{
		hefesto.addObjects(createNavegationsArrows(100, 100, "Hestia", 0.5));
		hefesto.addObjects(createNavegationsArrows(1300, 100, "Demeter", 0.5));
		hefesto.addObjects(createCharacter(300, 300, "paulino", 0.25));
	}
	else if (place == "Hestia") {
		hestia.addObjects(createNavegationsArrows(100, 100, "Artemisa", 0.5));
		hestia.addObjects(createNavegationsArrows(1300, 100, "Hefesto", 0.5));
		hestia.addObjects(createCharacter(300, 300, "anemos", 0.25));
	}
	else if (place == "Artemisa") {
		artemisa.addObjects(createNavegationsArrows(100, 100, "Demeter", 0.5));
		artemisa.addObjects(createNavegationsArrows(1300, 100, "Hestia", 0.5));
		artemisa.addObjects(createCharacter(300, 300, "abigail", 0.25));
	}
	else if (place == "Hermes") {
		hermes.addObjects(createNavegationsArrows(100, 100, "Hefesto", 0.5));
		hermes.addObjects(createNavegationsArrows(700, 100, "Apolo", 0.5));
		hermes.addObjects(createNavegationsArrows(1300, 100, "Demeter", 0.5));
	}
	else if (place == "Apolo") {
		apolo.addObjects(createNavegationsArrows(100, 100, "Poseidon", 0.5));
		apolo.addObjects(createNavegationsArrows(1300, 100, "Hermes", 0.5));
		apolo.addObjects(createCharacter(300, 300, "Soldado", 0.25));
	}
	else if (place == "Poseidon") {
		poseidon.addObjects(createNavegationsArrows(700, 100, "Apolo", 0.5));
		poseidon.addObjects(createCharacter(300, 300, "gargafiel", 0.25));
	}
}

//LUGAR__________________________________________________________________________________________

void ecs::Lugar::addDirections(std::string placeDir, Lugar* place)
{
	directions_[placeDir] = place;
}

bool ecs::Lugar::navigate(std::string placeDir)
{
	return directions_.count(placeDir) && directions_.at(placeDir)->navegable_;
}

ecs::Lugar* ecs::Lugar::getPlaceFromDirection(std::string placeDir)
{
	return directions_[placeDir];
}

void ecs::Lugar::killObjects()
{
	for (auto& e : ents_) {
		e->setAlive(false);
	}
	ents_.clear();
}

void ecs::Lugar::addObjects(ecs::Entity* e)
{
	ents_.push_back(e);
}



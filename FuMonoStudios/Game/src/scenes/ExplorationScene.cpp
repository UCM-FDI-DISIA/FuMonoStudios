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
#include "../architecture/Config.h"
#include <string>
#include "../sdlutils/Texture.h"
#include "../components/DialogComponent.h"
#include "../sistemas/ComonObjectsFactory.h"
#include "../architecture/GeneralData.h"
#include "../components/DelayedCallback.h"

ecs::ExplorationScene::ExplorationScene() :Scene()
{
	initPlacesDefaultMap();
	initDirectionsDefaultMap();
	actualPlace_ = &hestia;
	navigate("Hestia");
	createObjects("Hestia");
	rect_ = build_sdlrect(0, 0, sdlutils().width() / 1.25, sdlutils().height() / 1.25);
	canStartConversation = true;
	generalData().setDayData();
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
	hermes = Lugar(&sdlutils().images().at("hermes"), true);

	//Apolo
	apolo = Lugar(&sdlutils().images().at("apolo"), true);

	//Posidon
	poseidon = Lugar(&sdlutils().images().at("poseidon"), true);
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

ecs::Entity* ecs::ExplorationScene::createNavegationsArrows(Vector2D pos, std::string placeDir, float scale)
{
	//para crear la flecha a hefesto

	ComonObjectsFactory factory(this);
	factory.setLayer(ecs::layer::FOREGROUND);
	Texture* sujetaplazas = &sdlutils().images().at("cartel");
	Vector2D size{ sujetaplazas->width() * scale, sujetaplazas->height() * scale };
	
	CallbackClickeable cosa = [this, placeDir]() {
		if (actualPlace_->navigate(placeDir)) {
			closeConversation();
			actualPlace_->killObjects();
			placeToGo.push_back(placeDir);
			
		}
	};

	ecs::Entity* Arrow = factory.createImageButton(pos, size, sujetaplazas, cosa);

	factory.setLayer(ecs::layer::DEFAULT);
	
	return Arrow;

}

ecs::Entity* ecs::ExplorationScene::createCharacter(Vector2D pos, const std::string& character, float scale) {

	ComonObjectsFactory factory(this);

	Texture* texturaBoton = &sdlutils().images().at(character);
	Vector2D size{ texturaBoton->width() * scale, texturaBoton->height() * scale };
	
	// al pulsar sale el dialogo
	CallbackClickeable funcPress = [this, character]() {

		if (canStartConversation)
		{
			canStartConversation = false;

			boxBackground->setActive(true);

			// activamos los dialogos correspondientes
			std::pair<const std::string, int> aux = generalData().getNPCData(
				generalData().stringToPersonaje(character))->getDialogueInfo();

			dialogMngr_.setDialogues(generalData().stringToPersonaje(character), aux.first, aux.second);

			textDialogue->addComponent<DialogComponent>(&dialogMngr_, this);
		}
	};

	ecs::Entity* BotonPress = factory.createImageButton(pos, size, texturaBoton, funcPress);
	
	return BotonPress;
}

void ecs::ExplorationScene::createObjects(std::string place) {

	auto& pl = config().places();

	if (place == "Demeter") {

		for (int i = 0; i < pl.at(place).myArrows.size(); ++i) {

			demeter.addObjects(createNavegationsArrows(pl.at(place).myArrows[i].pos,
				pl.at(place).myArrows[i].destination_, pl.at(place).myArrows[i].scale_));


		}

		for (int i = 0; i < pl.at(place).myCharacters.size(); ++i) {

			demeter.addObjects(createCharacter(pl.at(place).myCharacters[i].pos,
				pl.at(place).myCharacters[i].name_, pl.at(place).myCharacters[i].scale_));


		}
	}
	else if (place == "Hefesto")
	{
		for (int i = 0; i < pl.at(place).myArrows.size(); ++i) {

			hefesto.addObjects(createNavegationsArrows(pl.at(place).myArrows[i].pos,
				pl.at(place).myArrows[i].destination_, pl.at(place).myArrows[i].scale_));


		}

		for (int i = 0; i < pl.at(place).myCharacters.size(); ++i) {

			hefesto.addObjects(createCharacter(pl.at(place).myCharacters[i].pos,
				pl.at(place).myCharacters[i].name_, pl.at(place).myCharacters[i].scale_));


		}
	}
	else if (place == "Hestia") {
		for (int i = 0; i < pl.at(place).myArrows.size(); ++i) {

			hestia.addObjects(createNavegationsArrows(pl.at(place).myArrows[i].pos,
				pl.at(place).myArrows[i].destination_, pl.at(place).myArrows[i].scale_));


		}

		for (int i = 0; i < pl.at(place).myCharacters.size(); ++i) {

			hestia.addObjects(createCharacter(pl.at(place).myCharacters[i].pos,
				pl.at(place).myCharacters[i].name_, pl.at(place).myCharacters[i].scale_));


		}


		//boton ir a trabajar
		ecs::Entity* botonTrabajar = addEntity();
		botonTrabajar->addComponent<Transform>(525, 300, 100, 300);
		auto clickableBotonTrabajar = botonTrabajar->addComponent<Clickeable>();
		CallbackClickeable funcPress = [this]() {
			gm().requestChangeScene(ecs::sc::EXPLORE_SCENE, ecs::sc::MAIN_SCENE);
		};
		clickableBotonTrabajar->addEvent(funcPress);
		demeter.addObjects(botonTrabajar);
	}
	else if (place == "Artemisa") {
		for (int i = 0; i < pl.at(place).myArrows.size(); ++i) {

			artemisa.addObjects(createNavegationsArrows(pl.at(place).myArrows[i].pos,
				pl.at(place).myArrows[i].destination_, pl.at(place).myArrows[i].scale_));


		}

		for (int i = 0; i < pl.at(place).myCharacters.size(); ++i) {

			artemisa.addObjects(createCharacter(pl.at(place).myCharacters[i].pos,
				pl.at(place).myCharacters[i].name_, pl.at(place).myCharacters[i].scale_));


		}
	}
	else if (place == "Hermes") {
		for (int i = 0; i < pl.at(place).myArrows.size(); ++i) {

			hermes.addObjects(createNavegationsArrows(pl.at(place).myArrows[i].pos,
				pl.at(place).myArrows[i].destination_, pl.at(place).myArrows[i].scale_));


		}

		for (int i = 0; i < pl.at(place).myCharacters.size(); ++i) {

			hermes.addObjects(createCharacter(pl.at(place).myCharacters[i].pos,
				pl.at(place).myCharacters[i].name_, pl.at(place).myCharacters[i].scale_));


		}
	}
	else if (place == "Apolo") {
		for (int i = 0; i < pl.at(place).myArrows.size(); ++i) {

			apolo.addObjects(createNavegationsArrows(pl.at(place).myArrows[i].pos,
				pl.at(place).myArrows[i].destination_, pl.at(place).myArrows[i].scale_));


		}

		for (int i = 0; i < pl.at(place).myCharacters.size(); ++i) {

			apolo.addObjects(createCharacter(pl.at(place).myCharacters[i].pos,
				pl.at(place).myCharacters[i].name_, pl.at(place).myCharacters[i].scale_));


		}
	}
	else if (place == "Poseidon") {
		for (int i = 0; i < pl.at(place).myArrows.size(); ++i) {

			poseidon.addObjects(createNavegationsArrows(pl.at(place).myArrows[i].pos,
				pl.at(place).myArrows[i].destination_, pl.at(place).myArrows[i].scale_));


		}

		for (int i = 0; i < pl.at(place).myCharacters.size(); ++i) {

			poseidon.addObjects(createCharacter(pl.at(place).myCharacters[i].pos,
				pl.at(place).myCharacters[i].name_, pl.at(place).myCharacters[i].scale_));


		}
	}

	// creamos la entidad caja dialogo
	boxBackground = addEntity();
	auto bgTr = boxBackground->addComponent<Transform>(100, sdlutils().height() - 250, sdlutils().width() - 200, 200);
	boxBackground->addComponent<RenderImage>(&sdlutils().images().at("cuadroDialogo"));

	// entidad del texto
	textDialogue = addEntity();
	auto textTr = textDialogue->addComponent<Transform>(100, 100, 80, 100);
	textTr->setParent(bgTr);
	textDialogue->addComponent<RenderImage>();

	boxBackground->setActive(false);
}

void ecs::ExplorationScene::closeConversation() {
	textDialogue->getComponent<RenderImage>()->setTexture(nullptr);
	textDialogue->removeComponent<DialogComponent>();
	boxBackground->setActive(false);
	textDialogue->addComponent<DelayedCallback>(0.1, [this]() {
		canStartConversation = true;
		});
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



#include "Mapa.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Render.h"
#include "../components/Clickeable.h"
#include "../components/DialogComponent.h"
#include "../components/Transform.h"
#include "../architecture/Game.h"



Mapa::Mapa(ecs::Scene* e) : mScene_(e), dialogMngr_()
{
	//dialogMngr_.setDialogues("recursos/dialogos/npc_mayores.json", "vagabundo", "presentacion", "jaja");
	initPlacesDefaultMap();
	initDirectionsDefaultMap();
	actualPlace_ = &demeter;
	navigate("Demeter");
	createObjects("Demeter");
	rect_ = build_sdlrect(0, 0, sdlutils().width() / 2, sdlutils().height() / 2);
}

ecs::Entity* Mapa::createNavegationsArrows(int x, int y, std::string placeDir)
{
	//para crear la flecha a hefesto
	ecs::Entity* Arrow = mScene_->addEntity(ecs::layer::FOREGROUND);
	Texture* sujetaplazas = &sdlutils().images().at("cartel");
	float scale = 0.5;
	Transform* e = Arrow->addComponent<Transform>(x,y, sujetaplazas->width() * scale, sujetaplazas->height() * scale);
	RenderImage* nachos = Arrow->addComponent<RenderImage>(sujetaplazas);
	auto clicker = Arrow->addComponent<Clickeable>();
	CallbackClickeable cosa = [this, placeDir]() {
		if (actualPlace_->navigate(placeDir)) {
			actualPlace_->killObjects();
			navigate(placeDir);
			createObjects(placeDir);
		}
	};
	clicker->addEvent(cosa);
	return Arrow;
}

ecs::Entity* Mapa::createCharacter(int x, int y,std::string character) {

	// Para Dani: El Personaje PlaceHolder que te he creado se compone del botón de press que al pulsarse te crea
// la caja de fondo y te empieza a renderizar el texto (ojo: si lo pulsas varias veces creas varias, esto lo puedes 
// solucionar sacando las entidades de box al h y comprobando si punteros a entidad son null o con un booleano que
// haga de flag)

// Para Dani: Aquí le hacemos clickable y le ponemos como callback el método funcPress
	ecs::Entity* BotonPress = mScene_->addEntity();
	Texture* texturaBoton = &sdlutils().images().at(character);
	Transform* transformBoton = BotonPress->addComponent<Transform>(260.0f, 400.0f, texturaBoton->width() * 0.25, texturaBoton->height() * 0.25);
	RenderImage* renderBoton = BotonPress->addComponent<RenderImage>(texturaBoton);
	auto clickerPress = BotonPress->addComponent<Clickeable>();
	CallbackClickeable funcPress = [this]() {
		//Esto sería la caja del fondo (lo de SDL que se ve)
		ecs::Entity* boxBg = mScene_->addEntity();
		auto bgTr = boxBg->addComponent<Transform>(100, sdlutils().height() - 250, sdlutils().width() - 200, 200);
		boxBg->addComponent<RenderImage>(&sdlutils().images().at("cuadroDialogo"));
		actualPlace_->addObjects(boxBg);

		//Aquí pillaría el diálogo con el manager y crearía la entidad que lo renderiza
		ecs::Entity* dialogoBox = mScene_->addEntity();
		auto textTr = dialogoBox->addComponent<Transform>(80, 55, 100, 100);
		textTr->setParent(bgTr);
		dialogoBox->addComponent<RenderImage>();
		//dialogoBox->addComponent<DialogComponent>(&dialogMngr_);
		actualPlace_->addObjects(dialogoBox);
		};
	clickerPress->addEvent(funcPress);
	return BotonPress;
}

void Mapa::initPlacesDefaultMap()
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

void Mapa::initDirectionsDefaultMap()
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
	artemisa.addDirections("Demeter",&demeter);
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

void Mapa::navigate(std::string placeDir) // otro string sin const
{
	if (actualPlace_->navigate(placeDir))
		actualPlace_ = actualPlace_->getPlaceFromDirection(placeDir);
}

void Mapa::renderBackGround() const
{
	actualPlace_->getTexture()->render(rect_);
}

void Mapa::killObjects()
{
	
}

void Mapa::createObjects(std::string place) {

	if (place == "Demeter") {
		demeter.addObjects(createNavegationsArrows(100,100,"Hefesto"));
		demeter.addObjects(createNavegationsArrows(700, 100, "Hermes"));
		demeter.addObjects(createNavegationsArrows(1300, 100, "Artemisa"));
		demeter.addObjects(createCharacter(300, 300, "pancracio"));


		//boton ir a trabajar
		ecs::Entity* botonTrabajar = mScene_->addEntity();
		botonTrabajar->addComponent<Transform>(500, 500, 200, 100);
		botonTrabajar->addComponent<RenderImage>(&sdlutils().images().at("botonTrabajar"));
		auto clickableBotonTrabajar = botonTrabajar->addComponent<Clickeable>();
		CallbackClickeable funcPress = [this]() {
			gm().requestChangeScene(ecs::sc::EXPLORE_SCENE, ecs::sc::MAIN_SCENE);
			};
		clickableBotonTrabajar->addEvent(funcPress);
		demeter.addObjects(botonTrabajar);
	}
	else if(place == "Hefesto")
	{
		hefesto.addObjects(createNavegationsArrows(100, 100, "Hestia"));
		hefesto.addObjects(createNavegationsArrows(1300, 100, "Demeter"));
		hefesto.addObjects(createCharacter(300, 300, "paulino"));
	}
	else if (place == "Hestia") {
		hestia.addObjects(createNavegationsArrows(100, 100, "Artemisa"));
		hestia.addObjects(createNavegationsArrows(1300, 100, "Hefesto"));
		hestia.addObjects(createCharacter(300, 300, "anemos"));
	}
	else if (place == "Artemisa") {
		artemisa.addObjects(createNavegationsArrows(100, 100, "Demeter"));
		artemisa.addObjects(createNavegationsArrows(1300, 100, "Hestia"));
		artemisa.addObjects(createCharacter(300, 300, "abigail"));
	}
	else if (place == "Hermes") {
		hermes.addObjects(createNavegationsArrows(100, 100, "Hefesto"));
		hermes.addObjects(createNavegationsArrows(700, 100, "Apolo"));
		hermes.addObjects(createNavegationsArrows(1300, 100, "Demeter"));
	}
	else if (place == "Apolo") {
		apolo.addObjects(createNavegationsArrows(100, 100, "Poseidon"));
		apolo.addObjects(createNavegationsArrows(1300, 100, "Hermes"));
		apolo.addObjects(createCharacter(300, 300, "Soldado"));
	}
	else if (place == "Poseidon") {
		poseidon.addObjects(createNavegationsArrows(700, 100, "Apolo"));
		poseidon.addObjects(createCharacter(300, 300, "gargafiel"));
	}
}

void Lugar::addDirections(std::string placeDir, Lugar* place)
{
	directions_[placeDir] = place;
}

bool Lugar::navigate(std::string placeDir)
{
	return directions_.count(placeDir) && directions_.at(placeDir)->navegable_;
}

Lugar* Lugar::getPlaceFromDirection(std::string placeDir)
{
	return directions_[placeDir];
}

void Lugar::killObjects()
{
	for (auto& e : ents_) {
		e->setAlive(false);
	}
	ents_.clear();
}

void Lugar::addObjects(ecs::Entity* e)
{
	ents_.push_back(e);
}

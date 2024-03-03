#include "Mapa.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Render.h"
#include "../components/Clickeable.h"
#include "Transform.h"



Mapa::Mapa(ecs::Scene* e) : mScene(e)
{
	initPlacesDefaultMap();
	initDirectionsDefaultMap();
	actualPlace = &demeter;
	createObjects("Demeter");
	rect = build_sdlrect(0, 0, sdlutils().width(), sdlutils().height());
}

ecs::Entity* Mapa::createNavegationsArrows(int x, int y, std::string placeDir)
{
	//para crear la flecha a hefesto
	ecs::Entity* Arrow = mScene->addEntity();
	Texture* sujetaplazas = &sdlutils().images().at("boxTest");
	float scale = 0.2;
	Transform* e = Arrow->addComponent<Transform>(x,y, sujetaplazas->width() * scale, sujetaplazas->height() * scale);
	RenderImage* nachos = Arrow->addComponent<RenderImage>(sujetaplazas);
	auto clicker = Arrow->addComponent<Clickeable>();
	CallbackClickeable cosa = [this, placeDir]() {
		if (actualPlace->navigate(placeDir)) {
			actualPlace->killObjects();
			navigate(placeDir);
			createObjects(placeDir);
			sdlutils().clearRenderer();
		}
	};
	clicker->addEvent(cosa);
	return Arrow;
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

void Mapa::navigate(std::string placeDir)
{
	if (actualPlace->navigate(placeDir))
		actualPlace = actualPlace->getPlaceFromDirection(placeDir);
}

void Mapa::renderBackGround() const
{
	actualPlace->getTexture()->render(rect);
}

void Mapa::killObjects()
{
	
}

void Mapa::createObjects(std::string place) {

	if (place == "Demeter") {
		demeter.addObjects(createNavegationsArrows(100,100,"Hefesto"));
		demeter.addObjects(createNavegationsArrows(700, 100, "Hermes"));
		demeter.addObjects(createNavegationsArrows(1300, 100, "Artemisa"));
	}
	else if(place == "Hefesto")
	{
		hefesto.addObjects(createNavegationsArrows(100, 100, "Hestia"));
		hefesto.addObjects(createNavegationsArrows(1300, 100, "Demeter"));
	}
	else if (place == "Hestia") {
		hestia.addObjects(createNavegationsArrows(100, 100, "Artemisa"));
		hestia.addObjects(createNavegationsArrows(1300, 100, "Hefesto"));
	}
	else if (place == "Artemisa") {
		artemisa.addObjects(createNavegationsArrows(100, 100, "Demeter"));
		artemisa.addObjects(createNavegationsArrows(1300, 100, "Hestia"));
	}
	else if (place == "Hermes") {
		hermes.addObjects(createNavegationsArrows(100, 100, "Hefesto"));
		hermes.addObjects(createNavegationsArrows(700, 100, "Apolo"));
		hermes.addObjects(createNavegationsArrows(1300, 100, "Demeter"));
	}
	else if (place == "Apolo") {
		apolo.addObjects(createNavegationsArrows(100, 100, "Poseidon"));
		apolo.addObjects(createNavegationsArrows(1300, 100, "Hermes"));
	}
	else if (place == "Poseidon") {
		poseidon.addObjects(createNavegationsArrows(700, 100, "Apolo"));
	}
}

void Lugar::addDirections(std::string placeDir, Lugar* place)
{
	directions[placeDir] = place;
}

bool Lugar::navigate(std::string placeDir)
{
	return directions.count(placeDir) && directions.at(placeDir)->navegable;
}

Lugar* Lugar::getPlaceFromDirection(std::string placeDir)
{
	return directions[placeDir];
}

void Lugar::killObjects()
{
	for (auto e : ents) {
		e->setAlive(false);
	}
	ents.clear();
}

void Lugar::addObjects(ecs::Entity* e)
{
	ents.push_back(e);
}

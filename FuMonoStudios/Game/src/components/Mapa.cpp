#include "Mapa.h"
#include "../sdlutils/SDLUtils.h"

Mapa::Mapa()
{
	initPlacesDefaultMap();
	initDirectionsDefaultMap();
	actualPlace = &demeter;
	rect = build_sdlrect(0, 0, sdlutils().width(), sdlutils().height());
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
	demeter.addDirections("Hermes", hermes);
	demeter.addDirections("Hefesto", hefesto);
	demeter.addDirections("Artemisa", artemisa);

	//Hefesto
	hefesto.addDirections("Demeter", demeter);
	hefesto.addDirections("Hestia", hestia);
	hefesto.addDirections("Hermes", hermes);

	//Hestia
	hestia.addDirections("Hefesto", hefesto);
	hestia.addDirections("Artemisa", artemisa);

	//Artemisa
	artemisa.addDirections("Demeter", demeter);
	artemisa.addDirections("Hestia", hestia);

	//hermes
	hermes.addDirections("demeter", demeter);
	hermes.addDirections("Hefesto", hefesto);
	hermes.addDirections("Apolo", apolo);

	//apolo
	apolo.addDirections("Hermes", hermes);
	apolo.addDirections("Poseidon", poseidon);

	//Poseidon
	poseidon.addDirections("Apolo", apolo);
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

void Lugar::addDirections(std::string placeDir, Lugar place)
{
	directions[placeDir] = place;
}

bool Lugar::navigate(std::string placeDir)
{
	return directions.count(placeDir) && directions.at(placeDir).navegable;
}

Lugar* Lugar::getPlaceFromDirection(std::string placeDir)
{
	return &directions[placeDir];
}
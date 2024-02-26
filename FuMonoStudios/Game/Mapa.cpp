#include "Mapa.h"
#include "src/sdlutils/SDLUtils.h"

Mapa::Mapa()
{
	initPlacesDefaultMap();
	initDirectionsDefaultMap();
	actualPlace = &demeter;
}

Mapa::~Mapa()
{
	//if(actualPlace != nullptr)
		//delete actualPlace;
}


void Mapa::initPlacesDefaultMap()
{
	//Demeter
	Texture* demeterTexture = &sdlutils().images().at("demeter");
	demeter = Lugar(demeterTexture, true);

	//Hefesto
	Texture* hefestoTexture = &sdlutils().images().at("hefesto");
	hefesto = Lugar(hefestoTexture, true);


	//Hestia
	Texture* hestiaTexture = &sdlutils().images().at("hestia");
	hestia = Lugar(hestiaTexture, true);

	//Artemisa
	Texture* artemisaTexture = &sdlutils().images().at("artemisa");
	artemisa = Lugar(artemisaTexture, true);

	//Hermes
	Texture* hermesTexture = &sdlutils().images().at("hermes");
	hermes = Lugar(hermesTexture, false /*hermesCharacter*/);

	//Apolo
	Texture* apoloTexture = &sdlutils().images().at("apolo");
	apolo = Lugar(apoloTexture, false);

	//Posidon
	Texture* poseidonTexture = &sdlutils().images().at("poseidon");
	poseidon = Lugar(poseidonTexture, false);
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
			actualPlace = actualPlace->getDirection(placeDir);
}

void Mapa::render() const
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

Lugar* Lugar::getDirection(std::string placeDir)
{
	return &directions[placeDir];
}

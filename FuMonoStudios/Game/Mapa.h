#pragma once
#include "src/sdlutils/Texture.h"
#include <unordered_map>

struct Lugar {
private:
	Texture* backGround;
	bool navegable;
	//Character* character;
	std::unordered_map<std::string,Lugar> directions;

public:
	Lugar() {};
	Lugar(Texture* t, bool n /*Character* c*/) : backGround(t), navegable(n) /*character(c)*/ {};
	//~Lugar() { if(backGround != nullptr) delete backGround; };
	void addDirections(std::string placeDir, Lugar place);
	bool navigate(std::string placeDir);
	Lugar* getDirection(std::string placeDir);
	Texture* getTexture() const { return backGround; };
};
class Mapa
{
private:

	Lugar* actualPlace;

	//Luego haré un vector y un enum
	Lugar demeter;
	Lugar hefesto;
	Lugar hestia;
	Lugar artemisa;
	Lugar hermes;
	Lugar apolo;
	Lugar poseidon;

	void initPlacesDefaultMap();
	void initDirectionsDefaultMap();

	SDL_Rect rect = build_sdlrect(0, 0, 600, 800);

public:
	Mapa();
	~Mapa();
	void navigate(std::string placeDir);
	void render() const;
};


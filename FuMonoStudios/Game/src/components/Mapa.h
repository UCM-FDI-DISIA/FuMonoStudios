#pragma once
#include "../sdlutils/Texture.h"
#include <unordered_map>
/// <summary>
/// Struct que guarda la informaci�n de cada lugar, tiene el fondo a renderizar, un booleano para saber si se 
/// puedenavegar a �l, un mapa con las direcciones que conectan a �l (a las que no tiene por qu� poder navegarse)
/// Tiene m�todos para a�adir direcciones al lugar (necesita un string y una instancia de lugar), un booleano
/// que indica si cierto lugar (indicado con el string del mapa) es navegable, un getPlaceFromDirection 
/// que devuelve un puntero apuntando la posici�n de memoria de un lugar del mapa de direcciones (se usa para 
/// moverte por el mapa) y un getTexture (se usa para renderizar el background en el mapa).
/// No hay destructora porque no se genera nueva memoria din�mica.
/// </summary>
struct Lugar {
public:
	//Puntero a la textura del fondo
	Texture* backGround;

	//Bool que permite la navegaci�n
	bool navegable;

	//Mapa con las direcciones adyacentes al lugar (a las que no tiene por qu� poderse navegar)
	std::unordered_map<std::string,Lugar> directions;

	//constructoras
	Lugar() {};
	Lugar(Texture* t, bool n /*Character* c*/) : backGround(t), navegable(n) /*character(c)*/ {};

	/// <summary>
	/// M�todo para a�adir direcciones al mapa del lugar
	/// </summary>
	/// <param name="placeDir"></param>
	/// <param name="place"></param>
	void addDirections(std::string placeDir, Lugar place);

	/// <summary>
	/// M�todo para comprobar la navegabilidad a ciero lugar
	/// </summary>
	/// <param name="placeDir"></param>
	/// <returns></returns>
	bool navigate(std::string placeDir);

	/// <summary>
	/// M�todo para obtener la direcci�n de memoria de un lugar del mapa de direcciones (se usa para navegar)
	/// </summary>
	Lugar* getPlaceFromDirection(std::string placeDir);
	/// <summary>
	/// M�todo que devuelve la textura del fondo para poder renderizarla
	/// </summary>
	/// <returns></returns>
	Texture* getTexture() const { return backGround; };
};

/// <summary>
/// Clase que encapsula los lugares y se usa como sistema de navegaci�n.
/// La parte privada de la clase incluye un rect para el BackGround,
/// todos los lugares cargados en variables junto a un puntero apuntando a la posici�n de memoria del lugar
///	actual, y dos m�todos para inicializar los lugares y sus direcciones (podiciones adyacentes a las que no 
/// necesariamente se puede navegar).
/// Como m�todos p�blicos tenemos la constructora que inicializa toda la informaci�n del mapa, un m�todo 
/// navigate que comprueba si se puede navegar desde el lugar actual al indicado con el string que le pasas, si 
/// es posible la navgaci�n navegas al lugar, por �ltimo est� el m�todo renderBackGround que renderiza el fondo,
/// No hay destructora porque no se genera nueva memoria din�mica.
/// </summary>
class Mapa
{
private:
	//Puntero al lugar actual
	Lugar* actualPlace;

	//Luego har� un vector y un enum, son los lugares
	Lugar demeter;
	Lugar hefesto;
	Lugar hestia;
	Lugar artemisa;
	Lugar hermes;
	Lugar apolo;
	Lugar poseidon;
	
	/// <summary>
	/// M�todo para inicializar los lugares del mapa
	/// </summary>
	void initPlacesDefaultMap();
	/// <summary>
	/// M�todo para incializar las direcciones adyacentes a cada lugar del mapa
	/// </summary>
	void initDirectionsDefaultMap();

	//rect para renderizar el BackGround
	SDL_Rect rect;

public:
	//constructora
	Mapa();
	/// <summary>
	/// M�todo para navegar a cierto lugar
	/// </summary>
	void navigate(std::string placeDir);

	/// <summary>
	/// M�todo para renderizar el backGround
	/// </summary>
	void renderBackGround() const;

	//TODO: hacer lugares activables de forma din�mica
};
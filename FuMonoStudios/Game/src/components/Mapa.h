#pragma once
#include "../sdlutils/Texture.h"
#include <unordered_map>
/// <summary>
/// Struct que guarda la información de cada lugar, tiene el fondo a renderizar, un booleano para saber si se 
/// puedenavegar a él, un mapa con las direcciones que conectan a él (a las que no tiene por qué poder navegarse)
/// Tiene métodos para añadir direcciones al lugar (necesita un string y una instancia de lugar), un booleano
/// que indica si cierto lugar (indicado con el string del mapa) es navegable, un getPlaceFromDirection 
/// que devuelve un puntero apuntando la posición de memoria de un lugar del mapa de direcciones (se usa para 
/// moverte por el mapa) y un getTexture (se usa para renderizar el background en el mapa).
/// No hay destructora porque no se genera nueva memoria dinámica.
/// </summary>
struct Lugar {
public:
	//Puntero a la textura del fondo
	Texture* backGround;

	//Bool que permite la navegación
	bool navegable;

	//Mapa con las direcciones adyacentes al lugar (a las que no tiene por qué poderse navegar)
	std::unordered_map<std::string,Lugar> directions;

	//constructoras
	Lugar() {};
	Lugar(Texture* t, bool n /*Character* c*/) : backGround(t), navegable(n) /*character(c)*/ {};

	/// <summary>
	/// Método para añadir direcciones al mapa del lugar
	/// </summary>
	/// <param name="placeDir"></param>
	/// <param name="place"></param>
	void addDirections(std::string placeDir, Lugar place);

	/// <summary>
	/// Método para comprobar la navegabilidad a ciero lugar
	/// </summary>
	/// <param name="placeDir"></param>
	/// <returns></returns>
	bool navigate(std::string placeDir);

	/// <summary>
	/// Método para obtener la dirección de memoria de un lugar del mapa de direcciones (se usa para navegar)
	/// </summary>
	Lugar* getPlaceFromDirection(std::string placeDir);
	/// <summary>
	/// Método que devuelve la textura del fondo para poder renderizarla
	/// </summary>
	/// <returns></returns>
	Texture* getTexture() const { return backGround; };
};

/// <summary>
/// Clase que encapsula los lugares y se usa como sistema de navegación.
/// La parte privada de la clase incluye un rect para el BackGround,
/// todos los lugares cargados en variables junto a un puntero apuntando a la posición de memoria del lugar
///	actual, y dos métodos para inicializar los lugares y sus direcciones (podiciones adyacentes a las que no 
/// necesariamente se puede navegar).
/// Como métodos públicos tenemos la constructora que inicializa toda la información del mapa, un método 
/// navigate que comprueba si se puede navegar desde el lugar actual al indicado con el string que le pasas, si 
/// es posible la navgación navegas al lugar, por último está el método renderBackGround que renderiza el fondo,
/// No hay destructora porque no se genera nueva memoria dinámica.
/// </summary>
class Mapa
{
private:
	//Puntero al lugar actual
	Lugar* actualPlace;

	//Luego haré un vector y un enum, son los lugares
	Lugar demeter;
	Lugar hefesto;
	Lugar hestia;
	Lugar artemisa;
	Lugar hermes;
	Lugar apolo;
	Lugar poseidon;
	
	/// <summary>
	/// Método para inicializar los lugares del mapa
	/// </summary>
	void initPlacesDefaultMap();
	/// <summary>
	/// Método para incializar las direcciones adyacentes a cada lugar del mapa
	/// </summary>
	void initDirectionsDefaultMap();

	//rect para renderizar el BackGround
	SDL_Rect rect;

public:
	//constructora
	Mapa();
	/// <summary>
	/// Método para navegar a cierto lugar
	/// </summary>
	void navigate(std::string placeDir);

	/// <summary>
	/// Método para renderizar el backGround
	/// </summary>
	void renderBackGround() const;

	//TODO: hacer lugares activables de forma dinámica
};
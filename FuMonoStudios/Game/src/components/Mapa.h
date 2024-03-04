#pragma once
#include "../sdlutils/Texture.h"
#include "../architecture/ecs.h";
#include "../architecture/Entity.h"
#include "../architecture/Scene.h"
#include "Dialog_Manager.h"
#include <unordered_map>
#include <vector>
#include <array>
class DialogManager;
/// <summary>
/// Struct que guarda la información de cada lugar, tiene el fondo a renderizar, un booleano para saber si se 
/// puedenavegar a él, un mapa con las direcciones que conectan a él (a las que no tiene por qué poder navegarse),
/// y una lista de punteros a las entidades propias del lugar (perosonajes y flechas de movimiento) 
/// Tiene métodos para añadir direcciones al lugar (necesita un string y una instancia de lugar), un booleano
/// que indica si cierto lugar (indicado con el string del mapa) es navegable, un getPlaceFromDirection 
/// que devuelve un puntero apuntando la posición de memoria de un lugar del mapa de direcciones (se usa para 
/// moverte por el mapa) y un getTexture (se usa para renderizar el background en el mapa).
/// No hay destructora porque no se genera nueva memoria dinámica.
/// </summary>
struct Lugar {
private:
	//Puntero a la textura del fondo
	Texture* backGround;

	//Bool que permite la navegación
	bool navegable;

	//Mapa con las direcciones adyacentes al lugar (a las que no tiene por qué poderse navegar)
	std::unordered_map<std::string,Lugar*> directions;

	// Las entidades del lugar se almacenan como las de la escena, en vectores de objetos organizados en layouts
	std::vector<ecs::Entity*> ents;

public:
	//constructoras
	Lugar(): ents(){};
	Lugar(Texture* t, bool n) : ents(), backGround(t), navegable(n) /*character(c)*/ {};

	/// <summary>
	/// Método para añadir direcciones al mapa del lugar
	/// </summary>
	/// <param name="placeDir"></param>
	/// <param name="place"></param>
	void addDirections(std::string placeDir, Lugar* place);

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

	/// <summary>
	/// Mata (setAlive(false) los objetos del lugar para que se borren de la escena y los borra del vector
	/// del lugar.
	/// USAR ANTES DE NAVEGAR SI ES QUE SE PUEDE NAVEGAR
	/// </summary>
	void killObjects();

	/// <summary>
	/// Crea los objetos del lugar acatual al que te acabas de mover.
	/// USAR DESPUÉS DE HABER NAVEGADO
	/// </summary>
	void addObjects(ecs::Entity* e);
};

/// <summary>
/// Clase que encapsula los lugares y se usa como sistema de navegación.
/// La parte privada de la clase incluye un rect para el BackGround,
/// todos los lugares cargados en variables junto a un puntero apuntando a la posición de memoria del lugar
///	actual, dos métodos para inicializar los lugares y sus direcciones (podiciones adyacentes a las que no 
/// necesariamente se puede navegar) y otros dos métodos para gestionar las entidades del lugar en el que 
/// te encuentras.
/// Como métodos públicos tenemos la constructora que inicializa toda la información del mapa, un método 
/// navigate que comprueba si se puede navegar desde el lugar actual al indicado con el string que le pasas, si 
/// es posible la navgación navegas al lugar, por último está el método renderBackGround que renderiza el fondo,
/// No hay destructora porque no se genera nueva memoria dinámica.
/// </summary>
class Mapa
{
private:
	ecs::Scene* mScene;

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

	DialogManager dialogMngr_;

	/// <summary>
	/// Mata (setAlive(false) los objetos del lugar para que se borren de la escena y los borra del vector
	/// del lugar.
	/// USAR ANTES DE NAVEGAR SI ES QUE SE PUEDE NAVEGAR
	/// </summary>
	void killObjects();

	/// <summary>
	/// Crea los objetos del lugar acatual al que te acabas de mover.
	/// USAR DESPUÉS DE HABER NAVEGADO
	/// </summary>
	void createObjects(std::string place);

	/// <summary>
	/// Método factoría para las flechas de navegación
	/// </summary>
	ecs::Entity* createNavegationsArrows(int x, int y, std::string placeDir);

	/// <summary>
	/// Método factiría para characters
	/// </summary>
	ecs::Entity* createCharacter(int x, int y, std::string character);
public:
	//constructora
	Mapa(ecs::Scene* e);
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
#pragma once
#include "../architecture/Scene.h"
#include "../components/DialogManager.h"
#include "../sistemas/ComonObjectsFactory.h"
#include <list>

constexpr float SCALE_NPCS = 0.25;

namespace ecs {

	/// <summary>
	/// Struct que guarda la informaci�n de cada lugar, tiene el fondo a renderizar, un booleano para saber si se 
	/// puedenavegar a �l, un mapa con las direcciones que conectan a �l (a las que no tiene por qu� poder navegarse),
	/// y una lista de punteros a las entidades propias del lugar (perosonajes y flechas de movimiento) 
	/// Tiene m�todos para a�adir direcciones al lugar (necesita un string y una instancia de lugar), un booleano
	/// que indica si cierto lugar (indicado con el string del mapa) es navegable, un getPlaceFromDirection 
	/// que devuelve un puntero apuntando la posici�n de memoria de un lugar del mapa de direcciones (se usa para 
	/// moverte por el mapa) y un getTexture (se usa para renderizar el background en el mapa).
	/// No hay destructora porque no se genera nueva memoria din�mica.
	/// </summary>
	struct Lugar {
	public:
		//constructoras
		Lugar() : ents_() {};

		Lugar(Texture* t, bool n) : ents_(), backGround_(t), navegable_(n) /*character(c)*/ {};

		/// <summary>
		/// Metodo para anadir direcciones al mapa del lugar
		/// </summary>
		/// <param name="placeDir"></param>
		/// <param name="place"></param>
		void addDirections(std::string placeDir, Lugar* place);

		/// <summary>
		/// Metodo para comprobar la navegabilidad a ciero lugar
		/// </summary>
		/// <param name="placeDir"></param>
		/// <returns></returns>
		bool navigate(std::string placeDir);

		/// <summary>
		/// Metodo para obtener la direccion de memoria de un lugar del mapa de direcciones (se usa para navegar)
		/// </summary>
		Lugar* getPlaceFromDirection(std::string placeDir);
		/// <summary>
		/// Metodo que devuelve la textura del fondo para poder renderizarla
		/// </summary>
		/// <returns></returns>
		Texture* getTexture() const { return backGround_; };

		/// <summary>
		/// Mata (setAlive(false) los objetos del lugar para que se borren de la escena y los borra del vector
		/// del lugar.
		/// USAR ANTES DE NAVEGAR SI ES QUE SE PUEDE NAVEGAR
		/// </summary>
		void killObjects();

		/// <summary>
		/// Crea los objetos del lugar actual al que te acabas de mover.
		/// USAR DESPUES DE HABER NAVEGADO
		/// </summary>
		void addObjects(ecs::Entity* e);
	private:
		//Puntero a la textura del fondo
		Texture* backGround_;

		//Bool que permite la navegacion
		bool navegable_;

		//Mapa con las direcciones adyacentes al lugar (a las que no tiene por qu� poderse navegar)
		std::unordered_map<std::string, Lugar*> directions_;

		// Las entidades del lugar se almacenan como las de la escena, en vectores de objetos organizados en layouts
		std::vector<ecs::Entity*> ents_;

	};

	
	//CLASE
    class ExplorationScene :
        public Scene

    {
    public:

        ExplorationScene();
        virtual ~ExplorationScene();
        void init() override;
        virtual void close() override {}
        void render();
		void update();

		/// <summary>
		/// Metodo para navegar a cierto lugar
		/// </summary>
		void navigate(std::string placeDir);

		/// <summary>
		/// Metodo para renderizar el backGround
		/// </summary>
		void renderBackGround() const;

		// cierra la conversacion
		void closeConversation();
    private:

		/// <summary>
		/// Metodo para inicializar los lugares del mapa
		/// </summary>
		void initPlacesDefaultMap();

		/// <summary>
		/// Metodo para incializar las direcciones adyacentes a cada lugar del mapa
		/// </summary>
		void initDirectionsDefaultMap();

		/// <summary>
		/// Mata (setAlive(false) los objetos del lugar para que se borren de la escena y los borra del vector
		/// del lugar.
		/// USAR ANTES DE NAVEGAR SI ES QUE SE PUEDE NAVEGAR
		/// </summary>
		void killObjects();

		/// <summary>
		/// Crea los objetos del lugar actual al que te acabas de mover.
		/// USAR DESPUES DE HABER NAVEGADO
		/// </summary>
		void createObjects(std::string place);

		/// <summary>
		/// Metodo factoria para las flechas de navegacion
		/// </summary>
		ecs::Entity* createNavegationsArrows(Vector2D pos, std::string placeDir, float scale);

		/// <summary>
		/// Metodo factoria para characters
		/// </summary>
		ecs::Entity* createCharacter(Vector2D pos, const std::string& character, float scale);
        
		//Puntero al lugar actual
		Lugar* actualPlace_;

		//Luego hara un vector y un enum, son los lugares
		Lugar demeter;
		Lugar hefesto;
		Lugar hestia;
		Lugar artemisa;
		Lugar hermes;
		Lugar apolo;
		Lugar poseidon;

		//rect para renderizar el BackGround
		SDL_Rect rect_;

		DialogManager dialogMngr_;

		std::vector<std::string> placeToGo;
	
		// entidades del dialogo
		ecs::Entity* boxBackground;
		ecs::Entity* textDialogue;

		// flag para saber si podemos entablar dialogo
		bool canStartConversation;
    };
}



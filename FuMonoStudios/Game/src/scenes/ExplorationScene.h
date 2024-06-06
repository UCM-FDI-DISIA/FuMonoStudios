#pragma once
#ifndef DEV_TOOLS
#include <utils/checkML.h>
#endif // !DEV_TOOLS
#include <architecture/Scene.h>
#include <sistemas/DialogManager.h>
#include <sistemas/ComonObjectsFactory.h>
#include <architecture/GeneralData.h>

constexpr int MAX_CHAR_LEN_LEFT_DIARIO = 320;
constexpr int MAX_CHAR_LEN_RIGHT_DIARIO = 390;
class NPCeventSystem;
class RenderImage;

namespace ecs {

	/// <summary>
	/// Struct que guarda la informacion de cada lugar, tiene el fondo a renderizar, un booleano para saber si se 
	/// puedenavegar a el, un mapa con las direcciones que conectan a el (a las que no tiene por que poder navegarse),
	/// y una lista de punteros a las entidades propias del lugar (perosonajes y flechas de movimiento) 
	/// Tiene metodos para anadir direcciones al lugar (necesita un string y una instancia de lugar), un booleano
	/// que indica si cierto lugar (indicado con el string del mapa) es navegable, un getPlaceFromDirection 
	/// que devuelve un puntero apuntando la posicion de memoria de un lugar del mapa de direcciones (se usa para 
	/// moverte por el mapa) y un getCurrentTexture (se usa para renderizar el background en el mapa).
	/// No hay destructora porque no se genera nueva memoria dinamica.
	/// </summary>
	/// 
	struct Lugar {
	public:
		//constructoras
		Lugar() : ents_(),backGround_(nullptr),navegable_(false) {};

		Lugar(Distrito id,Texture* t, bool n) : ents_(), backGround_(t), navegable_(n),placeID_(id) /*character(c)*/ {};

		/// <summary>
		/// Metodo para anadir direcciones al mapa del lugar
		/// </summary>
		/// <param name="placeDir"></param>
		/// <param name="place"></param>
		void addDirections(Lugar* place);

		/// <summary>
		/// Metodo para comprobar la navegabilidad a ciero lugar
		/// </summary>
		/// <param name="placeDir"></param>
		/// <returns></returns>
		bool navigate(Distrito placeDir);

		/// <summary>
		/// Metodo para obtener la direccion de memoria de un lugar del mapa de direcciones (se usa para navegar)
		/// </summary>
		Lugar* getPlaceFromDirection(Distrito placeDir);
		/// <summary>
		/// Metodo que devuelve la textura del fondo para poder renderizarla
		/// </summary>
		/// <returns></returns>
		Texture* getCurrentTexture() const { return backGround_; };

		/// <summary>
		/// Destruye todos los objetos vinculados con el lugar
		/// </summary>
		/// <param name="state"></param>
		void changeActivationObjects(bool state);

		/// <summary>
		/// Crea los objetos del lugar actual al que te acabas de mover.
		/// USAR DESPUES DE HABER NAVEGADO
		/// </summary>
		void addObject(ecs::Entity* e);

		/// <summary>
		/// metodo para comprobar la propia navegabilidad de un lugar
		/// </summary>
		bool isNavegable() const;

		/// <summary>
		/// Metodo para setear la navegabilidad a true o false en funcion de value, vale true si no introduces valor
		/// </summary>
		/// <param name="value"></param>
		void setNavegability(bool value = true);

		inline Distrito getID() { return placeID_; };
	private:
		/// <summary>
		/// Identificador de el distrito
		/// </summary>
		Distrito placeID_;
		//Puntero a la textura del fondo
		Texture* backGround_;

		//Bool que permite la navegacion
		bool navegable_;

		//Mapa con las direcciones adyacentes al lugar (a las que no tiene por que poderse navegar)
		std::unordered_map<pq::Distrito, Lugar*> directions_;

		// Las entidades del lugar se almacenan como las de la escena, en vectores de objetos organizados en layouts
		std::vector<ecs::Entity*> ents_;

	};

	
	//CLASE
    class ExplorationScene :
        public Scene

    {
        __SC_DECL__(ecs::sc::EXPLORE_SCENE)
    public:

        ExplorationScene();
        virtual ~ExplorationScene();
        void init() override;
		virtual void close() override;
        void render();
		void update();

		/// <summary>
		/// Metodo para navegar a cierto lugar
		/// </summary>
		void navigate(Distrito placeDir);

		void makeDataWindow();

		// cierra la conversacion
		void closeConversation();

		void enableInteract(bool onOff) { canInteract = onOff; }
    private:
		void dialogueWhenEntering();
		
		/// <summary>
		/// Metodo para inicializar los lugares del mapa
		/// </summary>
		void initPlacesDefaultMap();

		/// <summary>
		/// Metodo para incializar las direcciones adyacentes a cada lugar del mapa
		/// </summary>
		void initDirectionsDefaultMap();

		/// <summary>
		/// Crea los objetos del lugar actual al que te acabas de mover.
		/// USAR DESPUES DE HABER NAVEGADO
		/// </summary>
		void createObjects(int place);

		/// <summary>
		/// Metodo factoria para las flechas de navegacion
		/// </summary>
		ecs::Entity* createNavegationsArrow(Vector2D pos, std::string place, float scale, int flip);

		ecs::Entity* createWorkButton(Vector2D pos, Vector2D scale);

		void createDiario();

		/// <summary>
		/// Metodo para setar la navegabilidad de placeDir lugar, valor por defecto = true
		/// </summary>
		/// <param name="placeDir"></param>
		/// <param name="value"></param>
		void setNavegabilityOfPlace(int place, bool value = true);

		/// <summary>
		/// Metodo para actualizar la navegabilidad segun el dia
		/// </summary>
		void updateNavegavility();

		/// <sumary>
		/// Nos devuelve si hemos visitados todos los lugares en un rango
		/// 
		bool checkIfVisited(int from, int to);


		/// <summary>
		/// Metodo factoria para characters
		/// </summary>
		ecs::Entity* createCharacter(Vector2D pos, const std::string& character, float scale, int flip);

		ecs::Entity* createInteractableObj(Vector2D pos, const std::string& character, float scaleX, float scaleY);

		void createPauseButton();

		void fillPagesWithEvents(std::string& text, NPCdata* data, int day);

		void adjustPagesTextAndAdd(std::string& text, int& j);
		//VARIABLES

		/// <summary>
		/// mapa que almacena todos los distritos que existen en el juego
		/// </summary>
		std::unordered_map<Distrito, Lugar> lugares;

		//Puntero al lugar actual
		Lugar* actualPlace_;	

		//rect para renderizar el BackGround
		SDL_Rect rect_;

		DialogManager dialogMngr_;

		int placeToGo;

		// flag para saber si podemos entablar dialogo
		bool canStartConversation;

		// bool que permite interactuar con flechas entrar a trabajar etc. Esta siempre true menos al entrar a dialogo
		bool canInteract;

		// flag que indica si ensenar la advertencia de que no has hablado con algun npc
		bool showTalkWarning;

		ecs::Entity* boton_Trabajo;

		void addDiarioEvent(NPCevent* event);
		void setupDiarioPages();
		void changeDiarioPages(bool forward);
		void changeCaraFelicidad(NPCdata* data);
		void makeDiaryPages();
		std::vector<std::string> diarioText_;
		std::vector<int> pagesByCharacter;
		int currentDiarioPage;

		//Vector que marca si ese dia se han visitado o no los distritos
		std::vector<bool> placesExplored;

		//diario variables

		ecs::Entity* diario_;
		RenderImage* leftPageRnd = nullptr;
		Transform* leftPageTr = nullptr;
		RenderImage* rightPageRnd = nullptr;
		Transform* rightPageTr = nullptr;
		RenderImage* caraFelicidad = nullptr;
		Texture* rightTex = nullptr;
		Texture* leftTex = nullptr;
    };
}



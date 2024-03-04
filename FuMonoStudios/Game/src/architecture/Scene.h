#pragma once
#include "../sdlutils/SDLUtils.h"
#include "ecs.h"
#include <vector>
#include <array>
#include <queue>
//#include "Entity.h"

namespace ecs {


	class Entity;
	/*
	Clase base de la que heredaran todas las escenas del juego
	*/
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		/// <summary>
		/// metodo llamado para pasar informacion y para generar las entidades
		/// </summary>
		virtual void init();

		//Vamos a querer tener un handle input o procesamos en el update?

		/// <summary>
		/// funcion llamada cada tic del juego
		/// se encarga de la logica basica
		/// </summary>
		virtual void update();
		/// <summary>
		/// funcion dedicada a pintar las entidades en pantalla
		/// </summary>
		virtual void render();
		/// <summary>
		///	Borrar las entidades en la lista de borrado
		/// </summary>
		void deleteQueueEntities();

		/// <summary>
		/// Añade una entidad vacia a la escena
		/// </summary>
		/// <returns>Entidad vacia</returns>
		Entity* addEntity(ecs::layer::layerId lyId = ecs::layer::DEFAULT);

		std::list<Entity*>::iterator addEntityToColisionList(Entity* e);

		void removeEntity(std::vector<Entity*>::iterator it, ecs::layer::layerId);

		void removeCollison(std::list<Entity*>::iterator it);

		bool checkColisions(Entity* myTrans);

		void refresh();

		void deleteAllEntities();
	protected:
    /// <summary>
		/// Vector de los objetos que pertenecen a la escena
		/// </summary>
		std::array<std::vector<Entity*>,ecs::layer::maxLayerId> objs_;
    
		std::list<Entity* > colisionEntities;

		std::queue<std::pair<ecs::layer::layerId, std::vector<Entity*>::iterator>> del_;
	};
}


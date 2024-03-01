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
		void update();
		/// <summary>
		/// funcion dedicada a pintar las entidades en pantalla
		/// </summary>
		void render();
		/// <summary>
		///	Borrar las entidades en la lista de borrado
		/// No activo (ver comentarios de la línea 36 en Scene.cpp)
		/// </summary>
		//void deleteQueueEntities();

		/// <summary>
		/// Añade una entidad vacia a la escena
		/// </summary>
		/// <returns>Entidad vacia</returns>
		Entity* addEntity(ecs::layer::layerId lyId = ecs::layer::DEFAULT);

		std::list<Entity*>::iterator addEntityToColisionList(Entity* e);

		/// No activo (ver comentarios de la línea 36 en Scene.cpp)
		//void removeEntity(std::vector<Entity*>::iterator it, ecs::layer::layerId);

		void removeCollison(std::list<Entity*>::iterator it);

		bool checkColisions(Entity* myTrans);

		void refresh();

	protected:
    /// <summary>
		/// Vector de los objetos que pertenecen a la escena
		/// </summary>
		std::array<std::vector<Entity*>,ecs::layer::maxLayerId> objs_;
    
		std::list<Entity* > colisionEntities;

		//Queue de borrado hecha por Pablo. Ver somentarios en Scene.cpp linea 36
		//std::queue<std::pair<ecs::layer::layerId, std::vector<Entity*>::iterator>> del_;
	};
}


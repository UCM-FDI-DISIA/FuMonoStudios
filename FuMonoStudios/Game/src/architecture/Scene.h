#pragma once
#include "../sdlutils/SDLUtils.h"
#include "ecs.h"
#include <vector>
#include <array>
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
		void render();
		/// <summary>
		/// Añade una entidad vacia a la escena
		/// </summary>
		/// <returns>Entidad vacia</returns>
		Entity* addEntity(ecs::layer::layerId lyId = ecs::layer::DEFAULT);

		void addEntityToColisionList(Entity* e);

		bool checkColisions(Entity* myTrans);

		void refresh();

		void deleteAllEntities();
	protected:
    /// <summary>
		/// Vector de los objetos que pertenecen a la escena
		/// </summary>
		std::array<std::vector<Entity*>,ecs::layer::maxLayerId> objs_;
    
		std::list<Entity* > colisionEntities;
	};
}


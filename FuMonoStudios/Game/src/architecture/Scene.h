#pragma once
#include "Entity.h"
namespace ecs {
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
		void init();

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

		//Entity* addEntity();

	protected:
		std::vector<Entity*> objs_;
	};
}


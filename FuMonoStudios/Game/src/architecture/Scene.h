#pragma once
#include "Entity.h"
namespace ecs {

	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		/// <summary>
		/// metodo llamado para pasar informacion
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
	protected:
		std::vector<Entity*> objs_;
	};
}


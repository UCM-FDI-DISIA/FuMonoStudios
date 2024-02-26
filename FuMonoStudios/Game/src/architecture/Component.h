#pragma once
#include "ecs.h"
//#include "Entity.h"

class Manager;
namespace ecs {

	class Entity;

	class Component {
	public:
		Component() : ent_() {}
		virtual ~Component() {}
		//Establece a que componente pertenece
		inline void setContext(Entity* ent) {
			ent_ = ent;
		}

		virtual void initComponent() {};//Metodo llamado despues de instanciar el componente (util para hacer getters)
		virtual void update() {};
		virtual void render() const {};
	protected:
		Entity* ent_; //Entidad a la que el componente pertenece
	};
}


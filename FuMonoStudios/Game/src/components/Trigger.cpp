
#include "Trigger.h"

#include "Transform.h"
#include "../architecture/Entity.h"

#include <assert.h>

Trigger::Trigger() : tr_(nullptr){

}

Trigger::~Trigger() {

}

void Trigger::initComponent() {

	tr_ = ent_->getComponent<Transform>();

	assert(tr_ != nullptr);

}

//se limpia la lista de colisiones y se comprueba en ese frame si se esta tocando con algo
void Trigger::update() {

	entTouching.clear();

	if (ent_->getMngr()->checkColisions(ent_)) {

		//Algo

	}


}

//Se registra cuando se ha tocado a una entidad y se hace un push back en la lista de entidades en contacto
void Trigger::touchEntity(ecs::Entity* ent) {

	entTouching.push_back(ent);

}

#include "Trigger.h"

#include "Transform.h"
#include "../architecture/Entity.h"

#include <assert.h>


Trigger::Trigger(std::list<ecs::Entity*>::iterator it) : tr_(nullptr)
{
	collisionIterator = it;
}

Trigger::~Trigger() {
	ent_->getMngr()->removeCollison(collisionIterator);
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

//Añade funcionalidad a la entidad si algo se posa sobre ella
void Trigger::addCallback(Callback event) {

	eventList.push_back(event);

}

//activa los eventos de todas las entidades que tenga asociadas (que este tocando)
//NOTA: en un futuro será necesario implementar un sistema de layers para diferenciar que cosa puede tocar a que cosa
bool Trigger::activateEventsFromEntities() {

	for (auto it = entTouching.begin(); it != entTouching.end(); ++it) {

		(*it)->getComponent<Trigger>()->activateCallbacks();

	}

	return entTouching.empty();

}

//Activa las funciones asociadas a esta entidad
bool Trigger::activateCallbacks() {


	for (Callback call : eventList) {

		call();
	}

	return eventList.empty();

}
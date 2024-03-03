
#include "Trigger.h"

#include "Transform.h"
#include "Clickeable.h"
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

	//asegurarse que si hay un trigger no hay un trigger clickeable
	Clickeable* cl_ = ent_->getComponent<Clickeable>();

	assert(tr_ != nullptr);
	assert(cl_ == nullptr);

}

//se limpia la lista de colisiones y se comprueba en ese frame si se esta tocando con algo
void Trigger::update() {

	entTouching.clear();

	if (ent_->getMngr()->checkColisions(ent_)) {

		//std::cout << "Choca << std::endl;

	}


}

//Se registra cuando se ha tocado a una entidad y se hace un push back en la lista de entidades en contacto
void Trigger::touchEntity(ecs::Entity* ent) {

	entTouching.push_back(ent);

}

//Aï¿½ade funcionalidad a la entidad si algo se posa sobre ella
void Trigger::addCallback(Callback event) {

	eventList.push_back(event);

}

//activa los eventos de todas las entidades que tenga asociadas (que este tocando)
//NOTA: en un futuro serï¿½ necesario implementar un sistema de layers para diferenciar que cosa puede tocar a que cosa
bool Trigger::activateEventsFromEntities() {

	for (auto it = entTouching.begin(); it != entTouching.end(); ++it) {

		(*it)->getComponent<Trigger>()->activateCallbacks(ent_);

	}

	return entTouching.empty();

}

//Activa las funciones asociadas a esta entidad
bool Trigger::activateCallbacks(ecs::Entity* Ent) {


	for (Callback call : eventList) {

		call(Ent);
	}

	return eventList.empty();

}

//Se comprueba si la entidad con este trigger esta más cercana a la pantalla que el resto de entidades con las que choca
bool Trigger::checkIfClosest() {

	auto it = entTouching.begin();

	ecs::layer::layerId myLayer = ent_->getLayer();

	while (it != entTouching.end() && (!(*it)->getComponent<Transform>()->getIfPointerIn() || myLayer >= (*it)->getLayer())) {

		++it;

	}

	return it == entTouching.end();

}
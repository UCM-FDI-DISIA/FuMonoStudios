
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

void Trigger::update() {


	if (ent_->getMngr()->checkColisions(ent_)) {

		std::cout << "Toco";

	}

}

void Trigger::touchEntity(ecs::Entity* ent) {

	entTouching.push_back(ent);

}
#include "Gravity.h"
#include "Transform.h"
#include "../architecture/Entity.h"

Gravity::Gravity(float gravityForce) : tr_(nullptr), force(gravityForce) {

}

Gravity::~Gravity() {

}

void Gravity::initComponent() {

	tr_ = ent_->getComponent<Transform>();

	assert(tr_ != nullptr);
}

void Gravity::update() {

	tr_->setPos(tr_->getRelativePos().getX(), tr_->getRelativePos().getY() - force);
	// falta hacer que deje de caer cuando colisione, borde de la pantalla, coordenada...???
}

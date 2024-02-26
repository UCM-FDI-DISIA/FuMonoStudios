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

	
	tr_->setPos(tr_->getPos().getX(), tr_->getPos().getY() - force);
	if (tr_->getPos().getY() <= 800) {
		setGravity(0);
	}
}

void Gravity::setGravity(float gravityForce) {
	force = gravityForce;
}

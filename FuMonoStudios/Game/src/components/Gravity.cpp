#include "Gravity.h"
#include "Transform.h"
#include "../architecture/Entity.h"
#include "../Time.h"

const float Gravity::GRAVITY_LIMIT = 400.0f;
const float Gravity::DEFAUTL_FORCE = 9.8f;
const float Gravity::MAX_VELOCITY = 30.0f;

Gravity::Gravity(float gravityForce) : tr_(nullptr), force(gravityForce) {

}

Gravity::~Gravity() {

}

void Gravity::initComponent() {

	tr_ = ent_->getComponent<Transform>();

	assert(tr_ != nullptr);
}

void Gravity::update() {

    if (active) {
        bool contactGround = (tr_->getPos().getY() >= GRAVITY_LIMIT);

        if (!contactGround) {
            velocity += gravityForce*Time::getDeltaTime(); // cleon: velocidad + fuerza y sin el tiempo. Toma esto, Newton!
            if (velocity > MAX_VELOCITY) {
                velocity = MAX_VELOCITY; // Limitamos la velocidad
            }
            float newY = tr_->getPos().getY() + velocity;
            if (newY > GRAVITY_LIMIT) {
                newY = GRAVITY_LIMIT;
                velocity = 0.0f; // Reseteamos velocidad al tocar el suelo
            }
            tr_->setPos(tr_->getPos().getX(), newY);
        }
    }
}

void Gravity::setActive(bool value) {
    active = value;
    velocity = 0.0f;
}

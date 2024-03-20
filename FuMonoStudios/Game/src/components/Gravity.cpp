#include "Gravity.h"
#include "Transform.h"
#include "../architecture/Entity.h"
#include "../architecture/Time.h"

const float Gravity::GRAVITY_LIMIT = 625.0f;
const float Gravity::DEFAUTL_FORCE = 9.8f * 4;
const float Gravity::MAX_VELOCITY = 30.0f;

Gravity::Gravity() : tr_(nullptr), gravityForce_(DEFAUTL_FORCE), velocity_(0), active_(true) {}

Gravity::Gravity(float force) : tr_(nullptr), gravityForce_(force), velocity_(0), active_(true) {}

Gravity::~Gravity() {}

void Gravity::initComponent() {

    tr_ = ent_->getComponent<Transform>();

    assert(tr_ != nullptr);
}

void Gravity::update() {

    if (active_) {
        bool contactGround = (tr_->getCenter().getY() >= GRAVITY_LIMIT);

        if (!contactGround) {
            velocity_ += gravityForce_ * Time::getDeltaTime();
            if (velocity_ > MAX_VELOCITY) {
                velocity_ = MAX_VELOCITY; // Limitamos la velocidad
            }
            float newY = tr_->getPos().getY() + velocity_;
            if (newY > GRAVITY_LIMIT) {
                newY = GRAVITY_LIMIT;
                velocity_ = 0.0f; // Reseteamos velocidad al tocar el suelo
            }
            tr_->setPos(tr_->getPos().getX(), newY);
        }
    }
}

void Gravity::setActive(bool value) {
    active_ = value;
    velocity_ = 0.0f;
}

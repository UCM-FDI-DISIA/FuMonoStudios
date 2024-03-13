#include "MoverTransform.h"
#include "../architecture/Entity.h"

MoverTransform::MoverTransform(Vector2D& newPos, float MovTime, Easing Easing) 
	: finalPos_(newPos), movTime_(MovTime * 1000), easing_(Easing), timer_(0), mTr_(nullptr){

}

MoverTransform::~MoverTransform() {

}

void MoverTransform::initComponent() {
	mTr_ = ent_->getComponent<Transform>();
	initPos_ = mTr_->getPos();
	startTimer_ = sdlutils().currRealTime();
}

void MoverTransform::update() {
	timer_ = sdlutils().currRealTime();

	float porcentajeRecorrido = (timer_ - startTimer_) / movTime_;

	float newX = 0;
	float newY = 0;
	switch (easing_) {
		case Linear:
			newX = initPos_.getX() +
				((finalPos_.getX() - initPos_.getX()) * porcentajeRecorrido);
			newY = initPos_.getY() +
				((finalPos_.getY() - initPos_.getY()) * porcentajeRecorrido);
			break;
		case EaseOutCubic:
			newX = finalPos_.getX() - 
				((float)pow(1 - porcentajeRecorrido, 3) * (finalPos_.getX() - initPos_.getX()));
			newY = finalPos_.getY() - 
				((float)pow(1 - porcentajeRecorrido, 3) * (finalPos_.getY() - initPos_.getY()));
			break;
		case EaseOutBack:
			float t = porcentajeRecorrido;
			float constante = 1.70158f;
			newX = initPos_.getX() + (finalPos_.getX() - initPos_.getX()) * (float)(1 - pow(1 - t, 3) * (1 - t * (constante * t - constante)));
			newY = initPos_.getY() + (finalPos_.getY() - initPos_.getY()) * (float)(1 - pow(1 - t, 3) * (1 - t * (constante * t - constante)));
			break;
	}
	

	mTr_->setPos(newX, newY);

	if (timer_ > (startTimer_ + movTime_)) 
	{
		mTr_->setPos(finalPos_);
		ent_->removeComponent<MoverTransform>();
	}
}
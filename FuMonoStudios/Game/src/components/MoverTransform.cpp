#include "MoverTransform.h"
#include "../architecture/Entity.h"
#include <architecture/Time.h>

MoverTransform::MoverTransform(Vector2D& newPos, float MovTime, Easing Easing) 
	: finalPos_(newPos), movTime_(MovTime * 1000), 
	easing_(Easing), timer_(0), mTr_(nullptr), usingCallback(false),call_(), enable_(false)
{

}

MoverTransform::MoverTransform(Vector2D& newPos, float MovTime, Easing Easing, SimpleCallback call)
	: finalPos_(newPos), movTime_(MovTime * 1000),
	easing_(Easing), timer_(0), mTr_(nullptr), usingCallback(true), call_(call), enable_(false)
{

}

MoverTransform::~MoverTransform() {

}

void MoverTransform::initComponent() {
	mTr_ = ent_->getComponent<Transform>();
	initPos_ = mTr_->getPos();
	startTimer_ = sdlutils().currRealTime();

	DragAndDrop* dnd_ = ent_->getComponent<DragAndDrop>();
	if (dnd_ != nullptr)
		dnd_->disableInteraction();
}

void MoverTransform::update() {
	if(enable_){
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
				constexpr float constante = 1.70158f;
				newX = initPos_.getX() + (finalPos_.getX() - initPos_.getX()) * (float)(1 - pow(1 - t, 3) * (1 - t * (constante * t - constante)));
				newY = initPos_.getY() + (finalPos_.getY() - initPos_.getY()) * (float)(1 - pow(1 - t, 3) * (1 - t * (constante * t - constante)));
				break;
		}
		//Aplicamos movimiento
		if(timer_ <= (startTimer_ + movTime_))
			mTr_->setPos(newX, newY);
		//si ya se ha realizado el recorrido se desactiva el componente
		else
		{
			mTr_->setPos(finalPos_);

			DragAndDrop* dnd_ = ent_->getComponent<DragAndDrop>();
			if (dnd_ != nullptr)
				dnd_->activateInteraction();
			if (call_)
				call_();
			enable_ = false;
		}
	}
}

void MoverTransform::enable()
{
	enable_ = true; 
	startTimer_ = sdlutils().currRealTime(); 
	initPos_ = mTr_->getPos();
}

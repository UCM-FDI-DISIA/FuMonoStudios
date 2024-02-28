#include "MoverTransform.h"
#include "../architecture/Entity.h"

MoverTransform::MoverTransform(Vector2D newPos, float MovTime, Easing Easing) 
	: finalPos(newPos), movTime(MovTime * 1000), easing(Easing), timer(0), tr(nullptr){

}

MoverTransform::~MoverTransform() {

}

void MoverTransform::initComponent() {
	tr = ent_->getComponent<Transform>();
	initPos = tr->getPos();
	startTimer = sdlutils().currRealTime();
}

void MoverTransform::update() {
	timer = sdlutils().currRealTime();

	float porcentajeRecorrido = (timer - startTimer) / movTime;

	float newX = 0;
	float newY = 0;
	switch (easing) {
		case Linear:
			newX = initPos.getX() +
				((finalPos.getX() - initPos.getX()) * porcentajeRecorrido);
			newY = initPos.getY() +
				((finalPos.getY() - initPos.getY()) * porcentajeRecorrido);
			break;
		case EaseOutCubic:
			newX = finalPos.getX() - 
				((float)pow(1 - porcentajeRecorrido, 3) * (finalPos.getX() - initPos.getX()));
			newY = finalPos.getY() - 
				((float)pow(1 - porcentajeRecorrido, 3) * (finalPos.getY() - initPos.getY()));
			break;
		case EaseOutBack:
			float t = porcentajeRecorrido;
			float constante = 1.70158f;
			newX = initPos.getX() + (finalPos.getX() - initPos.getX()) * (float)(1 - pow(1 - t, 3) * (1 - t * (constante * t - constante)));
			newY = initPos.getY() + (finalPos.getY() - initPos.getY()) * (float)(1 - pow(1 - t, 3) * (1 - t * (constante * t - constante)));
			break;
	}
	

	tr->setPos(newX, newY);

	if (timer > (startTimer + movTime)) 
	{
		tr->setPos(finalPos);
		ent_->removeComponent<MoverTransform>();
	}
}
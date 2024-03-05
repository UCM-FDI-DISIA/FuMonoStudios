#include "SelfDestruct.h"
#include "../sdlutils/SDLUtils.h";
#include "../architecture/Entity.h";

SelfDestruct::SelfDestruct(float TimeToDestroy) {
	timeToDestroy = TimeToDestroy * 1000;
}

SelfDestruct::SelfDestruct(float TimeToDestroy, Callback Func) {
	timeToDestroy = TimeToDestroy * 1000;
	func = Func;
	usingCallback = true;
}

SelfDestruct::SelfDestruct(float TimeToDestroy, SimpleCallback Func) {
	timeToDestroy = TimeToDestroy * 1000;
	funcSimple = Func;
	usingSimpleCallback = true;
}

SelfDestruct::~SelfDestruct() {

}

void SelfDestruct::initComponent() {
	startTime = sdlutils().currRealTime();
	
}

void SelfDestruct::update() {
	timer = sdlutils().currRealTime();

	if (timer > (startTime + timeToDestroy))
	{
		if (usingCallback)
			func(ent_);
		else if (usingSimpleCallback)
			funcSimple();

		ent_->setAlive(false);
	}
}
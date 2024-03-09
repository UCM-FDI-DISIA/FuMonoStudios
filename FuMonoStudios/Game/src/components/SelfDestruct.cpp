#include "SelfDestruct.h"
#include "../sdlutils/SDLUtils.h";
#include "../architecture/Entity.h";

SelfDestruct::SelfDestruct(float TimeToDestroy) {
	timeToDestroy_ = TimeToDestroy * 1000;
}

SelfDestruct::SelfDestruct(float TimeToDestroy, Callback Func) {
	timeToDestroy_ = TimeToDestroy * 1000;
	func_ = Func;
	usingCallback_ = true;
}

SelfDestruct::SelfDestruct(float TimeToDestroy, SimpleCallback Func) {
	timeToDestroy_ = TimeToDestroy * 1000;
	funcSimple_ = Func;
	usingSimpleCallback_ = true;
}

SelfDestruct::~SelfDestruct() {

}

void SelfDestruct::initComponent() {
	startTime_ = sdlutils().currRealTime();
	
}

void SelfDestruct::update() {
	timer_ = sdlutils().currRealTime();

	if (timer_ > (startTime_ + timeToDestroy_))
	{
		if (usingCallback_)
			func_(ent_);
		else if (usingSimpleCallback_)
			funcSimple_();

		ent_->setAlive(false);
	}
}
#include "DelayedCallback.h"
#include "../sdlutils/SDLUtils.h"
#include "../architecture/Entity.h"

DelayedCallback::DelayedCallback(float time, SimpleCallback call) 
	: Component() {
	timeToCall_ = time * 1000;
	call_ = call;
}

DelayedCallback::~DelayedCallback() {

}

void DelayedCallback::initComponent() {
	timer_ = sdlutils().currRealTime();
	timeToCall_ = timeToCall_ + timer_;
}

void DelayedCallback::update() {

	timer_ = sdlutils().currRealTime();

	if (timer_ > timeToCall_) {
		call_();
		ent_->removeComponent<DelayedCallback>();
	}
}
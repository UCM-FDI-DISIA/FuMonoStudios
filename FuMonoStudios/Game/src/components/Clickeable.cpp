#include "Clickeable.h"

#include "Transform.h"
#include "Trigger.h"
#include "../architecture/Entity.h"
#include "../sdlutils/InputHandler.h"

#include <SDL.h>
#include <assert.h>



Clickeable::Clickeable(): mTr_(nullptr), eventsWhenClick_() {

}

Clickeable::~Clickeable() {

}

void Clickeable::initComponent() {

	mTr_ = ent_->getComponent<Transform>();

	//Evitar poner clickeable si ya hay trigger
	Trigger* tri_ = ent_->getComponent<Trigger>();

	assert(mTr_ != nullptr);

	assert(tri_ == nullptr);

}
	

// cleon: "de hecho, no tenemos delta"
void Clickeable::update() {

	auto& ihdlr = ih();

	if (ihdlr.mouseButtonDownEvent()) {

		SDL_Rect* mRect_ = &mTr_->getRect();
		SDL_Point point{ ihdlr.getMousePos().first, ihdlr.getMousePos().second };

		if (SDL_PointInRect(&point, mRect_)) {

			std::cout << "click" << std::endl;
			// 
			//Recorrido por las colbacks a las que est� suscrito este objeto
			sdlutils().soundEffects().at("click").play();
			for (CallbackClickeable call : eventsWhenClick_) {

				call();
			}
		}
	}
}

void Clickeable::addEvent(CallbackClickeable event) {
	eventsWhenClick_.push_back(event);
}

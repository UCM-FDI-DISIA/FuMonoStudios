#include "Clickeable.h"

#include "Transform.h"
#include "Trigger.h"
#include "../architecture/Entity.h"
#include "../sdlutils/InputHandler.h"

#include <SDL.h>
#include <assert.h>



Clickeable::Clickeable(): tr_(nullptr), eventsWhenClick() {

}

Clickeable::~Clickeable() {

}

void Clickeable::initComponent() {

	tr_ = ent_->getComponent<Transform>();

	//Evitar poner clickeable si ya hay trigger
	Trigger* tri_ = ent_->getComponent<Trigger>();

	assert(tr_ != nullptr);

	assert(tri_ == nullptr);

}
	

// cleon: "de hecho, no tenemos delta"
void Clickeable::update() {

	auto& ihdlr = ih();

	if (ihdlr.mouseButtonDownEvent()) {

		SDL_Point point{ ihdlr.getMousePos().first, ihdlr.getMousePos().second};

		if (SDL_PointInRect(&point, &tr_->getRect())) {

			std::cout << "click" << std::endl;
			// 
			//Recorrido por las colbacks a las que est� suscrito este objeto
			for (CallbackClickeable call : eventsWhenClick) {

				call();
			}
		}
	}
}

void Clickeable::addEvent(CallbackClickeable event) {
	eventsWhenClick.push_back(event);
}

#include "Clickeable.h"

#include "Transform.h"
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

	assert(tr_ != nullptr);

}
	


void Clickeable::update() {

	auto& ihdlr = ih();

	if (ihdlr.mouseButtonDownEvent()) {

		SDL_Point point{ ihdlr.getMousePos().first, ihdlr.getMousePos().second};

		if (SDL_PointInRect(&point, &tr_->getRect())) {

			//std::cout << "click" << std::endl;
			// 
			//Recorrido por las colbacks a las que est� suscrito este objeto
			for (Callback call:eventsWhenClick) {

				call();
			}

		}

	}


}

void Clickeable::addEvent(Callback event) {

	eventsWhenClick.push_back(event);

}

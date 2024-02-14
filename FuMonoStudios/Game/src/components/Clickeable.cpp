#include "Clickeable.h"

#include "Transform.h"
#include "../architecture/Entity.h"
#include "../sdlutils/InputHandler.h"

#include <SDL.h>
#include <assert.h>



Clickeable::Clickeable() {

}

Clickeable::~Clickeable() {

}

void Clickeable::initComponent() {

	tr_ = ent_->getComponent<Transform>(ecs::cmp::TRANSFORM);

	assert(tr_ != nullptr);

}
	


void Clickeable::update() {

	auto& ihdlr = ih();

	if (ihdlr.mouseButtonDownEvent()) {

		SDL_Point point{ ihdlr.getMousePos().first, ihdlr.getMousePos().second};

		if (SDL_PointInRect(&point, tr_->getRect())) {

			std::cout << "click" << std::endl;

			for (auto i = eventsWhenClick.begin(); i != eventsWhenClick.end(); ++i) {

				(**i)();

			}

		}

	}


}

void Clickeable::addEvent(Callback& const event) {

	eventsWhenClick.push_back(&event);

}

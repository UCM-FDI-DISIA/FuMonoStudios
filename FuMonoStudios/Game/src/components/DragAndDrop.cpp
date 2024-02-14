
#include "DragAndDrop.h"

#include "Transform.h"
#include "../architecture/Entity.h"
#include "../sdlutils/InputHandler.h"

#include <SDL.h>
#include <assert.h>


DragAndDrop::DragAndDrop() {

}

DragAndDrop::~DragAndDrop() {

}

void DragAndDrop::initComponent() {

	tr_ = ent_->getComponent<Transform>(ecs::cmp::TRANSFORM);

	assert(tr_ != nullptr);

}

void DragAndDrop::update() {

	auto& ihdlr = ih();

	if (ihdlr.mouseButtonDownEvent()) {

		SDL_Point point{ ihdlr.getMousePos().first, ihdlr.getMousePos().second };

		if (SDL_PointInRect(&point, tr_->getRect())) {

			

		}

	}


}
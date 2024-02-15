
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

	SDL_Point point{ ihdlr.getMousePos().first, ihdlr.getMousePos().second };

	//Detección al clicar sobre el objeto
	if (ihdlr.mouseButtonDownEvent()) {


		if (SDL_PointInRect(&point, tr_->getRect())) {

			dragging = true;

		}

	}
	//Detección al soltar el objeto
	else if (ihdlr.mouseButtonUpEvent()) {

		dragging = false;

	}

	//Arrastre del objeto
	if (dragging) {

		tr_->Move(point.x, point.y);

		//std::cout << point.x << " " << point.y << std::endl;
	}
	


}
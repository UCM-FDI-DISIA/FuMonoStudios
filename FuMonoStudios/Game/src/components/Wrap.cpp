
#include "Wrap.h"
#include "Transform.h"

#include "../architecture/Entity.h"
#include "../sdlutils/InputHandler.h"

#include <SDL.h>
#include <assert.h>
#include <cmath>

Wrap::Wrap(float spaceAux) : space(spaceAux){


}

Wrap::~Wrap() {


}

void Wrap::initComponent() {

	tr_ = ent_->getComponent<Transform>();

	assert(tr_ != nullptr);

}

void Wrap::update() {

	auto& ihdlr = ih();

	SDL_Point point{ ihdlr.getMousePos().first, ihdlr.getMousePos().second };

	Vector2D posTR = tr_->getPos();

	double posXTR = posTR.getX();

	double posYTR = posTR.getY();

	float widthTR = tr_->getWidth();

	float heightTR = tr_->getHeigth();

	if (abs(point.x - posXTR) < space && abs(point.y - posYTR) < space) {

		std::cout << "Esquina superior izquierda" << std::endl;

	}
	else if (abs(point.x - (posXTR + widthTR / 2) < space && abs(point.y - posYTR) < space)){

		std::cout << "Esquina superior media" << std::endl;

	}
	else if (abs(point.x - (posXTR + widthTR) < space && abs(point.y - posYTR) < space)) {

		std::cout << "Esquina superior derecha" << std::endl;

	}
	else if (abs(point.x - (posXTR) < space && abs(point.y - (posYTR + heightTR / 2)) < space)) {

		std::cout << "Esquina media izquierda" << std::endl;

	}
	else if (abs(point.x - (posXTR) < space && abs(point.y - (posYTR + heightTR)) < space)) {

		std::cout << "Esquina inferior izquierda" << std::endl;

	}
	else if (abs(point.x - (posXTR + widthTR / 2) < space && abs(point.y - (posYTR + heightTR / 2)) < space)) {

		std::cout << "Esquina media media" << std::endl;

	}
	else if (abs(point.x - (posXTR + widthTR) < space && abs(point.y - (posYTR + heightTR / 2)) < space)) {

		std::cout << "Esquina media derecha" << std::endl;

	}
	else if (abs(point.x - (posXTR + widthTR / 2) < space && abs(point.y - (posYTR + heightTR)) < space)) {

		std::cout << "Esquina inferior media" << std::endl;

	}
	else if (abs(point.x - (posXTR + widthTR) < space && abs(point.y - (posYTR + heightTR)) < space)) {

		std::cout << "Esquina inferior derecha" << std::endl;

	}

}
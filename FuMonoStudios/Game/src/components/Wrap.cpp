
#include "Wrap.h"
#include "Transform.h"

#include "../architecture/Entity.h"
#include "../sdlutils/InputHandler.h"

#include <SDL.h>
#include <assert.h>
#include <cmath>

Wrap::Wrap(float spaceAux, int repTimesAux, std::list<int> routeAux) : space(spaceAux), repTimes(repTimesAux) {

	route = routeAux;

	restartRoute();

}

Wrap::Wrap(float spaceAux, int repTimesAux) : space(spaceAux), repTimes(repTimesAux) {

	route.push_back(pointRoute::LeftUp);

	route.push_back(pointRoute::LeftDown);

	route.push_back(pointRoute::RightDown);

	route.push_back(pointRoute::RightUp);

	restartRoute();

}

Wrap::Wrap(float spaceAux) : space(spaceAux) {

	route.push_back(pointRoute::LeftUp);

	route.push_back(pointRoute::LeftDown);

	route.push_back(pointRoute::RightDown);

	route.push_back(pointRoute::RightUp);

	restartRoute();
}

Wrap::~Wrap() {


}

void Wrap::initComponent() {

	tr_ = ent_->getComponent<Transform>();

	assert(tr_ != nullptr);

}

void Wrap::update() {

	if (!wrapped) {
		auto& ihdlr = ih();

		SDL_Point point{ ihdlr.getMousePos().first, ihdlr.getMousePos().second };

		Vector2D posTR = tr_->getPos();

		double posXTR = posTR.getX();

		double posYTR = posTR.getY();

		float widthTR = tr_->getWidth();

		float heightTR = tr_->getHeigth();

		if (abs(point.x - posXTR) < space && abs(point.y - posYTR) < space) {

			std::cout << "Esquina superior izquierda" << std::endl;

			if ((*lastPoint) == pointRoute::LeftUp) {
				++lastPoint;
			}

		}
		else if (abs(point.x - (posXTR + widthTR / 2) < space && abs(point.y - posYTR) < space)) {

			std::cout << "Esquina superior media" << std::endl;

			if ((*lastPoint) == pointRoute::MiddleUp) {
				++lastPoint;
			}

		}
		else if (abs(point.x - (posXTR + widthTR) < space && abs(point.y - posYTR) < space)) {

			std::cout << "Esquina superior derecha" << std::endl;

			if ((*lastPoint) == pointRoute::RightUp) {
				++lastPoint;
			}

		}
		else if (abs(point.x - (posXTR) < space && abs(point.y - (posYTR + heightTR / 2)) < space)) {

			std::cout << "Esquina media izquierda" << std::endl;

			if ((*lastPoint) == pointRoute::LeftMid) {
				++lastPoint;
			}

		}
		else if (abs(point.x - (posXTR + widthTR / 2) < space && abs(point.y - (posYTR + heightTR / 2)) < space)) {

			std::cout << "Esquina media media" << std::endl;

			if ((*lastPoint) == pointRoute::MiddleMid) {
				++lastPoint;
			}

		}
		else if (abs(point.x - (posXTR + widthTR) < space && abs(point.y - (posYTR + heightTR / 2)) < space)) {

			std::cout << "Esquina media derecha" << std::endl;

			if ((*lastPoint) == pointRoute::RightMid) {
				++lastPoint;
			}

		}
		else if (abs(point.x - (posXTR) < space && abs(point.y - (posYTR + heightTR)) < space)) {

			std::cout << "Esquina inferior izquierda" << std::endl;

			if ((*lastPoint) == pointRoute::LeftDown) {
				++lastPoint;
			}

		}
		else if (abs(point.x - (posXTR + widthTR / 2) < space && abs(point.y - (posYTR + heightTR)) < space)) {

			std::cout << "Esquina inferior media" << std::endl;

			if ((*lastPoint) == pointRoute::MiddleDown) {
				++lastPoint;
			}

		}
		else if (abs(point.x - (posXTR + widthTR) < space && abs(point.y - (posYTR + heightTR)) < space)) {

			std::cout << "Esquina inferior derecha" << std::endl;

			if ((*lastPoint) == pointRoute::RightDown) {
				++lastPoint;
			}

		}

		if (lastPoint == route.end()) {

			std::cout << "Embalado" << std::endl;

			repTimes--;

			if (repTimes < 0) {

				wrapped = true;

			}

			restartRoute();
		}
	}
	

}

void Wrap::restartRoute() {

	lastPoint = route.begin();

}
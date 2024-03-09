
#include "Wrap.h"
#include "Transform.h"
#include "MultipleTextures.h"

#include "../architecture/Entity.h"
#include "../sdlutils/InputHandler.h"

#include <SDL.h>
#include <assert.h>
#include <cmath>

//Constructora dada una ruta especifica
Wrap::Wrap(float spaceAux, int repTimesAux, std::list<int> routeAux) : space(spaceAux), repTimes(repTimesAux) {

	route = routeAux;

	totalPointsRoute = route.size() * (repTimes + 1);

	restartRoute();

}

//constructora con ruta base pero pudiendo escoger radio de deteccion de puntos y numero de repeticiones de patron
Wrap::Wrap(float spaceAux, int repTimesAux) : space(spaceAux), repTimes(repTimesAux) {

	route.push_back(pointRoute::LeftUp);

	route.push_back(pointRoute::LeftDown);

	route.push_back(pointRoute::RightDown);

	route.push_back(pointRoute::RightUp);

	totalPointsRoute = route.size() * (repTimes + 1);

	restartRoute();

}

//Ruta base y no se repite el patron de este
Wrap::Wrap(float spaceAux) : space(spaceAux) {

	route.push_back(pointRoute::LeftUp);

	route.push_back(pointRoute::LeftDown);

	route.push_back(pointRoute::RightDown);

	route.push_back(pointRoute::RightUp);

	totalPointsRoute = route.size() * (repTimes + 1);

	restartRoute();
}

Wrap::~Wrap() {


}

void Wrap::initComponent() {

	tr_ = ent_->getComponent<Transform>();

	tri_ = ent_->getComponent<Trigger>();

	mul_ = ent_->getComponent<MultipleTextures>();

	assert(tr_ != nullptr);

	assert(tri_ != nullptr);

	assert(mul_ != nullptr);

}

void Wrap::update() {

	//Primero se revisa si el paquete aun no se ha envuelto
	if (!wrapped) {
		auto& ihdlr = ih();

		SDL_Point point{ ihdlr.getMousePos().first, ihdlr.getMousePos().second };

		Vector2D posTR = tr_->getPos();

		//Se inicializan las posiciones del paquete para no acceder al transform y coordenadas constantemente
		double posXTR = posTR.getX();

		double posYTR = posTR.getY();

		float widthTR = tr_->getWidth();

		float heightTR = tr_->getHeigth();
		
		auto tapeEnt = tri_->getSpecificEntity(ecs::layer::TAPE);

		//primero se comprueba que la caja este tocando con la cinta
		if (tapeEnt != nullptr) {

			//despues se comprueba que la cinta esta tocando con el ratón
			//a futuro si se ve un bug se podria añadir que además el ratón este pulsado pero no debería hacer falta
			SDL_Rect tapeRect = tapeEnt->getComponent<Transform>()->getRect();

			if (SDL_PointInRect(&point, &tapeRect)) {

				//Se comprueba punto a punto si el ratón esta en un radio especifico de los nueve puntos que forman la entidad 
				if (abs(tapeRect.x - posXTR) < space && abs(tapeRect.y - posYTR) < space) {
					if (debug) {
						std::cout << "Esquina superior izquierda" << std::endl;
					}

					checkPointTouch(pointRoute::LeftUp);

				}
				else if (abs(tapeRect.x - (posXTR + widthTR / 2)) < space && abs(tapeRect.y - posYTR) < space) {

					if (debug) {
						std::cout << "Esquina superior media" << std::endl;
					}

					checkPointTouch(pointRoute::MiddleUp);

				}
				else if (abs(tapeRect.x - (posXTR + widthTR)) < space && abs(tapeRect.y - posYTR) < space) {

					if (debug) {
						std::cout << "Esquina superior derecha" << std::endl;
					}

					checkPointTouch(pointRoute::RightUp);

				}
				else if (abs(tapeRect.x - (posXTR)) < space && abs(tapeRect.y - (posYTR + heightTR / 2)) < space) {

					if (debug) {
						std::cout << "Esquina media izquierda" << std::endl;
					}

					checkPointTouch(pointRoute::LeftMid);

				}
				else if (abs(tapeRect.x - (posXTR + widthTR / 2)) < space && abs(tapeRect.y - (posYTR + heightTR / 2)) < space) {

					if (debug) {
						std::cout << "Esquina media media" << std::endl;
					}

					checkPointTouch(pointRoute::MiddleMid);

				}
				else if (abs(tapeRect.x - (posXTR + widthTR)) < space && abs(tapeRect.y - (posYTR + heightTR / 2)) < space) {

					if (debug) {
						std::cout << "Esquina media derecha" << std::endl;
					}

					checkPointTouch(pointRoute::RightMid);

				}
				else if (abs(tapeRect.x - (posXTR)) < space && abs(tapeRect.y - (posYTR + heightTR)) < space) {

					if (debug) {
						std::cout << "Esquina inferior izquierda" << std::endl;
					}

					checkPointTouch(pointRoute::LeftDown);

				}
				else if (abs(tapeRect.x - (posXTR + widthTR / 2)) < space && abs(tapeRect.y - (posYTR + heightTR)) < space) {

					if (debug) {
						std::cout << "Esquina inferior media" << std::endl;
					}

					checkPointTouch(pointRoute::MiddleDown);

				}
				else if (abs(tapeRect.x - (posXTR + widthTR)) < space && abs(tapeRect.y - (posYTR + heightTR)) < space) {

					if (debug) {
						std::cout << "Esquina inferior derecha" << std::endl;
					}

					checkPointTouch(pointRoute::RightDown);

				}

				//Si se ha recorrido toda la ruta se comprueba si quedan repeticiones de patron. En caso contrario se da por envalado
				if (lastPoint == route.end()) {

					if (debug) {
						std::cout << "Embalado" << std::endl;
					}

					repTimes--;

					if (repTimes < 0) {

						wrapped = true;

					}

					restartRoute();
				}

				//Se comprueba el % de paquete empaquetado para hacer el cambio de sprites
				if ((routePointsDone == totalPointsRoute / 4 && wrapFase < 1)
					|| (routePointsDone == totalPointsRoute / 2 && wrapFase < 2)
					|| (routePointsDone == (totalPointsRoute * 3) / 4 && wrapFase < 3)
					|| (routePointsDone == totalPointsRoute && wrapFase < 4)) {

					mul_->nextTexture();
					wrapFase++;

				}

			}

		}
		
	}
	

}

//Reinicia la ruta de envalado
void Wrap::restartRoute() {

	lastPoint = route.begin();

}

void Wrap::checkPointTouch(pointRoute point) {

	if ((*lastPoint) == point) {
		++lastPoint;
		routePointsDone++;
	}

}
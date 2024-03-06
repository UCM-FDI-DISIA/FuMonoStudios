
#include "Wrap.h"
#include "Transform.h"

#include "../architecture/Entity.h"
#include "../sdlutils/InputHandler.h"

#include <SDL.h>
#include <assert.h>
#include <cmath>

//Constructora dada una ruta especifica
Wrap::Wrap(float spaceAux, int repTimesAux, std::list<int> routeAux) : space(spaceAux), repTimes(repTimesAux) {

	route = routeAux;

	restartRoute();

}

//constructora con ruta base pero pudiendo escoger radio de deteccion de puntos y numero de repeticiones de patron
Wrap::Wrap(float spaceAux, int repTimesAux) : space(spaceAux), repTimes(repTimesAux) {

	route.push_back(pointRoute::LeftUp);

	route.push_back(pointRoute::LeftDown);

	route.push_back(pointRoute::RightDown);

	route.push_back(pointRoute::RightUp);

	restartRoute();

}

//Ruta base y no se repite el patron de este
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

	tri_ = ent_->getComponent<Trigger>();

	assert(tr_ != nullptr);

	assert(tri_ != nullptr);

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
				if (abs(point.x - posXTR) < space && abs(point.y - posYTR) < space) {
					if (debug) {
						std::cout << "Esquina superior izquierda" << std::endl;
					}


					if ((*lastPoint) == pointRoute::LeftUp) {
						++lastPoint;
					}

				}
				else if (abs(point.x - (posXTR + widthTR / 2) < space && abs(point.y - posYTR) < space)) {

					if (debug) {
						std::cout << "Esquina superior media" << std::endl;
					}

					if ((*lastPoint) == pointRoute::MiddleUp) {
						++lastPoint;
					}

				}
				else if (abs(point.x - (posXTR + widthTR) < space && abs(point.y - posYTR) < space)) {

					if (debug) {
						std::cout << "Esquina superior derecha" << std::endl;
					}

					if ((*lastPoint) == pointRoute::RightUp) {
						++lastPoint;
					}

				}
				else if (abs(point.x - (posXTR) < space && abs(point.y - (posYTR + heightTR / 2)) < space)) {

					if (debug) {
						std::cout << "Esquina media izquierda" << std::endl;
					}

					if ((*lastPoint) == pointRoute::LeftMid) {
						++lastPoint;
					}

				}
				else if (abs(point.x - (posXTR + widthTR / 2) < space && abs(point.y - (posYTR + heightTR / 2)) < space)) {

					if (debug) {
						std::cout << "Esquina media media" << std::endl;
					}

					if ((*lastPoint) == pointRoute::MiddleMid) {
						++lastPoint;
					}

				}
				else if (abs(point.x - (posXTR + widthTR) < space && abs(point.y - (posYTR + heightTR / 2)) < space)) {

					if (debug) {
						std::cout << "Esquina media derecha" << std::endl;
					}

					if ((*lastPoint) == pointRoute::RightMid) {
						++lastPoint;
					}

				}
				else if (abs(point.x - (posXTR) < space && abs(point.y - (posYTR + heightTR)) < space)) {

					if (debug) {
						std::cout << "Esquina inferior izquierda" << std::endl;
					}

					if ((*lastPoint) == pointRoute::LeftDown) {
						++lastPoint;
					}

				}
				else if (abs(point.x - (posXTR + widthTR / 2) < space && abs(point.y - (posYTR + heightTR)) < space)) {

					if (debug) {
						std::cout << "Esquina inferior media" << std::endl;
					}

					if ((*lastPoint) == pointRoute::MiddleDown) {
						++lastPoint;
					}

				}
				else if (abs(point.x - (posXTR + widthTR) < space && abs(point.y - (posYTR + heightTR)) < space)) {

					if (debug) {
						std::cout << "Esquina inferior derecha" << std::endl;
					}

					if ((*lastPoint) == pointRoute::RightDown) {
						++lastPoint;
					}

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


			}

		}

		

		
	}
	

}

//Reinicia la ruta de envalado
void Wrap::restartRoute() {

	lastPoint = route.begin();

}
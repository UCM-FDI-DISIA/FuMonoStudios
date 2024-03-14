
#include "DragAndDrop.h"

#include "Transform.h"
#include "Gravity.h"
#include "Trigger.h"
#include "../architecture/Entity.h"
#include "../sdlutils/InputHandler.h"

#include <SDL.h>
#include <assert.h>

DragAndDrop::DragAndDrop() : tr_(nullptr), tri_(nullptr), grav_(nullptr), dragging_(false), differenceX_(0), differenceY_(0),
usingCallback_(false), usingOnlyClosestEnt_(false) {
}


DragAndDrop::DragAndDrop(bool UsingOnlyClosestEnt) : 
	tr_(nullptr), tri_(nullptr), grav_(nullptr), dragging_(false), differenceX_(0), differenceY_(0), 
	usingCallback_(false), usingOnlyClosestEnt_(UsingOnlyClosestEnt) {
}

DragAndDrop::DragAndDrop(bool UsingOnlyClosestEnt, SimpleCallback Func) : 
	tr_(nullptr), tri_(nullptr), grav_(nullptr), dragging_(false), differenceX_(0), differenceY_(0),
	usingCallback_(true), usingOnlyClosestEnt_(UsingOnlyClosestEnt)
{
	func_ = Func;
}

DragAndDrop::~DragAndDrop() {

}

void DragAndDrop::initComponent() {
	assert(ent_->getComponent<Trigger>() == nullptr);

	tri_ = ent_->addComponent<Trigger>();

	tr_ = ent_->getComponent<Transform>();

	grav_ = ent_->getComponent<Gravity>();

	assert(tr_ != nullptr);

}

void DragAndDrop::update() {
	auto& ihdlr = ih();

	SDL_Point point{ ihdlr.getMousePos().first, ihdlr.getMousePos().second };

	//Deteccion al clicar sobre el objeto
	if (ihdlr.mouseButtonDownEvent()) {
		if (tr_->getIfPointerIn() && tri_->checkIfClosest()) {

			dragging_ = true;
			// desactivamos gravedad al draggear
			if (grav_ != nullptr) {
				grav_->setActive(false);
			}

			//Para que funcione sin ir al centro, con margen
			differenceX_ = point.x - tr_->getPos().getX();;
			differenceY_ = point.y - tr_->getPos().getY();;
			porcentajeStart = tr_->getPorcentajeScale();
		}
	}
	//Deteccion al soltar el objeto
	else if (ihdlr.mouseButtonUpEvent()) {

		dragging_ = false;
		// reactivamos la gravedad
		if (grav_ != nullptr) {
			grav_->setActive(true);
		}

		//Al soltar el objeto activa los callback de todas las entidades que este tocando el objeto
		// si no tenemos activado el activar solo al mas cercano
		if (!usingOnlyClosestEnt_)
			tri_->activateEventsFromEntities();
		else
			tri_->activateEventFromClosestEntity();

		// si has asignado callback se activa
		if (usingCallback_)
			func_();
	}

	//Arrastre del objeto
	if (dragging_) {
		//Para que vaya en el medio
		//tr_->setPos(point.x - (tr_->getWidth() / 2), point.y - (tr_->getHeigth() / 2));

		// comprobacion para evitar sacar la entidad de la pantalla
		if ((point.x - differenceX_ > -(tr_->getWidth() / 2))
			&& (point.x - differenceX_ < sdlutils().width() - (tr_->getWidth() / 2)) 
			&& (point.y - differenceY_ < sdlutils().height() - (tr_->getHeigth() / 6)))
		{

			Vector2D pos = Vector2D(
				point.x - (differenceX_ * (1 - (porcentajeStart - tr_->getPorcentajeScale()))),
				point.y - (differenceY_ * (1 - (porcentajeStart - tr_->getPorcentajeScale()))));

			//Sin centrarse el objeto
			//tr_->setPos((point.x - differenceX_), (point.y - differenceY_));
			tr_->setPos(pos);

		}
	}

}
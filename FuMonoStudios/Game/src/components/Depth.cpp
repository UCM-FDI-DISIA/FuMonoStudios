#include "Depth.h"

Depth::Depth() {

}

Depth::~Depth() {

}

void Depth::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	tr_->activateDepth();
}

void Depth::updateDepth() {
	//función que calcula el depth
	depth_ = (tr_->getCenter().getY() * 0.07) + 40;
	if (depth_ > 100)
		depth_ = 100;
	depth_ = depth_ / 100; // para que quede como porcentaje

	tr_->setTrueScale(tr_->getScale() * depth_);

	// esto actualiza el scale de cada transform
	for (Transform* chTr : tr_->GetChildren())
	{
		float porcentaje = ((tr_->getTrueScale() * 100) / tr_->getScale()) / 100;
		chTr->setTrueScale(porcentaje * chTr->getScale());
	}
}

void Depth::updateChildPos() {
	// mueve las posiciones relativas de los hijos al cambiar de escala
	for (Transform* trCh : tr_->GetChildren())
	{
		trCh->setPos((trCh->getRelPos() * depth_).getX(),
			(trCh->getRelPos() * depth_).getY());
	}
}
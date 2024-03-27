#include "PackageChecker.h"
#include "../architecture/Component.h"
#include "../architecture/Entity.h"
#include "Transform.h"
#include "Gravity.h"
#include "MoverTransform.h"
#include "Paquete.h"
#include "SelfDestruct.h"
#include "../architecture/GeneralData.h"
#include <list>
#include <functional>
#include <components/ErrorNote.h>

PackageChecker::PackageChecker(pq::Distrito dis, ecs::MainScene* sc) : toDis_(dis), extraCond_(),mainSc_(sc)
{

}

PackageChecker::~PackageChecker()
{
}

void PackageChecker::initComponent()
{

	std::function<void(ecs::Entity*)> call = [this](ecs::Entity* ent) {checkEntity(ent); };
	Trigger* tri = ent_->getComponent<Trigger>();
	assert(tri != nullptr);
	tri->addCallback(call);
}

void PackageChecker::addCondition(Condition newCond)
{
	extraCond_.push_back(newCond);
}

bool PackageChecker::checkPackage(Paquete* package)
{
	bool correctPack = package->correcto() && checkAdditionalConditions(package);
	return  correctPack && package->bienSellado() || (!correctPack && toDis_ == pq::Erroneo);
}

void PackageChecker::checkEntity(ecs::Entity* ent)
{
	//comprobamos si es un paquete
	if (ent->getComponent<Paquete>() != nullptr) {
		Vector2D entPos = ent->getComponent<Transform>()->getPos();
		ent->removeComponent<Gravity>();

		//animacion de salida del paquete dependiaendo de que sea
		auto mover = ent->getComponent<MoverTransform>();
		if (toDis_ != Erroneo) {
			mover->setEasing(Easing::EaseOutCubic);
			mover->setFinalPos(entPos+ Vector2D(0, -600));
			mover->setMoveTime(1.7f);
		}
		else {
			mover->setEasing(Easing::EaseOutCubic);
			mover->setFinalPos(entPos+ Vector2D(-600, 0));
			mover->setMoveTime(1);
		}
		mover->enable();

		ent->addComponent<SelfDestruct>(1,[this](){
			if (mainSc_ != nullptr) mainSc_->createPaquete(generalData().getPaqueteLevel());
			});

		if (checkPackage(ent->getComponent<Paquete>())) {

			GeneralData::instance()->correctPackage();
		}
		else {
			GeneralData::instance()->wrongPackage();
			auto note = mainSc_->addEntity(ecs::layer::BACKGROUND);
			note->addComponent<ErrorNote>(ent->getComponent<Paquete>(), toDis_==Erroneo, 
				toDis_ != ent->getComponent<Paquete>()->getDistrito());
		}
#ifdef QA_TOOLS
		dataCollector().recordPacage(entRec->getComponent<Paquete>());
#endif // QA_TOOLS
	}
}

bool PackageChecker::checkAdditionalConditions(Paquete* package)
{
	bool aditional = true;
	for (Condition call : extraCond_) {
		if (!call(package)) {
			aditional = false;
		}
	}
	return aditional;
}




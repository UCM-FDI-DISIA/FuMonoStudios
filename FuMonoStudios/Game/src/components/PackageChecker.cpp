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

PackageChecker::PackageChecker(Paquete::Distrito dis) : toDis(dis), extraCond()
{

}

PackageChecker::~PackageChecker()
{
}

void PackageChecker::initComponent()
{
	//std::function<void(ecs::Entity*)> call = [this](ecs::Entity* ent) {checkEntity(ent); };
	//ent_->getComponent<Trigger>()->addCallback(call);
}

void PackageChecker::addCondition(Condition newCond)
{
	extraCond.push_back(newCond);
}

bool PackageChecker::checkPackage(Paquete* package)
{
	bool correctPack = false;
	if (package->Correcto() && package->BienSellado()) {
		if (toDis == package->getDistrito()) {
			correctPack = checkAdditionalConditions(package);
		}
	}
	else {
		if (toDis == Paquete::Erroneo) {
			correctPack = checkAdditionalConditions(package);
		}
	}
	return correctPack;
}

void PackageChecker::checkEntity(ecs::Entity* ent)
{
	//comprobamos si es un paquete
	Transform* entTr = ent->getComponent<Transform>();
	if (ent->getComponent<Paquete>() != nullptr) {
		ent->removeComponent<Gravity>();
		ent->addComponent<MoverTransform>( // animación básica del paquete llendose
				entTr->getPos() + Vector2D(0,-600), 1.5, Easing::EaseOutCubic);
		ent->addComponent<SelfDestruct>(1);
		if (checkPackage(ent->getComponent<Paquete>())) {

			GeneralData::instance()->correctPackage();
		}
		else {
			GeneralData::instance()->wrongPackage();
		}
	}
}

bool PackageChecker::checkAdditionalConditions(Paquete* package)
{
	bool aditional = true;
	/*for (Condition call : extraCond) {
		if (!call(package)) {
			aditional = false;
		}
	}*/
	return aditional;
}




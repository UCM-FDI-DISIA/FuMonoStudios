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

PackageChecker::PackageChecker() : extraCond_()
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
	extraCond_.push_back(newCond);
}

bool PackageChecker::checkPackage(Paquete* package)
{
	bool correctPack = false;
	if (package->correcto() && package->bienSellado()) {
		correctPack = checkAdditionalConditions(package);
	}
	else {
		//Esto me gustaria cambiarlo luego, es decir, simplemente darle un booleano de papelera o algo. Nos ahorraria tambien el tema de
		//que tenemos un distrito extra. Por ahora esta asi simplemente porque la refactorizacion que acabo de hacer parece un poco tonta.
		//Ademas no se siquiera si vamos a hacer que las papeleras tengan condiciones extras Dx
		//Pero sí que se que podemos dar a un tubo la condicion de papelera (por ejemplo, un dia decir que todos los paqutes malos tienen que ser 
		//redirigidos a la oficina en x distrito y entonces funciona ambos de papelera para los errones pero normal para el resto)
		correctPack = checkAdditionalConditions(package);
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
	for (Condition call : extraCond_) {
		if (!call(package)) {
			aditional = false;
		}
	}
	return aditional;
}




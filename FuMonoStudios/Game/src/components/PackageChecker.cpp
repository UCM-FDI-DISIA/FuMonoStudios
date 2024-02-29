#include "PackageChecker.h"
#include "../architecture/Component.h"
#include "Paquete.h"

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
}

void PackageChecker::addCondition(Condition newCond)
{
	extraCond.push_back(newCond);
}

bool PackageChecker::checkPackage(Paquete* package)
{
	bool correctPack = false;
	if (package->Correcto()) {
		if (toDis == package->getDist()) {
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

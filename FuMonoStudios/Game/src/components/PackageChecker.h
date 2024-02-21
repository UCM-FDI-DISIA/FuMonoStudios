#pragma once
#include "../architecture/Component.h"
#include "Paquete.h"

#include <list>
#include <functional>

using Condition = std::function<bool(Paquete*)>;

class PackageChecker : public ecs::Component
{
public:
	PackageChecker(Paquete::Distrito);
	~PackageChecker();

	virtual void initComponent();
	void addCondition(Condition);

	bool checkPackage(Paquete*);
private:
	Paquete::Distrito toDis;
	std::list<Condition> extraCond;

	bool checkAdditionalConditions(Paquete*);
};


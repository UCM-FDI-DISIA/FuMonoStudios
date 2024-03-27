#pragma once
#include "../architecture/Component.h"
#include <scenes/MainScene.h>
#include "Paquete.h"

#include <list>
#include <functional>

using Condition = std::function<bool(Paquete*)>;

class PackageChecker : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::CHECKER)
	PackageChecker(pq::Distrito, ecs::MainScene* sc);
	~PackageChecker();

	virtual void initComponent();
	void addCondition(Condition);

	bool checkPackage(Paquete*);

	void checkEntity(ecs::Entity* ent);
private:
	bool checkAdditionalConditions(Paquete*);

	pq::Distrito toDis_;
	std::list<Condition> extraCond_;
	ecs::MainScene* mainSc_;
};


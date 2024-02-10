#pragma once
#include "ecs.h"
#include "Entity.h"

class Manager;

class Component {
public:
	Component() : ent_() {}
	virtual ~Component() {}

	inline void setContext(Entity* ent) {
		ent_ = ent;
	}

	virtual void initComponent() {};
	virtual void update() {};
	virtual void render() {};
protected:
	Entity* ent_;
};


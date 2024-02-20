#pragma once

#include <list>

#include "../architecture/Component.h"

class Transform;

class Trigger : public ecs::Component {

public:

	__CMP_DECL__(ecs::cmp::TRIGGER)

	Trigger();

	~Trigger();

	void initComponent() override;

	void update() override;

	void touchEntity(ecs::Entity* ent);

private:

	Transform* tr_;

	std::list <ecs::Entity*> entTouching;



};


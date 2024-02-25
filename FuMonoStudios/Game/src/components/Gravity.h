#pragma once
#include "../architecture/Component.h"

class Transform;

class Gravity : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::TRANSFORM)
	Gravity(float gravityForce);
	~Gravity();

	void setGravity(float gravityForce);
	void initComponent() override;
	void update() override;
private:
	Transform* tr_;
	float force;
};


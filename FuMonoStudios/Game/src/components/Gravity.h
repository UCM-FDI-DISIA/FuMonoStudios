#pragma once
#include "../architecture/Component.h"

class Transform;

class Gravity : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::GRAVITY)
	Gravity();
	Gravity(float gravityForce);
	~Gravity();

	void initComponent() override;
	void update() override;
	void setActive(bool value);
private:
	static const float GRAVITY_LIMIT; // Limite de gravedad (donde tenemos el suelo)
	static const float DEFAUTL_FORCE; // Fuerza de gravedad por deferto
	static const float MAX_VELOCITY; // Limite de aceleracion

	Transform* tr_;
	float gravityForce;
	float velocity;
	bool active;
};


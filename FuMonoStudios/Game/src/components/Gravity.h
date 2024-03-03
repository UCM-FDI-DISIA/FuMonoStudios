#pragma once
#include "../architecture/Component.h"

class Transform;

// Aplica gravedad al Transform. ¡Importante!
// si el entity tiene draganddrop, aplicar el componente
// gravity antes de aplicar el de draganddrop
// Para evitar fallos, añadir este componente justo después del Transform
class Gravity : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::TRANSFORM)
	Gravity(float gravityForce);
	~Gravity();

	void initComponent() override;
	void update() override;
private:
	Transform* tr_;
	float force;
};


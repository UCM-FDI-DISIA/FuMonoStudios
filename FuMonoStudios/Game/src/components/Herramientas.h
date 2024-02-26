#pragma once
#include "../architecture/Component.h"

class Herramientas : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::HERRAMIENTAS)
	Herramientas();

	~Herramientas();

	void initComponent() override;

	void update() override;
private:
};


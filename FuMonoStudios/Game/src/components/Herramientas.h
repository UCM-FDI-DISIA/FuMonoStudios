#pragma once
#include "../architecture/Component.h"
#include <functional>
#include "Paquete.h"
#include "../architecture/Entity.h"

using Callback = std::function<void(ecs::Entity*)>;

enum TipoHerramienta {
	SelloCalleA, selloCalleB, selloCalleC
};

class Herramientas : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::HERRAMIENTAS)
	Herramientas();

	~Herramientas();
	
	void initComponent() override {};

	void update() override {};

	void setFunctionality(TipoHerramienta tipo);

	void interact(ecs::Entity* paquete);
private:
	Callback funcion;
};


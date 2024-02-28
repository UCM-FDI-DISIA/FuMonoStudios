#pragma once
#include "../architecture/Component.h"
#include <functional>
#include "Paquete.h"
#include "../architecture/Entity.h"

using Callback = std::function<void(ecs::Entity*)>;

enum TipoHerramienta {
	SelloCalleA, SelloCalleB, SelloCalleC
};

// Para usar esta clase, hay que asignarla al entity y luego
// llamar a setFunctionality para saber qué hará al interactuar con el
// paquete. 
// Funciona a la par con una función que está asignada a cada paquete
// que llama a la funcion interact si detecta que es una herramienta
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


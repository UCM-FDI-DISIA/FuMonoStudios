#pragma once

#include "../architecture/Component.h"
#include <functional>

class Transform;
class Gravity;
class Trigger;

using SimpleCallback = std::function<void()>; // por si quieres q haga algo al soltar

// Este comp permite mover una entity con transform y al soltarlo sobre una
// entity con Trigger, se activan los callbacks de la entidad soltada.
// Es importante NO AÑADIR UN TRIGGER si se ha añadido este componente antes
// Puedes añadir un callback para la entidad que arrastras, para ello asignalo
// en la constructora.
// Debes meter un bool diciendo si quieres que se haga callbacks de todas las entidades
// que están tocando o solo la que esta mas cercana
class DragAndDrop : public ecs::Component {

public:
	__CMP_DECL__(ecs::cmp::DRAGANDDROP)
	DragAndDrop();
	DragAndDrop(bool UsingOnlyClosestEnt);
	DragAndDrop(bool UsingOnlyClosestEnt, SimpleCallback Func);

	~DragAndDrop();

	void initComponent() override;

	void update() override;

private:

	Transform* tr_;
	
	Gravity* grav_;

	Trigger* tri_;

	bool dragging;

	float differenceX;

	float differenceY;

	bool usingOnlyClosestEnt = false;

	bool usingCallback = false;
	SimpleCallback func;
};

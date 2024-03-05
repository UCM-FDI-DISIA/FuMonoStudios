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
class DragAndDrop : public ecs::Component {

public:
	__CMP_DECL__(ecs::cmp::DRAGANDDROP)
	DragAndDrop();

	DragAndDrop(SimpleCallback Func);

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

	bool usingCallback = false;
	SimpleCallback func;
};

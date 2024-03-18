#pragma once

#include "../architecture/Component.h"
#include <functional>

class Transform;
class Gravity;
class Trigger;

using SimpleCallback = std::function<void()>; // por si quieres q haga algo al soltar

// Este comp permite mover una entity con transform y al soltarlo sobre una
// entity con Trigger, se activan los callbacks de la entidad soltada.
// Es importante NO A�ADIR UN TRIGGER si se ha a�adido este componente antes
// Puedes a�adir un callback para la entidad que arrastras, para ello asignalo
// en la constructora.
// Debes meter un bool diciendo si quieres que se haga callbacks de todas las entidades
// que est�n tocando o solo la que esta mas cercana
class DragAndDrop : public ecs::Component {

public:
	__CMP_DECL__(ecs::cmp::DRAGANDDROP)
	DragAndDrop();
	DragAndDrop(bool usingClosestEnt);
	DragAndDrop(bool usingClosestEnt, SimpleCallback func);

	~DragAndDrop();

	void initComponent() override;

	void update() override;

	void disableInteraction() { canInteract = false; }
	void activateInteraction() { canInteract = true; }
private:
	bool canInteract = true;

	Transform* tr_;
	Gravity* grav_;
	Trigger* tri_;

	bool dragging_;
	float differenceX_;
	float differenceY_;

	// para el escalado al arrastrar objetos
	float porcentajeStart;

	bool usingOnlyClosestEnt_ = false;
	bool usingCallback_ = false;
	SimpleCallback func_;
};

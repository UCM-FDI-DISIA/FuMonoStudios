#pragma once
#include "../architecture/Component.h"
#include "Paquete.h"

class ErrorNote : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::ERROR_NOTE);

	ErrorNote(Paquete*, bool basura, bool tuboIncorrecto);
	~ErrorNote();
};


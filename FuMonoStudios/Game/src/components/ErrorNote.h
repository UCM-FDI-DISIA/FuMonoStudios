#pragma once
#include <architecture/Component.h>
#include <components/Paquete.h>

class ErrorNote : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::ERROR_NOTE)
	std::string text_;
	ErrorNote(Paquete*, bool basura, bool tuboIncorrecto,bool bossEventFail);
	~ErrorNote();
};


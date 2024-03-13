#pragma once
#include "../architecture/Component.h"
#include <functional>

using Callback = std::function<void(ecs::Entity*)>;

using SimpleCallback = std::function<void()>;
// Autodestruye a el entity que está atacheado tras pasar el
// tiempo indicado en TimeToDestroy.
// Si le pasas un callback, lo ejecutará al final
// El tiempo pasado en TimeToDestroy es en segundos !
class SelfDestruct : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::SELFDESTRUCT)

	// el tiempo se pasa en segundos
	SelfDestruct(float TimeToDestroy);
	SelfDestruct(float TimeToDestroy, Callback Call);
	SelfDestruct(float TimeToDestroy, SimpleCallback Call);
	~SelfDestruct();
	void initComponent() override;
	void update() override;
private:
	Callback func_;
	bool usingCallback_ = false;
	SimpleCallback funcSimple_;
	bool usingSimpleCallback_ = false;
	float timer_;
	float startTime_;
	float timeToDestroy_;
};


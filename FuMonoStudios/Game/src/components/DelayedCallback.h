#pragma once
#include "../architecture/Component.h"
#include <functional>

using SimpleCallback = std::function<void()>;

// Este componente ejecuta un callback al pasar
// el tiempo que le metes en la constructora. 
// Es igual al de phaser.
// El tiempo se pasa en SEGUNDOS, por ejemplo,
// si quieres que sea segundo y medio = 1,5
class DelayedCallback : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::DELAYEDCALLBACK)

	DelayedCallback(float time, SimpleCallback call);
	~DelayedCallback();

	void initComponent() override;

	void update() override;

private:
	float timer_;
	float timeToCall_;
	SimpleCallback call_;
};


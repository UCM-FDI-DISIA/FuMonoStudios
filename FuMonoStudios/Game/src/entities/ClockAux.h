#pragma once
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"

class ecs::Entity;
class Transform;
class RenderImage;

// Componente auxiliar para abstraer el comportamiento del
// reloj.
// El reloj gira las manecillas alrededor del reloj en funcion
// del tiempo, y cuando llega a las 21 horas, empiezan a parpadear
// para indicar que queda poco tiempo.
class ClockAux : public ecs::Component
{
public:
    __CMP_DECL__(ecs::cmp::CLOCKAUX)

	ClockAux(float minigameTime);
	virtual ~ClockAux();

	void initComponent() override;

	void update() override;
private:
    float minigameTime;
    float timeMultiplier;
    float hours;
    float minutes;
    Vector2D clockCenter;
    Transform* trManecillaL;
    Transform* trManecillaS;
    // numeros magicos para que roten las manecillas en el centro del reloj (no tocar)
    const float CONST_ROT = 57.3;
    const Vector2D offsetL = Vector2D(-14, -10);
    const float radiusManL = 13.2;
    const Vector2D offsetS = Vector2D(-15, 1);
    const float radiusManS = 6;
    //

    // feedback parpadeo
    float timeBetweenLowTime = 1000;
    bool lowTimeFlag;
    float timerLowTime;
    float timeToUpdateLowTime;
    RenderImage* clockRender;
};


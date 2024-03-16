#pragma once
#include "../architecture/Component.h"
#include "../sdlutils/SDLutils.h"
#include "Transform.h"
#include "DragAndDrop.h"

// El easing EaseOutBack recomendado para la entrada
// del paquete por la derecha 
enum Easing { Linear, EaseOutCubic, EaseOutBack };

// Este componente mueve el transform hacia las coordenadas X
// en un tiempo Y con un easing. El easing es un efecto, pj 
// un muelle o linear.
// Se autodestruira al acabar el movimiento.
// Para entender los easings https://easings.net
// 
// El movTime se mete en segundos 
class MoverTransform : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::MOVERTRANSFORM)

	MoverTransform(Vector2D& newPos, float MovTime, Easing Easing);

	~MoverTransform();

	void initComponent() override;

	void update() override;
private:
	float timer_;
	float startTimer_;
	float movTime_;
	Easing easing_;
	Vector2D finalPos_;
	Vector2D initPos_;
	Transform* mTr_;
};


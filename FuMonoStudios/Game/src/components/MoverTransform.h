#pragma once
#include "../architecture/Component.h"
#include "../sdlutils/SDLutils.h"
#include "Transform.h"
#include "DragAndDrop.h"

// El easing EaseOutBack recomendado para la entrada
// del paquete por la derecha 
enum Easing { Linear, EaseOutCubic, EaseOutBack };

using SimpleCallback = std::function<void()>;

// Este componente mueve el transform hacia las coordenadas X
// en un tiempo Y con un easing. El easing es un efecto, pj 
// un muelle o linear.
// Se autodestruira al acabar el movimiento.
// Para entender los easings https://easings.net
// 
// El movTime se mete en segundos 
// Puedes pasarle un callback para que se ejecute al terminar
// el movertransform. Esto puede ser util para encadenar moverTansforms>
class MoverTransform : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::MOVERTRANSFORM)

	MoverTransform(Vector2D& newPos, float MovTime, Easing Easing);

	MoverTransform(Vector2D& newPos, float MovTime, Easing Easing, SimpleCallback call);

	~MoverTransform();

	void initComponent() override;

	void update() override;
	void enable();
	void disable() { enable_ = false; }

	inline void setEasing(Easing easing) { easing_ = easing; }
	inline void setFinalPos(const Vector2D& pos) { finalPos_ = pos; }
	inline void setMoveTime(float time) { movTime_ = time*1000; }
private:
	float timer_;
	float startTimer_;
	float movTime_;
	bool enable_;
	Easing easing_;
	Vector2D finalPos_;
	Vector2D initPos_;
	Transform* mTr_;

	bool usingCallback;
	SimpleCallback call_;
};


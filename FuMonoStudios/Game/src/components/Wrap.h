#pragma once

#include "../architecture/Component.h"

#include <list>

class Transform;

class Trigger;

//posibles puntos en los que se puede detectar el raton
enum pointRoute {

	LeftUp,
	MiddleUp,
	RightUp,
	LeftMid,
	MiddleMid,
	RightMid,
	LeftDown,
	MiddleDown,
	RightDown

};

class Wrap : public ecs::Component {

public:
	__CMP_DECL__(ecs::cmp::WRAP);

	Wrap(float spaceAux, int repTimesAux, std::list<int> routeAux);

	Wrap(float spaceAux, int repTimesAux);

	Wrap(float spaceAux);

	~Wrap();

	void initComponent() override;

	void update() override;

private:

	void restartRoute();

	Transform* tr_ = nullptr;

	Trigger* tri_ = nullptr;

	//Ruta con los distintos puntos por los que debe pasar el ratón
	std::list<int> route;

	//ultimo punto por el que se a pasado de la ruta
	std::list<int>::iterator lastPoint;

	//radio en el cual se considera que se a pasado por el punto
	float space = 5;

	//repeticiones del patron que hay que hacer para considerarlo envuelto
	int repTimes = 0;

	//si esta envuelto
	bool wrapped = false;

	//debug para futuras implementaciones
	bool debug = true;

};

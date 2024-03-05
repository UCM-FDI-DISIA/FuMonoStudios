#pragma once

#include "../architecture/Component.h"

#include <list>

class Transform;

class Wrap : public ecs::Component {

public:
	__CMP_DECL__(ecs::cmp::WRAP);

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

	Wrap(float spaceAux, std::list<int> routeAux);

	Wrap(float spaceAux);

	~Wrap();

	void initComponent() override;

	void update() override;

private:

	void restartRoute();

	Transform* tr_ = nullptr;

	std::list<int> route;

	std::list<int>::iterator lastPoint;

	float space = 5;

};

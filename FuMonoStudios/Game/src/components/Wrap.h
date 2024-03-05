#pragma once

#include "../architecture/Component.h"

class Transform;

class Wrap : public ecs::Component {

public:
	__CMP_DECL__(ecs::cmp::WRAP);

	Wrap(float spaceAux);

	~Wrap();

	void initComponent() override;

	void update() override;

private:

	Transform* tr_ = nullptr;

	float space = 5;

};

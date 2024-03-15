#pragma once
#include "../architecture/Component.h"
#include "../architecture/Entity.h"
#include "Transform.h"

class Depth : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::DEPTH)

	Depth();
	~Depth();
	void initComponent() override;

	void updateDepth();
	void updateChildPos();
private:
	float depth_;
	Transform* tr_;
};
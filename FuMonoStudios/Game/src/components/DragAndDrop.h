#pragma once

#include "../architecture/Component.h"

class Transform;

class DragAndDrop : public ecs::Component {

public:
	__CMP_DECL__(ecs::cmp::DRAGANDDROP)
	DragAndDrop();

	~DragAndDrop();

	void initComponent() override;

	void update() override;

private:

	Transform* tr_;

	bool dragging;

	float differenceX;

	float differenceY;

};

#pragma once

#include "../architecture/Component.h"

class Transform;

class DragAndDrop : public ecs::Component {

public:

	DragAndDrop();

	~DragAndDrop();

	void initComponent() override;

	void update() override;

private:

	Transform* tr_;

	bool dragging = false;

};

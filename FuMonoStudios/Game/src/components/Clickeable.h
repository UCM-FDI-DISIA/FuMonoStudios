#pragma once

#include "../architecture/Component.h"
#include <functional>
#include <list>

class Transform;

using CallbackClickeable = std::function<void(void)>;

class Clickeable : public ecs::Component {

public:
	__CMP_DECL__(ecs::cmp::CLICKEABLE)
	Clickeable();

	~Clickeable();

	void initComponent() override;

	void update() override;

	void addEvent(CallbackClickeable event );

private:

	Transform* tr_;

	std::list<CallbackClickeable> eventsWhenClick;
};

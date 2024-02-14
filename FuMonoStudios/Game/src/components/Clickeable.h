#pragma once

#include "../architecture/Component.h"
#include <functional>
#include <list>

class Transform;

using Callback = std::function<void(void)>;

class Clickeable : public ecs::Component {

public:

	Clickeable();

	~Clickeable();

	void initComponent() override;

	void update() override;

	void addEvent(Callback & const event );

private:

	Transform* tr_;

	std::list<Callback*> eventsWhenClick;


};

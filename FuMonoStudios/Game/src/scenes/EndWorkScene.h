#pragma once
#include "../architecture/Scene.h"

class EndWorkScene :public ecs::Scene {
public:
	EndWorkScene();
	virtual ~EndWorkScene();
	void init() override;
private:
	Font* font_;
};
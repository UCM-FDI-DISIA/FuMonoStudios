#pragma once
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include <SDL.h>
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

class RenderImage : public ecs::Component
{
public:
	RenderImage(Texture*);
	~RenderImage();
	void initComponent(Transform*);
	void render() const;
private:
	Texture* myTexture;
	Transform* myTransform;
};


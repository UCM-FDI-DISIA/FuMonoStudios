#pragma once
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include <SDL.h>
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../architecture/Entity.h"

class RenderImage : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::IMAGE)
	RenderImage(Texture*);
	~RenderImage();
	void initComponent();
	void render() const;
private:
	Texture* myTexture;
	Transform* myTransform;
};


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
	/// <summary>
	/// Testura a renderizar
	/// </summary>
	Texture* myTexture;
	/// <summary>
	/// transform que actua como destRect para el renderizado
	/// </summary>
	Transform* myTransform;
};


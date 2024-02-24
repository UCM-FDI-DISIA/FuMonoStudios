#pragma once
#include "../architecture/Component.h"

class Transform;
class Texture;

class RenderImage : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::IMAGE)
	RenderImage(Texture*);
	~RenderImage();
	void initComponent() override;
	void render() const;

	void setTexture(Texture* texture);
private:
	/// <summary>
	/// Textura que va a ser renderizada
	/// </summary>
	Texture* myTexture;
	/// <summary>
	/// Transform sobre el que se va a renderizar la imagen
	/// </summary>
	Transform* myTransform;
};


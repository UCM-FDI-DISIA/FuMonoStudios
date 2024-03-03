#pragma once
#include "../architecture/Component.h"

class Transform;
class Texture;

class RenderImage : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::IMAGE)
	RenderImage();
	RenderImage(Texture*);
	~RenderImage();
	void initComponent() override;
	void render() const;
	void setTexture(Texture* texture);
	const Texture* getTexture();
private:
	/// <summary>
	/// Textura que va a ser renderizada
	/// </summary>
	Texture* myTexture;
	/// <summary>
	/// Transform sobre el que se va a renderizar la imagen
	/// </summary>
	Transform* myTransform;
	/// <summary>
	/// Inica si este render image es responsable de destruir la textura que le
	/// pasan
	/// </summary>
	bool ownsTexture_;
};


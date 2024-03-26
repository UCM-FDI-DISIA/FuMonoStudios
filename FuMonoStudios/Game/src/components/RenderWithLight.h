
#pragma once
#include "../architecture/Component.h"

class Transform;
class Texture;
class Clickeable;
class RenderWithLight: public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::IMAGEWITHLIGHT)
	RenderWithLight();
	RenderWithLight(Texture*);
	~RenderWithLight();
	void initComponent() override;
	void render() const;
	void setTexture(Texture* texture);
	const Texture* getTexture();
private:
	/// <summary>
	/// Textura que va a ser renderizada
	/// </summary>
	Texture* mTexture_;
	/// <summary>
	/// Textura del recuadro
	/// </summary>
	Texture* lTexture_;
	/// <summary>
	/// Transform sobre el que se va a renderizar la imagen
	/// </summary>
	Transform* mTr_;
	/// <summary>
	/// Inica si este render image es responsable de destruir la textura que le
	/// pasan
	/// </summary>
	bool ownsTexture_;
};


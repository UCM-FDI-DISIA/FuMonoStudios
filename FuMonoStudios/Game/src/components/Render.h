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
	/// <summary>
	/// Constructora para guardar multiples texturas
	/// </summary>
	/// <param name="textures"></param>
	RenderImage(const std::vector<Texture*>& textures);
	RenderImage(const std::vector<Texture*>& textures, int startIndx);
	~RenderImage();
	void initComponent() override;
	void render() const;
	/// <summary>
	/// cambia la textura 0 (esto es temporal)
	/// </summary>
	/// <param name="texture"></param>
	inline void setTexture(Texture* texture) {texturesVector_[0] = texture; };
	inline void setTexture(int indx) { currentTextureIndx_ = indx; };
	inline void setVector(const std::vector<Texture*>& textures) { texturesVector_ = textures; }
	const Texture* getTexture();
	void nextTexture();
	void previousTexture();
private:
	/// <summary>
	/// indice que indica en que textura del array se encuentra
	/// </summary>
	int currentTextureIndx_;
	/// <summary>
	/// Transform sobre el que se va a renderizar la imagen
	/// </summary>
	Transform* mTr_;
	/// <summary>
	/// Vector de texturas multiples
	/// </summary>
	std::vector<Texture*> texturesVector_;

};


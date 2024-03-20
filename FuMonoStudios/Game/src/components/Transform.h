#pragma once
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include <SDL.h>
#include "../sdlutils/SDLUtils.h"

class Depth;

class Transform : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::TRANSFORM)
		Transform(float x, float y, float w, float h);
		Transform(float x, float y, float w, float h, float rot);
	~Transform();

	/// <summary>
	/// Devuelve un rectangulo correspondiente al espacio del transform
	/// </summary>
	/// <returns></returns>
	SDL_Rect& getRect() const;
	void update();
	void render() const;

	/// <summary>
	/// Devuelve un puntero al padre de este transform
	/// </summary>
	/// <returns></returns>
	Transform* getParent() const;
	/// <summary>
	/// Establece el padre de este transform
	/// </summary>
	/// <param name="newParent">puntero al padre</param>
	void setParent(Transform* newParent);

	/// <summary>
	/// Determina la posicion relativa del objeto
	/// </summary>
	/// <param name="pos"></param>
	void setPos(Vector2D& pos);
	/// <summary>
	/// Determina la posicion relativa del objeto
	/// </summary>
	/// <param name="pos"></param>
	void setPos(float x, float y);

	/// <summary>
	/// Devuelve la posici�n global del objeto
	/// </summary>
	/// <returns></returns>
	Vector2D getPos() const;
	/// <summary>
	/// Devuelve la posicon relativa del objeto
	/// </summary>
	/// <returns></returns>
	Vector2D getRelPos() const;

	/// <summary>
	/// Devuelve posicion del objeto en su centro en
	/// vez de su punta abajo derecha
	/// </summary>
	Vector2D getCenter() const;

	/// <summary>
	/// Devuelve si el rat�n esta encima de la entidad
	/// </summary>
	bool getIfPointerIn() const;
	/// <summary>
	/// Devuelve el ancho del transform
	/// </summary>
	/// <returns></returns>
	float getWidth() const { return width_ * trueScale_; };
	/// <summary>
	/// Devuelve la altura del transform
	/// </summary>
	/// <returns></returns>
	float getHeigth() const { return height_ * trueScale_; };

	void setScale(float Scale) { scale_ = Scale; trueScale_ = Scale; }
	// este solo lo usa el depth
	void setTrueScale(float newScale) { trueScale_ = newScale; } 
	float getScale() { return scale_; }
	float getTrueScale() { return trueScale_; }

	void activateDepth();

	std::list<Transform*> GetChildren() { return childsTr_; }

	void setWidth(float newWidth) { width_ = newWidth; }
	void setHeith(float newHeith) { height_ = newHeith; }

	// esto lo usa el dragNdrop para que funcione con el escalado
	// no es lo mismo del depth, es el porcentaje de escala desde
	// su origen (1)
	float getPorcentajeScale() {
		return ((trueScale_ * 100) / scale_) / 100;
	}

	void setRotation(float newRot) { rotation_ = newRot; }
	float getRotation() { return rotation_; }
private:
	/// <summary>
	/// Posicion relativa (al padre) del objeto
	/// En el caso de no tener padre es la posicion global
	/// </summary>
	Vector2D position_;

	Vector2D relPos_;
	/// <summary>
	/// Ancho del objeto
	/// </summary>
	float width_;
	/// <summary>
	/// Altura del objeto
	/// </summary>
	float height_;

	float scale_;
	float trueScale_;

	// para comunicarse con el en caso de usar depth
	Depth* depthComp_ = nullptr;

	float rotation_;

	/// <summary>
	/// Padre del objeto
	/// </summary>
	Transform* parentTr_ = nullptr;
	/// <summary>
	/// Lista de los hijos del transform
	/// </summary>
	std::list<Transform*> childsTr_;
	/// <summary>
	/// Iterador para borrarse de la lista de trasnforms del padre al destruirse
	/// </summary>
	std::list<Transform*>::iterator parentListIt_;
#ifdef _DEBUG
	SDL_Renderer* renderer_;
#endif // _DEBUG
};


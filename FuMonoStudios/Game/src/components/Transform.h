#pragma once
#include "../architecture/Component.h"
#include "../utils/Vector2D.h"
#include <SDL.h>
#include "../sdlutils/SDLUtils.h"

class Transform : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::TRANSFORM)
		Transform(float x, float y, float w, float h);
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
	float getWidth() const { return width; };
	/// <summary>
	/// Devuelve la altura del transform
	/// </summary>
	/// <returns></returns>
	float getHeigth() const { return height; };

	void setWidth(float newWidth) { width = newWidth; }
	void setHeith(float newHeith) { height = newHeith; }

private:
	/// <summary>
	/// posicion relativa (al padre) del objeto
	/// en el caso de no tener padre es la posicion global
	/// </summary>
	Vector2D position;
	/// <summary>
	/// ancho del objeto
	/// </summary>
	float width;
	/// <summary>
	/// altura del objeto
	/// </summary>
	float height;
	/// <summary>
	/// padre del objeto
	/// </summary>
	Transform* parent;
	/// <summary>
	/// lista de los hijos del transform
	/// </summary>
	std::list<Transform*> childs;
	/// <summary>
	/// iterador para borrarse de la lista de trasnforms del padre al destruirse
	/// </summary>
	std::list<Transform*>::iterator parentListIt;
#ifdef _DEBUG
	SDL_Renderer* renderer;
#endif // _DEBUG
};


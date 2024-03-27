#pragma once
#include <string>
#include <architecture/Scene.h>
#include "../architecture/Entity.h"
#include "../components/Clickeable.h"

/*
Clase a la que llamar para crear objetos que se crean frecuentemente (para no andar copiando y pegando codigo
a lo tonto)

Los metodos devuelven un puntero a la entidad por si se le quiere aplicar mas operaciones en tras crearlo
*/

class ComonObjectsFactory
{
public:
	ComonObjectsFactory(ecs::Scene* sc);
	virtual ~ComonObjectsFactory();
	/// <summary>
	/// establece la capa donde se crearan los objetos usando esta factory
	/// </summary>
	/// <param name="lay"></param>
	void setLayer(ecs::layer::layerId lay) { destLayer_ = lay; }
	/// <summary>
	/// Crea un objeto que contiene varias imágenes si no se le añade tamaño 
	/// se asume el tamaño de la primera textura pasada
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="size"></param>
	/// <param name="textures"></param>
	/// <returns></returns>
	ecs::Entity* createMultiTextureImage(const Vector2D& pos, const Vector2D& size, const std::vector<Texture*>& textures);
	ecs::Entity* createMultiTextureImage(const Vector2D& pos, const std::vector<Texture*>& textures);
	/// <summary>
	/// crea un objeto que contiene texto
	/// </summary>
	/// <param name="scene"></param>
	/// <param name="text"></param>
	/// <param name="fontSize"></param>
	/// <param name="pos"></param>
	/// <returns></returns>
	ecs::Entity* createLabel(const Vector2D& pos,const std::string& text, int fontSize, SDL_Color textColor = build_sdlcolor(0x000000ff));
	/// <summary>
	/// Crea un objeto que es una imagen
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="size">vector que representa el ancho(x) y el alto(y) de la imagen </param>
	/// <param name="texture"></param>
	/// <returns></returns>
	ecs::Entity* createImage(const Vector2D& pos, const Vector2D& size, Texture* texture);
	ecs::Entity* createImage(const Vector2D& pos, Texture* texture);
	/// <summary>
	/// crea un boton asociado a una imagen con un callback ya vinculado
	/// </summary>
	/// <param name="pos"></param>
	/// <param name=""></param>
	/// <param name="texture"></param>
	/// <param name="call"></param>
	/// <returns></returns>
	ecs::Entity* createImageButton(const Vector2D& pos, const Vector2D& size, Texture* texture, CallbackClickeable call);
	/// <summary>
	/// crea un boton a partir de un texto pasado y con un callback ya vinculado
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="text"></param>
	/// <param name="fontSize"></param>
	/// <param name="call"></param>
	/// <param name="textColor"></param>
	/// <returns></returns>
	ecs::Entity* createTextuButton(const Vector2D& pos, const std::string text,
		int fontSize, CallbackClickeable call,SDL_Color textColor = build_sdlcolor(0x000000ff));

private:
	/// <summary>
	/// Scene to create the objects
	/// </summary>
	ecs::Scene* scene_;
	/// <summary>
	/// capa donde se van a crear los objetos
	/// </summary>
	ecs::layer::layerId destLayer_;

	std::vector<Texture*> createdTextures;
};


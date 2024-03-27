#include "ComonObjectsFactory.h"
#include "../components/Transform.h"
#include "../components/Render.h"
#include "../components/Clickeable.h"



ComonObjectsFactory::ComonObjectsFactory(ecs::Scene* sc):scene_(sc), destLayer_(ecs::layer::DEFAULT){}
ComonObjectsFactory::~ComonObjectsFactory()
{
	//futuro sistema de limpieza
	//primero hace falta que las COF sean un atributo de la clase escena
	for (auto t : createdTextures) {
		delete t;
	}
}

ecs::Entity* ComonObjectsFactory::createMultiTextureImage(const Vector2D& pos, const Vector2D& size, const std::vector<Texture*>& textures)
{
	auto entity = scene_->addEntity(destLayer_);
	entity->addComponent<Transform>(pos.getX(), pos.getY(), size.getX(), size.getY());
	entity->addComponent<RenderImage>(textures);
	return entity;
}

ecs::Entity* ComonObjectsFactory::createMultiTextureImage(const Vector2D& pos, const std::vector<Texture*>& textures)
{
	return createMultiTextureImage(pos,Vector2D(textures[0]->width(), textures[0]->height()),textures);
}

ecs::Entity* ComonObjectsFactory::createLabel(const Vector2D& pos, const std::string& text, int fontSize, SDL_Color textColor)
{
#ifdef _DEBUG
	std::cout << "Entidad de texto creada en la capa " << (int)destLayer_ << std::endl;
#endif // _DEBUG
	auto entity = scene_->addEntity(destLayer_);
	Texture* labelText = new Texture(sdlutils().renderer(), text, sdlutils().fonts().at("arial"+std::to_string(fontSize)), textColor);
	createdTextures.push_back(labelText);
	entity->addComponent<Transform>(pos.getX(), pos.getY(), labelText->width(), labelText->height());
	entity->addComponent<RenderImage>(labelText);
	return entity;
}

ecs::Entity* ComonObjectsFactory::createImage(const Vector2D& pos, const Vector2D& size, Texture* texture)
{
#ifdef _DEBUG
	std::cout << "Entidad creada en la capa " << (int)destLayer_ << std::endl;
#endif // _DEBUG
	return createMultiTextureImage(pos, size, { texture });
}

ecs::Entity* ComonObjectsFactory::createImage(const Vector2D& pos, Texture* texture)
{
	return createImage(pos, Vector2D(texture->width(), texture->height()), texture);
}

ecs::Entity* ComonObjectsFactory::createImageButton(const Vector2D& pos, const Vector2D& size, Texture* texture, CallbackClickeable call)
{
	auto entity = createImage(pos,size,texture);
	auto click = entity->addComponent<Clickeable>();
	click->addEvent(call);
	return entity;
}

ecs::Entity* ComonObjectsFactory::createTextuButton(const Vector2D& pos, const std::string text, int fontSize, CallbackClickeable call, SDL_Color textColor)
{
	auto entity = createLabel(pos, text, fontSize);
	auto click = entity->addComponent<Clickeable>();
	click->addEvent(call);
	return entity;
}


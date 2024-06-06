#ifndef DEV_TOOLS
#include <utils/checkML.h>
#endif // !DEV_TOOLS
#include "ComonObjectsFactory.h"
#include <components/Render.h>
#include <components/HoverSensorComponent.h>
#include <components/RenderWithLight.h>

ComonObjectsFactory::ComonObjectsFactory(ecs::Scene* sc):scene_(sc), destLayer_(ecs::layer::DEFAULT),fontName_("arial"){}
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
#ifdef _DEBUG
	std::cout << "Entidad multitextura creada en la capa " << (int)destLayer_ << std::endl;
#endif // _DEBUG
	entity->addComponent<Transform>(pos.getX(), pos.getY(), size.getX(), size.getY());
	entity->addComponent<RenderImage>(textures);
	return entity;
}

ecs::Entity* ComonObjectsFactory::createMultiTextureImage(const Vector2D& pos, const std::vector<Texture*>& textures)
{
	return createMultiTextureImage(pos,Vector2D(textures[0]->width(), textures[0]->height()),textures);
}

ecs::Entity* ComonObjectsFactory::createLabel(const Vector2D& pos , const std::string& text, int fontSize, SDL_Color textColor_)
{
	return createImage(pos,createTextTexture(text,fontSize,textColor_));
}
ecs::Entity* ComonObjectsFactory::createLabel(const Vector2D& pos,Uint32 width, const std::string& text, int fontSize, SDL_Color textColor_)
{
	return  createImage(pos, createTextTexture(text, fontSize, textColor_,width));
}
ecs::Entity* ComonObjectsFactory::createLabel(const Vector2D& pos, const Vector2D& size, const std::string& text, int fontSize, SDL_Color textColor_)
{
	return createImage(pos, size, createTextTexture(text,fontSize,textColor_,size.getX()));
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

ecs::Entity* ComonObjectsFactory::createImageButton(const Vector2D& pos, const Vector2D& size, Texture* texture, 
	CallbackClickeable call,const std::string& soundClick)
{
	auto entity = createImage(pos,size,texture);
	makeButton(entity, call, soundClick);
	return entity;
}

ecs::Entity* ComonObjectsFactory::createMultiTextureButton(const Vector2D& pos, const Vector2D& size, const std::vector<Texture*>& textures,
    CallbackClickeable call, const std::string& soundClick)
{
	auto entity = createMultiTextureImage(pos, size, textures);
	makeButton(entity, call, soundClick);
	return entity;
}

ecs::Entity* ComonObjectsFactory::createTextuButton(const Vector2D& pos, const std::string& text, int fontSize, CallbackClickeable call, 
                                                    const std::string& soundClick, SDL_Color textColor_)
{
	auto entity = createLabel(pos, text, fontSize,textColor_);
	makeButton(entity, call, soundClick);
	return entity;
}

void ComonObjectsFactory::addHoverColorMod(ecs::Entity* entity, SDL_Color c)
{
	HoverSensorComponent* hover = entity->getComponent<HoverSensorComponent>();
	if (hover== nullptr) {
		hover = entity->addComponent<HoverSensorComponent>();
	}
	//posiblemente meter en un metodo que agregue esta propiedad
	auto texture = entity->getComponent<RenderImage>()->getCurrentTexture();
	auto baseColor = texture->getCurrentColor();
	hover->addInCall([texture, c]() {texture->modColor(c.r, c.g, c.b); });
	auto recoverColor = [texture, baseColor]() {texture->modColor(baseColor.r,baseColor.g,baseColor.b); };
	hover->addOutCall(recoverColor);
	hover->addDestoryCall(recoverColor);
}

void ComonObjectsFactory::addHilghtOnHover(ecs::Entity* entity)
{
	HoverSensorComponent* hover = entity->getComponent<HoverSensorComponent>();
	if (hover == nullptr) {
		hover = entity->addComponent<HoverSensorComponent>();
	}
	//añade feeback al pasar el raton por encima
	auto light = entity->addComponent<RenderWithLight>();
	hover = entity->addComponent<HoverSensorComponent>();
	hover->addInCall([light]() {light->lightOn(); });
	hover->addOutCall([light]() {light->lightOff(); });

	Clickeable* click = entity->getComponent<Clickeable>();
	if(click != nullptr)
		click->addEvent([light]() {light->lightOff(); });
}

Texture* ComonObjectsFactory::createTextTexture(const std::string& text, int fontSize, SDL_Color c,int width)
{
	Texture* nText;
	if(width == 0)
		nText = new Texture(sdlutils().renderer(), text, sdlutils().fonts().at(fontName_ + std::to_string(fontSize)), build_sdlcolor(0xffffffff));
	else if (width > 0) {
		nText = new Texture(sdlutils().renderer(), text, sdlutils().fonts().at(fontName_ + std::to_string(fontSize)), build_sdlcolor(0xffffffff), width);
	}
	else {
		throw "Invalid Texture Width";
	}
	nText->modColor(c.r, c.g, c.b);
	createdTextures.push_back(nText);
	return nText;
}

void ComonObjectsFactory::makeButton(ecs::Entity* entity, CallbackClickeable call, std::string clickSound)
{
	auto click = entity->addComponent<Clickeable>(clickSound);
	click->addEvent(call);
}


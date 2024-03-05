#include "ComonObjectsFactory.h"
#include "../components/Transform.h"
#include "../components/Render.h"

ecs::Entity* ComonObjectsFactory::createLabel(ecs::Scene* scene, const Vector2D& pos, const std::string& text, int fontSize, SDL_Color textColor)
{
	auto entity = scene->addEntity();
	Texture* labelText = new Texture(sdlutils().renderer(), text, sdlutils().fonts().at("arial"+std::to_string(fontSize)), textColor);
	entity->addComponent<Transform>(pos.getX(), pos.getY(), labelText->width(), labelText->height());
	entity->addComponent<RenderImage>(labelText);
	return entity;
}

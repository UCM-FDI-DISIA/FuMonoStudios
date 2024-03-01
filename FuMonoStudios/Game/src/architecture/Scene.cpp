#include "Scene.h"
#include "Entity.h"
#include "../components/Transform.h"
#include <iostream>
namespace ecs {
	Scene::Scene():objs_() {
		
	}
	Scene::~Scene() {
		for (auto ly : objs_) {
			for(auto e : ly)
				delete e;
		}
		//std::cout << "Se Destruyo correctamente la escena"<<std::endl;
	}

	void Scene::init()
	{
	}
	void Scene::update() {
		//std::cout << "Hola" << std::endl;
		for (auto ly : objs_)
			for(auto e : ly)
				e->update();
	}
	void Scene::render() {
		for (auto ly : objs_)
			for(auto e : ly)
				e->render();
	}
	Entity* Scene::addEntity(ecs::layer::layerId lyId)
	{
		Entity* e = new Entity(this);
		e->setAlive(true);
		objs_[lyId].push_back(e);
		return e;
	}
	void Scene::addEntityToColisionList(Entity* e) {

		colisionEntities.push_back(e);

	}
	bool Scene::checkColisions(Entity* e) {

		bool ret = false;

		for (auto it = colisionEntities.begin(); it != colisionEntities.end(); ++it) {

			if ((*it) != e) {

				if (SDL_HasIntersection(e->getComponent<Transform>()->getRect(), (*it)->getComponent<Transform>()->getRect())) {

					e->getComponent<Trigger>()->touchEntity((*it));

					ret = true;

				}

			}

		}

		return ret;

	}
	void Scene::refresh()
	{
		//objs_.erase(
		//	std::remove_if(ents_.begin(), ents_.end(), [](Entity* e) {
		//		if (e->isAlive()) {
		//			return false;
		//		}
		//		else {
		//			delete e;
		//			return true;
		//		}
		//		}), //
		//	ents_.end());
	}
}

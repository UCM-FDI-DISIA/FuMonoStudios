#include "Scene.h"
#include "Entity.h"
#include <iostream>
namespace ecs {
	Scene::Scene():objs_() {
		
	}
	Scene::~Scene() {
		for (auto ly : objs_) {
			for(auto e : ly)
				delete e;
		}
		std::cout << "Se Destruyo correctamente la escena"<<std::endl;
	}

	/// <summary>
	/// Metodo llamado al cargar una escena (similar al de Phaser)
	/// </summary>
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

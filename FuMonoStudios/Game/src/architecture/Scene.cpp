#include "Scene.h"
#include "Entity.h"
#include <iostream>
namespace ecs {
	Scene::Scene():objs_() {
		
	}
	Scene::~Scene() {
		for (auto e : objs_) {
			delete e;
		}
		//std::cout << "Se Destruyo correctamente la escena"<<std::endl;
	}

	/// <summary>
	/// Metodo llamado al cargar una escena (similar al de Phaser)
	/// </summary>
	void Scene::init()
	{
	}
	void Scene::update() {
		//std::cout << "Hola" << std::endl;
		for (auto e : objs_)
			e->update();
	}
	void Scene::render() {
		for (auto e : objs_)
			e->render();
	}
	Entity* Scene::addEntity()
	{
		Entity* e = new Entity(this);
		e->setAlive(true);
		objs_.push_back(e);
		return e;
	}
}

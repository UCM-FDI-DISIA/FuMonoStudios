#include "Scene.h"
namespace ecs {
	Scene::Scene():objs_() {
		
	}
	Scene::~Scene() {

	}
	void Scene::init() {

	}
	void Scene::update() {
		for (auto& e : objs_)
			;//e.update();
	}
	void Scene::render() {
		for (auto& e : objs_)
			;//e.render()
	}
}

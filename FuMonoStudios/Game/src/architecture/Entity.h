#pragma once
#include "ecs.h"
#include <algorithm>
#include <array>
#include "Component.h"
#include "Scene.h"
//class Manager;

namespace ecs {
	class Entity
	/*
	TODO:
	Hacer metodos:
		handleInput(SDL_Event& event)???
	*/
	{
	public:
		Entity(Scene* scene) : scene_(scene), cmps_(), currCmps_(), alive_() {
			currCmps_.reserve(cmp::maxComponentId);
		};

		virtual ~Entity() {
			for (auto c : currCmps_) {
				delete c;
			}
			std::cout << "Entidad destruida"<<std::endl;
		};

		inline bool isAlive() const { return alive_; };

		inline void setAlive(bool alive) { alive_ = alive; };

		//ACCESOR AL MANAGER (Luis va a hacer cositas)
		inline Scene* getMngr() const { return scene_; };


		/// <summary>
		/// Añade un componente a Entity
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <typeparam name="...Ts"></typeparam>
		/// <param name="cId">Identificador del componente</param>
		/// <param name="...args">Argumentos de la constructora del componente a añadir</param>
		/// <returns>Puntero al componente creado</returns>
		template<typename T, typename ...Ts>
		inline T* addComponent(ecs::cmpId_t cId, Ts&&... args) {
			T* c = new T(std::forward<Ts>(args)...);

			removeComponent(cId);

			currCmps_.push_back(c);
			cmps_[cId] = c;

			c->setContext(this);
			c->initComponent();

			return c;
		}

		//Remueve el componente de Entity marcado por cId
		inline void removeComponent(ecs::cmpId_t cId) {
			if (cmps_[cId] != nullptr) {
				auto iter = std::find(currCmps_.begin(),
					currCmps_.end(),
					cmps_[cId]);
				currCmps_.erase(iter);
				delete cmps_[cId];
				cmps_[cId] = nullptr;
			}
		}

		//Devuelve referencia al componente de Entity marcado por cId
		template<typename T>
		inline T* getComponent(ecs::cmpId_t cId) {
			return static_cast<T*>(cmps_[cId]);
		}
		//Comprueba si Entity tiene el componente marcado por cId
		inline bool hasComponent(ecs::cmpId_t cId) {
			return cmps_[cId] != nullptr;
		}

		inline void update() {
			auto n = currCmps_.size();
			for (auto i = 0u; i < n; i++) {
				currCmps_[i]->update();
			}
			//std::cout << "Entidad Update" << std::endl;
		}

		inline void render() {
			auto n = currCmps_.size();
			for (auto i = 0u; i < n; i++) {
				currCmps_[i]->render();
			}
		}

	private:
		bool alive_;
		Scene* scene_;
		std::vector<Component*> currCmps_;
		std::array<Component*, cmp::maxComponentId> cmps_;
	};

}


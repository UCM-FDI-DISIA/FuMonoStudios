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
		inline T* addComponent(Ts&&... args) {
			T* c = new T(std::forward<Ts>(args)...);

			removeComponent<T>();

			currCmps_.push_back(c);
			cmps_[cmpId<T>] = c;

			c->setContext(this);
			c->initComponent();

			return c;
		}

		//Remueve el componente de Entity marcado por cId
		template<typename T>
		inline void removeComponent() {
			if (cmps_[cmpId<T>] != nullptr) {
				auto iter = std::find(currCmps_.begin(),
					currCmps_.end(),
					cmps_[cmpId<T>]);
				currCmps_.erase(iter);
				delete cmps_[cmpId<T>];
				cmps_[cmpId<T>] = nullptr;
			}
		}

		//Devuelve referencia al componente de Entity marcado por cId
		template<typename T>
		inline T* getComponent() {

			// the component id
			constexpr cmpId_t cId = cmpId<T>;
			static_assert(cId < ecs::cmp::maxComponentId);

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

		inline std::vector<Entity*> getChildren() const {
			return children;
		}

		Entity* getParent() const {
			return parent;
		}

		// Los objetos solo pueden tener un único padre
		void setParent(Entity* newParent) {
			if (parent != nullptr) {
				parent->removeChild(this);
			}
			parent = newParent;
			if (parent != nullptr) {
				parent->addChild(this);
			}
		}

		void addChild(Entity* child) {
			children.push_back(child);
			child->setParent(this);
		}

		void removeChild(Entity* child) {
			auto it = std::find(children.begin(), children.end(), child);
			if (it != children.end()) {
				children.erase(it);
				child->setParent(nullptr);
			}
		}

	private:
		bool alive_;
		Scene* scene_;
		std::vector<Component*> currCmps_;
		std::array<Component*, cmp::maxComponentId> cmps_;
		Entity* parent;
		std::vector<Entity*> children;
	};

}


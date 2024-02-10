#pragma once
#include "ecs.h"
#include <algorithm>
#include <array>

class Manager;

namespace ecs {
	/*
	TODO:
	Hacer metodos:
		update()
		render()
		handleInput(SDL_Event& event)???
	*/
	class Entity
	{
	public:
		Entity(Manager* mngr) : mngr_(mngr), cmps_(), currCmps_(), alive_() {
			currCmps_.reserve(cmp::maxComponentId);
		};

		virtual ~Entity() {
			for (auto c : currCmps_) {
				delete c;
			}
		};

		inline bool isAlive() const;

		inline void setAlive(bool alive) { alive_ = alive; };

		//ACCESOR AL MANAGER (Luis va a hacer cositas)
		//Manager* getMngr() const;


		/// <summary>
		/// Añade un componente a Entity
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <typeparam name="...Ts"></typeparam>
		/// <param name="cId">Identificador del componente</param>
		/// <param name="...args">Argumentos de la constructora del componente a añadir</param>
		/// <returns>Puntero al componente creado</returns>
		template<typename T, typename ...Ts>
		inline T* addComponent(cmpId_t cId, Ts&&... args) {
			T* c = new T(std::forward<Ts>(args)...);

			removeComponent(cId);

			currCmps_.push_back(c);
			cmps_[cId] = c;

			c->setContext(this);
			c->initComponent();

			return c;
		}

		//Remueve el componente de Entity marcado por cId
		inline void removeComponent(cmpId_t cId) {
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
		inline bool hasComponent(cmpId_t cId) {
			return cmps_[cId] != nullptr;
		}

		inline void update() {
			auto n = currCmps_.size();
			for (auto i = 0u; i < n; i++) {
				currCmps_[i]->update();
			}
		}

		inline void render() {
			auto n = currCmps_.size();
			for (auto i = 0u; i < n; i++) {
				currCmps_[i]->render();
			}
		}

	private:
		bool alive_;
		Manager* mngr_;
		std::vector<Component*> currCmps_;
		std::array<Component*, cmp::maxComponentId> cmps_;
	};

}


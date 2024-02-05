#pragma once
#include "ecs.h"

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
		Entity(Manager* mng);
		virtual ~Entity();
		inline bool isAlive() const;
		inline void setAlive();
		Manager* getMngr() const;

		template<typename T, typename ...Ts>
		inline T* addComponent(cmpId_t cId, Ts&&... args) {
			T* c = new T(std::forward<Ts>(args)…);

			removeComponent(cId);

			currCmps_.push_back(c);
			cmps_[cId] = c;

			c->setContext(this);
			c->initComponent();

			return c;
		}

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

		template<typename T>
		inline T* getComponent(ecs::cmpId_t cId) {
			return static_cast<T*>(cmps_[cId]);
		}
		inline bool hasComponent(cmpId_t cId) {
			return cmps_[cId] != nullptr;
		}

	private:
		bool alive_;
		Manager* mngr_;
		std::vector<Component*> currCmps_;
		std::array<Component*, ecs::maxComponentId> cmps_;
	};

}


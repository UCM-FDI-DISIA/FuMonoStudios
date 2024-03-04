#pragma once
#include "ecs.h"
#include <algorithm>
#include <array>
#include "Component.h"
#include "Scene.h"
#include "../components/Trigger.h"
#include "../components/DragAndDrop.h"
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

		Entity(Scene* scene, ecs::layer::layerId ly) : scene_(scene), cmps_(), currCmps_(), alive_(), myLayer(ly),enable_(true),active_(true) {
			currCmps_.reserve(cmp::maxComponentId);
		};

		virtual ~Entity() {
			for (auto c : currCmps_) {
				delete c;
			}
			//std::cout << "Entidad destruida"<<std::endl;
		};

		inline bool isAlive() const { return alive_; };

		inline bool isActive() const { return active_; };

		inline bool isEnable() const { return enable_; };

		inline void setAlive(bool alive) { alive_ = alive; };

		inline void setActive(bool active) { active_ = active; };

		inline void setEnable(bool enable) { enable_ =enable; };

		//ACCESOR AL MANAGER (Luis va a hacer cositas)
		inline Scene* getMngr() const { return scene_; };

		//Modelo predeterminado del add entity al cual se mete pasandole cualquier valor excepto los especificos declarados justo debajo
		template<typename T, typename ...Ts>
		inline T* addComponent(Ts&&... args) {

			T* c = addComponent_aux<T>(args...);

			return c;

		}

		//sobreescritura del add component especificando funcionalidad extra necesaria para el Trigger
		template<>
		inline Trigger* addComponent<Trigger>() {

			Trigger* t = addComponent_aux<Trigger>(scene_->addEntityToColisionList(this));

			return t;

		}

		//sobreescritura del add component especificando funcionalidad extra necesaria para el Trigger
		template<>
		inline DragAndDrop* addComponent<DragAndDrop>() {


			Trigger* trg = getComponent<Trigger>();

			if (trg != nullptr)
				throw std::runtime_error("Entidad con trigger asignado DragAndDrop (el dragnDrop lo asigna automaticamente))");

			addComponent<Trigger>();

			DragAndDrop* d = addComponent_aux<DragAndDrop>();

			return d;

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

		inline ecs::layer::layerId getLayer() {
			return myLayer;
		}

		inline void addIterator(std::vector<Entity*>::iterator it) {
			mIt_ = it;
		}

		inline std::vector<Entity*>::iterator getIterator() {
			return mIt_;
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
		bool active_;
		bool enable_;
		Scene* scene_;
		std::vector<Entity*>::iterator mIt_;
		ecs::layer::layerId myLayer = ecs::layer::DEFAULT;
		std::vector<Component*> currCmps_;
		std::array<Component*, cmp::maxComponentId> cmps_;


		/// <summary>
		/// A�ade un componente a Entity
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <typeparam name="...Ts"></typeparam>
		/// <param name="cId">Identificador del componente</param>
		/// <param name="...args">Argumentos de la constructora del componente a a�adir</param>
		/// <returns>Puntero al componente creado</returns>
		template<typename T, typename ...Ts>
		inline T* addComponent_aux(Ts&&... args) {
			T* c = new T(std::forward<Ts>(args)...);

			removeComponent<T>();

			currCmps_.push_back(c);
			cmps_[cmpId<T>] = c;

			c->setContext(this);
			c->initComponent();

			return c;
		}
	};

}


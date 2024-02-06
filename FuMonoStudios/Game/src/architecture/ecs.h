#pragma once
#include <vector>

class Entity;

namespace ecs {

	using cmpId_t = uint8_t;
	namespace cmp {
		enum cmpId : cmpId_t {
			TRANSFORM = 0,
			IMAGE,
			CTRL,
			// do not remove this
			_LAST_CMP_ID
		};
		constexpr cmpId_t maxComponentId = _LAST_CMP_ID;
	}

	class Component {
	public:
		Component() : ent_() {}
		virtual ~Component() {}
		inline void setContext(Entity* ent) {
			ent_ = ent;
		}

		virtual void initComponent() {};
		virtual void update() {};
		virtual void render() {};
	protected:
		Entity* ent_;
	};

	class Manager {

	};
}


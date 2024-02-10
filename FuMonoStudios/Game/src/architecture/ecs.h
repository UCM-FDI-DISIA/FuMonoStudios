#pragma once
#include <vector>

class Entity;

namespace ecs {

	using cmpId_t = uint8_t;
	//Namespace que contiene los IDs de todos los componentes
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

	using scId_t = uint8_t;
	//Namespace para etiquetar las escenas
	namespace sc {
		enum sceneId : scId_t {
			MAIN_SCENE,
			EXPLORE_SCENE,
			_LAST_SCENE
		};
		constexpr sceneId maxSceneId = _LAST_SCENE;
	}
}


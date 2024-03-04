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
			CLICKEABLE,
			DRAGANDDROP,
			TRIGGER,
			PAQUETE,
			CHECKER,
			HERRAMIENTAS,
			MULTIPLETEXTURES,
			GRAVITY,
			DIALOGUE,
			MOVERTRANSFORM,
			// do not remove this
			_LAST_CMP_ID
		};
		constexpr cmpId_t maxComponentId = _LAST_CMP_ID;
	}

	template<typename T>
	constexpr cmpId_t cmpId = T::id;


	using scId_t = uint8_t;
	//Namespace para etiquetar las escenas
	namespace sc {
		enum sceneId : scId_t {
			MAIN_SCENE,
			EXPLORE_SCENE,
			MENU_SCENE,
			_LAST_SCENE
		};
		constexpr sceneId maxSceneId = _LAST_SCENE;
	}

	using lyId_t = uint8_t;
	//Namespace de las capas
	//El orden de las capas es de atr�s hacia adelante;
	namespace layer {
		enum layerId : lyId_t
		{
			BACKGROUND,
			DEFAULT,
			PACKAGE,
			STAMP,
			OFFICEELEMENTS,
			MANUAL,
			FOREGROUND,
			UI,
			_LAST_LAYER
		};
		constexpr layerId maxLayerId = _LAST_LAYER;
	}
	// a macro for component identifier declaration, e.g., __CMPID_DECL__(ecs::_TRANSFORM)
	// expands to:
	//
	//   constexpr static ecs::cmpId_type id = ecs::_TRANSFORM;
	//
	#define __CMP_DECL__(cId) constexpr static ecs::cmpId_t id = cId;
}


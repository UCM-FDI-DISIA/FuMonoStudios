#pragma once
#include "../components/Paquete.h"
#include "../components/PackageChecker.h"
#include "../architecture/Entity.h"
#include "../architecture/Scene.h"
#include <stdlib.h>
#include "../sdlutils/VirtualTimer.h"
#include "../architecture/GeneralData.h"
#include "../scenes/MainScene.h"
#include "../components/Render.h"
#include "../components/MoverTransform.h"
#include "../components/SelfDestruct.h"
#include "../components/Gravity.h"
#include <vector>

class PipeFactory
{
public:
	PipeFactory() {
		srand(sdlutils().currRealTime());
	}
	~PipeFactory() {}

	/// <summary>
	/// Call this method to build the pipe objects onto the selected scene.
	/// </summary>
	/// <param name="mScene"> Reference to Scene to build on </param>
	void createPipes(ecs::MainScene* mScene);
private:
	void createPipe(ecs::MainScene*, pq::Distrito, bool);
	//void addExtraConditions(); Pa luego, hay que hablar de arquitectura y de porros

	//std::vector<int> currentExtraConditions;
};


#pragma once
#include "../components/Paquete.h"
#include "../components/PackageChecker.h"
#include "../architecture/Entity.h"
#include "../architecture/Scene.h"
#include <stdlib.h>
#include "../sdlutils/VirtualTimer.h"
#include "../architecture/GeneralData.h"

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
	/// <param name="day"> Number of current day </param>
	/// <param name="mScene"> Reference to Scene to build on </param>
	void createPipes(Scene* mScene);
private:
	void createPipe(Scene*, Paquete::Distrito, bool);
	//void addExtraConditions(); Pa luego, hay que hablar de arquitectura y de porros
};


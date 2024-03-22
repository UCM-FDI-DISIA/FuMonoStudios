#include "ClockAux.h"
#include "../architecture/Entity.h"
#include "../architecture/Scene.h"
#include "../components/Render.h"
#include "../components/Transform.h"
#include "../architecture/Time.h"

ClockAux::ClockAux(float MinigameTime) {
	minigameTime = MinigameTime;
	hours = 0;
	minutes = 0;
	timeMultiplier = (1440 / MinigameTime) * Time::getDeltaTime();
	trManecillaL = nullptr;
	trManecillaS = nullptr;
	lowTimeFlag = false;
}

ClockAux::~ClockAux() {

}

void ClockAux::initComponent() {
	ecs::Scene* mngr = ent_->getMngr();

	ent_->addComponent<Transform>(1340, 510, 210, 140, 0);
	clockRender = ent_->addComponent<RenderImage>(&sdlutils().images().at("reloj"));

	ecs::Entity* manecillaL = mngr->addEntity(ecs::layer::BACKGROUND);
	trManecillaL = manecillaL->addComponent<Transform>(1430, 555, 25, 40);
	manecillaL->addComponent<RenderImage>(&sdlutils().images().at("manecillaL"));

	ecs::Entity* manecillaS = mngr->addEntity(ecs::layer::BACKGROUND);
	trManecillaS = manecillaS->addComponent<Transform>(1435, 580, 25, 15, 0);
	manecillaS->addComponent<RenderImage>(&sdlutils().images().at("manecillaS"));

	clockCenter = ent_->getComponent<Transform>()->getCenter();
}

void ClockAux::update() {
	timeMultiplier = (1440 / minigameTime) * Time::getDeltaTime();

	// numeros que aplicados hacen representar bien las horas y minutos
	float x = ((minutes - 15) / 9.55);
	float y = ((hours - 6) / 3.82);

	trManecillaL->setPos(clockCenter.getX() + offsetL.getX() + radiusManL * cos(x),
		clockCenter.getY() + offsetL.getY() + radiusManL * sin(x));
	trManecillaL->setRotation(90 + x * CONST_ROT);

	trManecillaS->setPos(clockCenter.getX() + offsetS.getX() + radiusManS * cos(y),
		clockCenter.getY() + offsetS.getY() + radiusManS * sin(y));
	trManecillaS->setRotation(y * CONST_ROT);

	minutes += timeMultiplier * 1;
	hours += timeMultiplier * 0.01666;


	if (hours > 18)
	{
		timerLowTime = sdlutils().currRealTime();

		if (timerLowTime > timeToUpdateLowTime)
		{
			clockRender->setTexture(&sdlutils().images().at(lowTimeFlag ? "reloj2" : "reloj"));
			timeToUpdateLowTime = sdlutils().currRealTime() + timeBetweenLowTime;
			lowTimeFlag = !lowTimeFlag;
		}
	}

	//std::cout << "y: " << y << " x:" << x << std::endl;
	//std::cout << "horas " << hours << " minutes: " << minutes << std::endl;
}
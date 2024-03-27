#include "PipeFactory.h"
#include "../components/Paquete.h"
#include "../architecture/Entity.h"
#include <stdlib.h>
#include "../sdlutils/VirtualTimer.h"
#include "../architecture/GeneralData.h"

void PipeFactory::createPipes(ecs::MainScene* mScene) {
	int numTubos = generalData().getTubesAmount(); // coge el numero de tubos que están desbloqueados
	int j = 0;
	for (int i = 0; i < numTubos; i++) {
		createPipe(mScene, (pq::Distrito)i, true);
		j++;
	}
	//Creación de paquetes bloqueados
	for (int z = j; z < 7; z++) {
		createPipe(mScene, (pq::Distrito)z, false);
	}
}

void PipeFactory::createPipe(ecs::MainScene* mScene, pq::Distrito toDis, bool disponible) {
	float scaleTubos = 0.3f;
	ecs::Entity* tuboEnt = mScene->addEntity(ecs::layer::BACKGROUND);
	Texture* texTubo = &sdlutils().images().at("tubo" + std::to_string(toDis + 1));

	Transform* tuboTr = tuboEnt->addComponent<Transform>(75 + (220 * toDis), -40, texTubo->width(), texTubo->height());
	tuboTr->setScale(scaleTubos);
	tuboEnt->addComponent<RenderImage>(texTubo);

	if (disponible) {
		Trigger* tuboTri = tuboEnt->addComponent<Trigger>();
		PackageChecker* tuboCheck = tuboEnt->addComponent<PackageChecker>(toDis);
		tuboTri->addCallback([this, mScene, toDis, tuboCheck](ecs::Entity* entRec) {
			//comprobamos si es un paquete
			Transform* entTr = entRec->getComponent<Transform>();
			if (entRec->getComponent<Paquete>() != nullptr) {
				entRec->removeComponent<Gravity>();
				entRec->addComponent<MoverTransform>( // animación básica del paquete llendose
					entTr->getPos() + Vector2D(0, -600), 1.5, Easing::EaseOutCubic);
				entRec->addComponent<SelfDestruct>(1, [this]() {
					generalData().correctPackage();
					//createPaquete(generalData().getPaqueteLevel());
					});
				if (tuboCheck->checkPackage(entRec->getComponent<Paquete>())) {
					//correct_++;
				}
				else {
					//fails_++;
				}
#ifdef _DEBUG
				//updateFailsText();
				std::cout << "crazy! " << toDis << std::endl;
#endif // _DEBUG

			}

			});
		tuboCheck->addCondition([toDis](Paquete* paqRec) -> bool {
			return paqRec->getDistrito() == toDis;
			});
	}
	else {
		ecs::Entity* cruzEnt = mScene->addEntity(ecs::layer::UI);
		Texture* texCruz = &sdlutils().images().at("cruz");

		Transform* cruzTr = cruzEnt->addComponent<Transform>(75 + (220 * toDis), 120, texCruz->width(), texCruz->height());
		cruzTr->setScale(0.2f);
		cruzEnt->addComponent<RenderImage>(texCruz);
	}

#ifdef _DEBUG
	std::cout << "Creado el tubo  " << toDis << std::endl;
#endif // _DEBUG
}
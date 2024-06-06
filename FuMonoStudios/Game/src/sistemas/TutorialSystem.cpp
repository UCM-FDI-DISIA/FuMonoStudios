#ifndef DEV_TOOLS
#include <utils/checkML.h>
#endif // !DEV_TOOLS
#include "TutorialSystem.h"
#include <scenes/TutorialScene.h>
#include <architecture/Game.h>

TutorialSystem::TutorialSystem(ecs::TutorialScene* scene) {
	scene_ = scene;
	
}

TutorialSystem::~TutorialSystem() {

}

void TutorialSystem::update() {
	if (waitingCallback)
	{
		timer_ = sdlutils().virtualTimer().currTime();
		if (timer_ > timeToCall_)
		{
			waitingCallback = false;
			call_();
		}
	}

	if (waitingEmbalaje) {
		if (waitingWrapComp->isWrapped())
		{
			waitingEmbalaje = false;
			notifyAction(Action::Embalado);
		}
	}

	if (waitingPesado) {

		if (scene_->balanzaUsed) {
			waitingPesado = false;
			notifyAction(Action::Pesado);
		}

	}
}

void TutorialSystem::activateEvent(TutorialEvent event) {

	currentEvent = event;
	tutorialIteration = (int)event;
	switch (event)
	{
		#pragma region Manual
		case TutorialEvent::Introduction:
			scene_->deactivateTubos();
			canPassPagesManual = false;
			DragAndDrop::enableDrag = false;
			activateDialogue(false);
			break;
		case TutorialEvent::SacaElManual1:
			DragAndDrop::enableDrag = false;
			activateDialogue(false);
			arrow_->setActive(true);
			
			// animacion de la flecha
			arrow_->getComponent<Transform>()->setPos(1350, 425);
			arrow_->getComponent<Transform>()->setRotation(130);
			arrow_->addComponent<MoverTransform>(Vector2D(800, 700), 1, Easing::EaseOutBack);
			arrow_->getComponent<MoverTransform>()->enable();

			delayedCallback(1.2, [this]() {
				arrow_->getComponent<Transform>()->setPos(1350, 425);
				arrow_->addComponent<MoverTransform>(Vector2D(800, 700), 1, Easing::EaseOutBack, [this]() {
					arrow_->getComponent<Transform>()->setPos(1350, 425);
					});
				arrow_->getComponent<MoverTransform>()->enable();
				});
			break;
		case TutorialEvent::SacaElManual2:
			DragAndDrop::enableDrag = false;
			activateDialogue(false);
			break;

#pragma endregion

		#pragma region Primer Paquete
		case TutorialEvent::PaqueteEnsenarRemitente:
			scene_->getManual()->getComponent<DragAndDrop>()->disable();
			DragAndDrop::enableDrag = false;
			scene_->createPackage(ecs::TutorialScene::Primero);
			delayedCallback(1, [this]() {
				activateDialogue(false);
				delayedCallback(0.2, [this]() {
					arrow_->setActive(true);
					arrow_->getComponent<Transform>()->setPos(1340, 720);
					});
				});
			break;
		case TutorialEvent::PaqueteEnsenarCodigoPostal:
			activateDialogue(false);
			arrow_->getComponent<Transform>()->setPos(1340, 680);
			break;
		case TutorialEvent::PaqueteBuscarPaginaCodigosPostales:
			activateDialogue(false);
			break;
		case TutorialEvent::BuscarPaginaHestia:
			arrow_->setActive(false);
			arrow_->getComponent<Transform>()->setRotation(130);
			canPassPagesManual = false;
			activateDialogue(false);
			break;
		case TutorialEvent::EnsenarSellos:

			DragAndDrop::enableDrag = false;
			canPassPagesManual = false;
			activateDialogue(true);
			arrow_->setActive(true);
			arrow_->getComponent<Transform>()->setPos(350, 850);
			arrow_->addComponent<MoverTransform>(Vector2D(100, 850), 1, Easing::EaseOutBack);
			arrow_->getComponent<MoverTransform>()->enable();
			delayedCallback(1.2, [this]() {
				arrow_->addComponent<MoverTransform>(Vector2D(350, 850), 1, Easing::EaseOutBack);
				arrow_->getComponent<MoverTransform>()->enable();
				});
			break;

		case TutorialEvent::EnsenarTubos:
			DragAndDrop::enableDrag = false;
			scene_->activateOneTube(0);
			activateDialogue(false);
			break;
#pragma endregion

		#pragma region Segundo Paquete
		case TutorialEvent::EntraSegundoPaquete:
			DragAndDrop::enableDrag = false;
			scene_->createPackage(ecs::TutorialScene::Segundo);
			delayedCallback(1, [this]() {
				activateDialogue(false);
				});
			break;
		case TutorialEvent::SegundoBuscarPaginaDistritos:
			canPassPagesManual = false;
			activateDialogue(false);
			break;
		case TutorialEvent::SellarSegundoPaquete:
			DragAndDrop::enableDrag = false;
			canPassPagesManual = false;
			activateDialogue(false);
			break;
		case TutorialEvent::EnviarSegundoPaquete:
			DragAndDrop::enableDrag = false;
			activateDialogue(false);
			break;
#pragma endregion

#pragma region Carta

		case TutorialEvent::EntraCarta:

			DragAndDrop::enableDrag = false;

			scene_->createPackage(ecs::TutorialScene::Carta);

			delayedCallback(0.5, [this]() {
				activateDialogue(false);
			});

			break;

		case TutorialEvent::EnviarCarta:

			DragAndDrop::enableDrag = false;

			delayedCallback(0.5, [this]() {
				activateDialogue(false);
			});

			break;
#pragma endregion

#pragma region SignificadoSellos

		case TutorialEvent::BuscarPaginaSellos:

			DragAndDrop::enableDrag = false;
			canPassPagesManual = true;

			delayedCallback(0.5, [this]() {
				activateDialogue(false);
			});

			break;

		case TutorialEvent::ExplicacionSellos:

			delayedCallback(0.5, [this]() {
				activateDialogue(false);
				});

			break;

#pragma endregion

		#pragma region Tercer Paquete
		case TutorialEvent::EntraTercerPaquete:
			DragAndDrop::enableDrag = false;
			scene_->getManual()->getComponent<DragAndDrop>()->enable();
			canPassPagesManual = false;
			scene_->deactivateTubos();
			scene_->createPackage(ecs::TutorialScene::Tercero);
			delayedCallback(0.5, [this]() {
				activateDialogue(false);
				arrow_->setActive(true);
				arrow_->getComponent<Transform>()->setRotation(130);
				arrow_->getComponent<Transform>()->setPos(1355, 620);
				});
			break;
		case TutorialEvent::EnPaginaInfoSellos:
			DragAndDrop::enableDrag = false;
			arrow_->setActive(false);
			canPassPagesManual = false;
			activateDialogue(false);
			break;
#pragma endregion

		#pragma region Paquete Fallar Aposta
		case TutorialEvent::EntraCuartoPaquete:
			DragAndDrop::enableDrag = false;
			canPassPagesManual = false;
			activateDialogue(false);
			delayedCallback(1.5, [this] {
				scene_->createPackage(ecs::TutorialScene::FallarAposta);
				});
			break;
		case TutorialEvent::ExplicacionFalloAposta:
			activateDialogue(true);
			break;
		#pragma endregion

		#pragma region Paquete pesado
		case TutorialEvent::EntraPaquetePeso:

			DragAndDrop::enableDrag = false;
			canPassPagesManual = false;
			scene_->createPackage(ecs::TutorialScene::BalanzaTut);
			delayedCallback(0.2, [this] {
				activateDialogue(false);
				});
			break;

		case TutorialEvent::PesarPaquetePeso:

			canPassPagesManual = false;
			DragAndDrop::enableDrag = false;

			delayedCallback(0.2, [this] {
				activateDialogue(false);
				scene_->createBalanza();

			});

			break;

		case TutorialEvent::EnviarPaquetePeso:
			DragAndDrop::enableDrag = false;
			activateDialogue(false);
			break;
		#pragma endregion

		#pragma region Paquete fragil
		case TutorialEvent::EntraPaqueteFragil:
			DragAndDrop::enableDrag = false;
			waitingWrapComp = scene_->createPackage(ecs::TutorialScene::Fragil)->getComponent<Wrap>();
			delayedCallback(0.2, [this] {
				activateDialogue(false);
				delayedCallback(0.2, [this] {
					scene_->createCinta();
					});
				});
			break;

		case TutorialEvent::PaginaFragil:

			DragAndDrop::enableDrag = false;

			delayedCallback(0.2, [this] {
				activateDialogue(false);

			});

			break;

		case TutorialEvent::SellarFragil:
			DragAndDrop::enableDrag = false;
			activateDialogue(false);
			break;

		case TutorialEvent::EnviarFragil:
			DragAndDrop::enableDrag = false;
			activateDialogue(false);
			break;
		#pragma endregion

		

		case TutorialEvent::Fin:
			activateDialogue(false);
			break;

	}
}

void TutorialSystem::stopEvent(TutorialEvent event) {

	switch (event) 
	{
		#pragma region Manual
		case TutorialEvent::Introduction:
			delayedCallback(1, [this]() {
				activateEvent(TutorialEvent::SacaElManual1);
				});
			break;
		case TutorialEvent::SacaElManual1:
			DragAndDrop::enableDrag = true;
			
			addActionListener(Action::SacarManual, [this]() {
				activateEvent(TutorialEvent::SacaElManual2);
				auto manual = scene_->getManual();
				manual->getComponent<Transform>()->setPos(650, 600);
				manual->getComponent<Depth>()->updateChildPos();
				arrow_->removeComponent<MoverTransform>();
				arrow_->setActive(false);
				});
			break;
		case TutorialEvent::SacaElManual2:
				activateEvent(TutorialEvent::PaqueteEnsenarRemitente);
			break;
#pragma endregion

		#pragma region Primer Paquete
		case TutorialEvent::PaqueteEnsenarRemitente:

			delayedCallback(0.5, [this]() {
				activateEvent(TutorialEvent::PaqueteEnsenarCodigoPostal);
				});
			break;
		case TutorialEvent::PaqueteEnsenarCodigoPostal:
			delayedCallback(0.5, [this]() {
					activateEvent(TutorialEvent::PaqueteBuscarPaginaCodigosPostales);
				});
			break;
		case TutorialEvent::PaqueteBuscarPaginaCodigosPostales:
			arrow_->setActive(true);
			canPassPagesManual = true;
			arrow_->getComponent<Transform>()->setRotation(320);

			arrow_->getComponent<Transform>()->setPos(

				scene_->getManual()->getComponent<Transform>()->getPos().getX() + (scene_->getManual()->getComponent<Transform>()->getWidth() * 0.93),
				scene_->getManual()->getComponent<Transform>()->getPos().getY() + (scene_->getManual()->getComponent<Transform>()->getHeigth() * 0.85));
			
			addActionListener(Action::PaginaCodigosPostales, [this]() {
				DragAndDrop::enableDrag = false;
				canPassPagesManual = false;
				activateEvent(TutorialEvent::BuscarPaginaHestia);
				});
			break;
		case TutorialEvent::BuscarPaginaHestia:
			canPassPagesManual = true;
			addActionListener(Action::PaginaDistritoHestia, [this]() {
				activateEvent(TutorialEvent::EnsenarSellos);
				});
			break;
		case TutorialEvent::EnsenarSellos:
			DragAndDrop::enableDrag = true;
			arrow_->setActive(false);
			addActionListener(Action::PaqueteEstampado, [this]() {
				activateEvent(TutorialEvent::EnsenarTubos);
				});
			break;
		case TutorialEvent::EnsenarTubos:
			DragAndDrop::enableDrag = true;
			scene_->deactivateGarbage();
			addActionListener(Action::PaqueteEnviado, [this]() {
				activateEvent(TutorialEvent::EntraSegundoPaquete);
				});
			break;
#pragma endregion

		#pragma region Segundo Paquete
		case TutorialEvent::EntraSegundoPaquete:

			canPassPagesManual = true;
			scene_->deactivateOneTube(0);
			
			addActionListener(Action::PaginaCodigosPostales, [this]() {
				activateEvent(TutorialEvent::SegundoBuscarPaginaDistritos);
				});
			break;
		case TutorialEvent::SegundoBuscarPaginaDistritos:

			canPassPagesManual = true;

			addActionListener(Action::PaginaDistritoDemeter, [this]() {
				activateEvent(TutorialEvent::SellarSegundoPaquete);
				});
			break;
		case TutorialEvent::SellarSegundoPaquete:

			DragAndDrop::enableDrag = true;
			addActionListener(Action::PaqueteEstampado, [this]() {
				scene_->activateOneTube(2);
				activateEvent(TutorialEvent::EnviarSegundoPaquete);
			});
			
			break;
		case TutorialEvent::EnviarSegundoPaquete:

			DragAndDrop::enableDrag = true;

			addActionListener(Action::PaqueteEnviado, [this]() {
				activateEvent(TutorialEvent::EntraCarta);
				});
			break;
#pragma endregion

#pragma region Carta

		case TutorialEvent::EntraCarta:

			DragAndDrop::enableDrag = true;

			canPassPagesManual = true;

			scene_->deactivateTubos();

			addActionListener(Action::PaqueteEstampado, [this] {
				activateEvent(TutorialEvent::EnviarCarta);
			});

			break;

		case TutorialEvent::EnviarCarta:

			DragAndDrop::enableDrag = true;

			scene_->activateOneTube(2);

			addActionListener(Action::PaqueteEnviado, [this] {
				activateEvent(TutorialEvent::BuscarPaginaSellos);
			});

			break;


#pragma endregion

#pragma region SignificadoSellos

		case TutorialEvent::BuscarPaginaSellos:

			scene_->deactivateOneTube(2);

			addActionListener(Action::PaginaSellos, [this] {
				activateEvent(TutorialEvent::ExplicacionSellos);
			});

			break;

		case TutorialEvent::ExplicacionSellos:

			scene_->deactivateOneTube(2);

			delayedCallback(0.5, [this]() {
				activateEvent(TutorialEvent::EntraCuartoPaquete);
				});

			break;

#pragma endregion

#pragma region Paquete Fallar Aposta
		case TutorialEvent::EntraCuartoPaquete:
			DragAndDrop::enableDrag = true;
			scene_->activateGarbage();
			addActionListener(Action::Basura, [this] {
				activateEvent(TutorialEvent::ExplicacionFalloAposta);
				});
			break;
		case TutorialEvent::ExplicacionFalloAposta:
			delayedCallback(1, [this] {
				activateEvent(TutorialEvent::Fin);
				});
			break;
#pragma endregion

		#pragma region Tercer Paquete
		case TutorialEvent::EntraTercerPaquete:
			DragAndDrop::enableDrag = true;
			canPassPagesManual = true;
			addActionListener(Action::PaginaSellos, [this] {
				activateEvent(TutorialEvent::EnPaginaInfoSellos);
				});
			break;
		case TutorialEvent::EnPaginaInfoSellos:
			DragAndDrop::enableDrag = true;
			scene_->activateGarbage();
			addActionListener(Action::Basura, [this] {
				activateEvent(TutorialEvent::Fin);
				});
			break;
#pragma endregion



#pragma region Paquete Peso
		case TutorialEvent::EntraPaquetePeso:

			DragAndDrop::enableDrag = true;
			canPassPagesManual = true;
			waitingPesado = true;
			scene_->deactivateTubos();
			scene_->deactivateGarbage();

			addActionListener(Action::PaginaPesado, [this]() {
				delayedCallback(1, [this] {
					activateEvent(TutorialSystem::PesarPaquetePeso);
			arrow_->setActive(false);
					});
				});

			break;

		case TutorialEvent::PesarPaquetePeso:

			DragAndDrop::enableDrag = true;
			arrow_->setActive(true);

			// animacion de la flecha
			arrow_->getComponent<Transform>()->setPos(1350, 625);
			arrow_->getComponent<Transform>()->setRotation(130);
			arrow_->addComponent<MoverTransform>(Vector2D(1150, 425), 1, Easing::EaseOutBack);
			arrow_->getComponent<MoverTransform>()->enable();

			addActionListener(Action::Pesado, [this]() {
				delayedCallback(1, [this] {
					activateEvent(TutorialSystem::EnviarPaquetePeso);
			arrow_->setActive(false);
					});
				});

			break;

		case TutorialEvent::EnviarPaquetePeso:

			DragAndDrop::enableDrag = true;
			canPassPagesManual = true;
			scene_->activateOneTube(3);
			addActionListener(Action::PaqueteEnviado, [this] {
				delayedCallback(1, [this] {
					activateEvent(TutorialSystem::Fin);
					});
				});
			break;
#pragma endregion

#pragma region Paquete Fragil
		case TutorialEvent::EntraPaqueteFragil:

			DragAndDrop::enableDrag = true;
			scene_->deactivateTubos();
			scene_->deactivateGarbage();
			canPassPagesManual = true;

			addActionListener(Action::PaginaFragilAccion, [this] {
				delayedCallback(1, [this] {
					activateEvent(TutorialSystem::PaginaFragil);
					});
			});

			break;

		case TutorialEvent::PaginaFragil:
	
			DragAndDrop::enableDrag = true;

			addActionListener(Action::PaqueteEstampado, [this] {
				delayedCallback(1, [this] {
					activateEvent(TutorialSystem::SellarFragil);
					});
				});

			break;

		case TutorialEvent::SellarFragil:
			DragAndDrop::enableDrag = true;
			waitingEmbalaje = true;
			addActionListener(Action::Embalado, [this]() {
				delayedCallback(1, [this] {
					activateEvent(TutorialSystem::EnviarFragil);
					});
				});
			break;

		case TutorialEvent::EnviarFragil:
			DragAndDrop::enableDrag = true;
			scene_->activateOneTube(0);
			addActionListener(Action::PaqueteEnviado, [this]() {
				delayedCallback(1, [this] {
					activateEvent(TutorialSystem::Fin);
					});
				});
			break;
#pragma endregion

		case TutorialEvent::Fin:
		
			gm().requestChangeScene(ecs::sc::TUTORIAL_SCENE, ecs::sc::MAIN_SCENE);
			// MANDAR A OTRA ESCENA O LO QUE QUERAMOS HACER

			break;
	}
}

void TutorialSystem::init()
{

	if (gD().getDay() == 1) {

		tutorialIteration = Introduction;

	}
	else if (gD().getDay() == 3) {

		tutorialIteration = EntraTercerPaquete;

	}
	else if (gD().getDay() == 5) {

		tutorialIteration = EntraPaquetePeso;

	}
	else if (gD().getDay() == 8) {

		tutorialIteration = EntraPaqueteFragil;

	}
	tutorialIteration = 0;
	DragAndDrop::enableDrag = true;
	waitingCallback = false;
	waitingEmbalaje = false;
	waitingPesado = false;

	dialogMngr_.init(scene_);
	createArrow();

}

void TutorialSystem::createArrow() {
	arrow_ = scene_->addEntity(ecs::layer::UI);
	arrow_->addComponent<Transform>(100, 100, 50, 100, 90);
	arrow_->addComponent<RenderImage>(&sdlutils().images().at("manecillaL"));

	arrow_->setActive(false);
}

void TutorialSystem::activateDialogue(bool dialogBoxInBottom) {
	dialogMngr_.setDialogueEntitiesActive(true);
	dialogMngr_.setDialogues(DialogManager::Tutorial, std::to_string(tutorialIteration));
	dialogMngr_.setEndDialogueCallback([this]{
		stopEvent(currentEvent);
	});
}

void TutorialSystem::delayedCallback(float time, SimpleCallback call) {
	call_ = call;

	waitingCallback = true;
	timeToCall_ = sdlutils().virtualTimer().currTime() + (time * 1000);
}

void TutorialSystem::notifyAction(Action a)
{
	std::vector<std::list<std::pair<Action, SimpleCallback>>::iterator> deleteUsedActionListeners;
#ifdef _DEBUG
	std::cout << a << std::endl;
#endif // _DEBUG

	//recorremos el vector de actions y activamos las actions que coincidan con el id
	for (auto it = actionListeners.begin(); it != actionListeners.end(); ++it)
	{
		//no se usa un find ya que se quiere obtener todas las apariciones
		if ((*it).first == a)
		{
			(*it).second();
			deleteUsedActionListeners.push_back(it);
		}
	}

	for (auto it : deleteUsedActionListeners)
		actionListeners.erase(it);
}

void TutorialSystem::addActionListener(Action a, SimpleCallback call)
{
	actionListeners.push_back(std::make_pair(a, call));
}
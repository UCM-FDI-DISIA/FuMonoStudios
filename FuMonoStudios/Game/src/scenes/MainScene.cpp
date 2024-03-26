#include "MainScene.h"
#include "../architecture/Entity.h"
#include <iostream>
#include <fstream>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/Render.h"
#include "../components/Clickeable.h"
#include "../components/DragAndDrop.h"
#include "../components/Trigger.h"
#include "../components/Wrap.h"
#include "../architecture/Game.h"
#include <string>
#include <list>
#include "../sdlutils/Texture.h"
#include "../components/PackageChecker.h"
#include "../components/Herramientas.h"
#include "../components/MultipleTextures.h"
#include "../components/Gravity.h"
#include "../components/MoverTransform.h"
#include "../architecture/Time.h"
#include "../architecture/GameConstants.h"
#include "../components/SelfDestruct.h"
#include "../architecture/GeneralData.h"
#include "../sistemas/ComonObjectsFactory.h"
#include "../components/Depth.h"
#include "../components/ErrorNote.h"
#include <QATools/DataCollector.h>



ecs::MainScene::MainScene():Scene(),fails_(0),correct_(0), timerPaused_(false), timerTexture_(nullptr),timerEnt_(nullptr)
{
	timeFont_ = new Font("recursos/fonts/ARIAL.ttf", 30);
	timer_ = MINIGAME_TIME;
#ifdef DEV_TOOLS
	stampsUnloked_= true;
	timeToAdd_ = 5;
#endif // DEV_TOOLS
	mPaqBuild_ = new PaqueteBuilder();
}

ecs::MainScene::~MainScene()
{
	delete timeFont_;
	delete mPaqBuild_;
}


void ecs::MainScene::update()
{
	Scene::update();
	if (!timerPaused_)
	{
		if (timer_ > 0) {
			timer_ -= Time::getDeltaTime();

			updateTimer();
		}
		else
			gm().requestChangeScene(ecs::sc::MAIN_SCENE, ecs::sc::END_WORK_SCENE);
	}
}

void ecs::MainScene::render()
{
	Scene::render();
#ifdef DEV_TOOLS
	ImGui::NewFrame();
	makeDataWindow();
	makeControlsWindow();
	ImGui::Render();

	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
#endif // DEV_TOOLS

}

void ecs::MainScene::init()
{
	std::cout << "Hola Main" << std::endl;
	sdlutils().clearRenderer(build_sdlcolor(0xFFFFFFFF));
	//crear objetos
	timer_ = MINIGAME_TIME;
	// Fondo
	Entity* Fondo = addEntity(ecs::layer::BACKGROUND);
	Fondo->addComponent<Transform>(0, 0, sdlutils().width(), sdlutils().height());
	Fondo->addComponent<RenderImage>(&sdlutils().images().at("fondoOficina"));

	createManual();

	createClock();

	initTexts();

	createPaquete(generalData().getPaqueteLevel());

	for (int i = 0; i < 7; i++) {
		createTubo((pq::Distrito)i);
	}

	createSelladores();
  
  	//cinta envolver
	factory_->setLayer(ecs::layer::TAPE);
	Entity* cinta = factory_->createImage(Vector2D(560, 500), Vector2D(100, 150), &sdlutils().images().at("cinta"));
	cinta->addComponent<Gravity>();
	cinta->addComponent<DragAndDrop>();
	factory_->setLayer(ecs::layer::DEFAULT);

	// papelera
	Entity* papelera = addEntity(ecs::layer::FOREGROUND);
	papelera->addComponent<Transform>(50, 650, 100, 150);
	papelera->addComponent<RenderImage>(&sdlutils().images().at("papelera"));
	Trigger* papTrig = papelera->addComponent<Trigger>();
	papTrig->addCallback([this](ecs::Entity* entRec) {
		Paquete* paqComp = entRec->getComponent<Paquete>();
		if (paqComp != nullptr)
		{
			if (paqComp->correcto())
			{
				generalData().wrongPackage();
				fails_++;
				Entity* NotaErronea = addEntity(ecs::layer::BACKGROUND);
				NotaErronea->addComponent<ErrorNote>(entRec->getComponent<Paquete>(), true, false);
			}
				
			else
			{ 
				generalData().correctPackage();
				correct_++;
			}
			
			entRec->setAlive(false);
			createPaquete(generalData().getPaqueteLevel());
		}
		});
}

void ecs::MainScene::close() {
	ecs::Scene::close();
	generalData().updateMoney(correct_,fails_);
}

void ecs::MainScene::createClock() {
	Entity* clock = addEntity(layer::BACKGROUND);
	clock->addComponent<Transform>(1340, 510, 210, 140, 0);
	clock->addComponent<RenderImage>(&sdlutils().images().at("reloj"));
	clockCenter = clock->getComponent<Transform>()->getCenter();


	Entity* manecillaL = addEntity(layer::BACKGROUND);
	trManecillaL = manecillaL->addComponent<Transform>(1430, 555, 25, 40);
	manecillaL->addComponent<RenderImage>(&sdlutils().images().at("manecillaL"));

	Entity* manecillaS = addEntity(layer::BACKGROUND);
	trManecillaS = manecillaS->addComponent<Transform>(1435, 580, 25, 15, 0);
	manecillaS->addComponent<RenderImage>(&sdlutils().images().at("manecillaS"));
}

void ecs::MainScene::createSelladores() {
	createStamp(SelloCalleA);
	createStamp(SelloCalleB);
	createStamp(SelloCalleC);
}

void ecs::MainScene::createStamp(TipoHerramienta type)
{
	constexpr float STAMPSIZE = 102.4f;

	factory_->setLayer(layer::OFFICEELEMENTS);

	auto stamp = factory_->createImage(Vector2D(100,300+(int)type * 110),Vector2D(STAMPSIZE,STAMPSIZE), 
		& sdlutils().images().at("sellador" + std::to_string(type)));

	stamp->addComponent<MoverTransform>(
		stamp->getComponent<Transform>()->getPos(), 
		0.5, 
		Easing::EaseOutCubic)->disable();

	stamp->addComponent<DragAndDrop>(true, [stamp]() {
		stamp->getComponent<MoverTransform>()->enable();
		});

	Herramientas* herrSelladorA = stamp->addComponent<Herramientas>();
	herrSelladorA->setFunctionality(type);
}

void ecs::MainScene::createTubo(pq::Distrito dist) {
	float scaleTubos = 0.3f;
	
	Entity* tuboEnt = addEntity(ecs::layer::BACKGROUND);
	Texture* texTubo = &sdlutils().images().at("tubo" + std::to_string(dist + 1));

	Transform* tuboTr = tuboEnt->addComponent<Transform>(75 + (220 * dist), -40, texTubo->width(), texTubo->height());
	tuboTr->setScale(scaleTubos);
	tuboEnt->addComponent<RenderImage>(texTubo);

	Trigger* tuboTri = tuboEnt->addComponent<Trigger>();
	PackageChecker* tuboCheck = tuboEnt->addComponent<PackageChecker>(dist);
	tuboTri->addCallback([this, dist,tuboCheck](ecs::Entity* entRec) {
		//comprobamos si es un paquete
		Transform* entTr = entRec->getComponent<Transform>();
		if (entRec->getComponent<Paquete>() != nullptr) {
			entRec->removeComponent<Gravity>();
			entRec->addComponent<MoverTransform>( // animación básica del paquete llendose
				entTr->getPos() + Vector2D(0, -600), 1.5, Easing::EaseOutCubic);
			entRec->addComponent<SelfDestruct>(1, [this]() {
				generalData().correctPackage();
				createPaquete(generalData().getPaqueteLevel());
				});
			if (tuboCheck->checkPackage(entRec->getComponent<Paquete>())) {
				correct_++;
			}
			else {
				fails_++;
				Entity* NotaErronea = addEntity(ecs::layer::BACKGROUND);
				if (dist == entRec->getComponent<Paquete>()->getDistrito()) {
					NotaErronea->addComponent<ErrorNote>(entRec->getComponent<Paquete>(), false, false);
				}
				else
				{
					NotaErronea->addComponent<ErrorNote>(entRec->getComponent<Paquete>(), false, true);
				}
			}
			/*
			Recogida de datos del paquete enviado (no esta implementado el revisar si era correcto o no
			*/
#ifdef QA_TOOLS
			dataCollector().recordPacage(entRec->getComponent<Paquete>());
#endif // QA_TOOLS
			std::cout << "crazy! " << dist << std::endl;
		}

		});
}

void ecs::MainScene::createManual()
{
	constexpr int MANUALNUMPAGES = 5;
	constexpr float MANUAL_WIDTH = 670;
	constexpr float MANUAL_HEITH = 459;

	Texture* buttonTexture = &sdlutils().images().at("flechaTest");
	//creado array de texturas par el libro
	std::vector<Texture*> bookTextures;
	bookTextures.reserve(MANUALNUMPAGES);
	for (int i = 1; i <= 5; i++) {
		bookTextures.emplace_back(&sdlutils().images().at("book"+std::to_string(i)));
	}
	factory_->setLayer(ecs::layer::MANUAL);

	auto baseManual = factory_->createMultiTextureImage(Vector2D(500, 500), Vector2D(MANUAL_WIDTH, MANUAL_HEITH),bookTextures);
	Transform* manualTransform = baseManual->getComponent<Transform>();
	RenderImage* manualRender = baseManual->getComponent<RenderImage>();
	manualRender->setVector(bookTextures);
	baseManual->addComponent<Gravity>();
	baseManual->addComponent<DragAndDrop>(true);
	baseManual->addComponent<Depth>();


	Vector2D buttonSize(100, 40);
	factory_->setLayer(ecs::layer::FOREGROUND);
	auto next = [manualRender]() {manualRender->nextTexture();};
	auto right = factory_->createImageButton(Vector2D(400, 300), buttonSize, buttonTexture, next);
	right->getComponent<Transform>()->setParent(manualTransform);

	auto previous = [manualRender]() {manualRender->previousTexture();};
	auto left = factory_->createImageButton(Vector2D(100, 300), buttonSize, buttonTexture, previous);
	left->getComponent<Transform>()->setParent(manualTransform);

	factory_->setLayer(ecs::layer::DEFAULT);

}
#ifdef DEV_TOOLS


void ecs::MainScene::makeDataWindow()
{
	ImGui::Begin("Paquetes Scene Data");
	//Reloj del timepo de la partida
	std::string time = "Current Game Time: " + std::to_string(timer_);
	ImGui::Text(time.c_str());
	//Contador de aciertos
	std::string data = "Aciertos: " + std::to_string(correct_);
	ImGui::Text(data.c_str());
	//contador de Fallos
	data = "Fallos: " + std::to_string(fails_);
	ImGui::Text(data.c_str());
	//Nivel de los paquetes
	data = "Pacage Level: " + std::to_string(generalData().getPaqueteLevel());
	ImGui::Text(data.c_str());
	//Dia acutual del juego
	data = "Current day: " + std::to_string(GeneralData::instance()->getCurrentDay());
	ImGui::Text(data.c_str());
	ImGui::End();
}

void ecs::MainScene::makeControlsWindow()
{
	ImGui::Begin("Controls");
	if (ImGui::CollapsingHeader("Paquetes"))
	{
		ImGui::Checkbox("Next Pacage Correct", &nextPacageCorrect_);
		if (ImGui::Button("Create pacage")) {
			createPaquete(generalData().getPaqueteLevel());
		}
	}
	//Todavia no es funcinal ya que no hay forma actual de limitar las mecánicas
	if (ImGui::CollapsingHeader("Mecánicas"))
	{
		int lvl = generalData().getPaqueteLevel();
		ImGui::InputInt("Nivel del Paquete", &lvl);
		generalData().setPaqueteLevel(lvl);
		//ImGui::Checkbox("Sellos",&stampsUnloked_);
		//ImGui::Checkbox("Peso",&weightUnloked_);
		//ImGui::Checkbox("Cinta", &cintaUnloked_);
	}
	if (ImGui::CollapsingHeader("Tiempo")) {
		if (ImGui::Button("Reset Timer")) {
			timer_ = MINIGAME_TIME;
		}

		ImGui::InputInt("Aditional Seconds", &timeToAdd_);
		if (ImGui::Button("Add Time")) {
			timer_ += timeToAdd_;
		}
	}
	ImGui::End();
}
#endif // DEV_TOOLS

void ecs::MainScene::initTexts() {
	// inicializamos el timer
#ifndef DEV_TOOLS
	timerEnt_ = addEntity(ecs::layer::UI);
	timerEnt_->addComponent<Transform>(1250, 50, 200, 200);
	timerEnt_->addComponent<RenderImage>();
	updateTimer();
#endif // DEV_TOOLS
}

void ecs::MainScene::updateTimer() {
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

	//std::cout << "y: " << y << " x:" << x << std::endl;
	//std::cout << "horas " << hours << " minutes: " << minutes << std::endl;
  
#ifndef DEV_TOOLS
	if (timerTexture_ != nullptr)
	{
		delete timerTexture_;
		timerTexture_ = nullptr;
	}

	timerTexture_ = new Texture(sdlutils().renderer(), std::to_string((int)(timer_)), *timeFont_, build_sdlcolor(0x000000ff), 200);
	timerEnt_->getComponent<RenderImage>()->setTexture(timerTexture_);
#endif // !DEV_TOOLS
}


void ecs::MainScene::createPaquete (int lv) {
	/*podriamos hacer que lo que le pases al paquete builder sean las estadisticas o un json 
	con las configuraciones de los niveles de dificultad y tener un constructora a parte que nos permita crear paquetes con configuraciones
	personalizadas*/
	mPaqBuild_->paqueteRND(lv, this);
}
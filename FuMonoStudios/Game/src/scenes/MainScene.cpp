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
	timer_ = MINIGAME_TIME;
#ifdef DEV_TOOLS
	stampsUnloked_= true;
	timeToAdd_ = 5;
#endif // DEV_TOOLS
	mPaqBuild_ = new PaqueteBuilder(this);
}

ecs::MainScene::~MainScene()
{
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
	timer_ = MINIGAME_TIME;
	// Fondo
	factory_->setLayer(layer::BACKGROUND);
	factory_->createImage(Vector2D(), Vector2D(sdlutils().width(), sdlutils().height()),
		&sdlutils().images().at("fondoOficina"));

	for (int i = 0; i < 7; i++) {
		createTubo((pq::Distrito)i);
	}

	createManual();

	createClock();

	initTexts();

	createPaquete(generalData().getPaqueteLevel());

	createGarbage();


	//creacion de las herramientas

	createSelladores();
  
  	//cinta envolver
	factory_->setLayer(ecs::layer::TAPE);
	Entity* cinta = factory_->createImage(Vector2D(560, 500), Vector2D(100, 150), &sdlutils().images().at("cinta"));
	cinta->addComponent<Gravity>();
	cinta->addComponent<DragAndDrop>();
	cinta->addComponent<Depth>();
	factory_->setLayer(ecs::layer::DEFAULT);

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
	if (type > 2) return;
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
	constexpr float TUBE_WIDTH = 138;
	constexpr float TUBE_HEITH = 282;
	constexpr float TUBES_X_OFFSET = 200;
	constexpr float DISTANCE_BETWEEN_TUBES = 220;
	factory_->setLayer(ecs::layer::BACKGROUND);
	
	Entity* tuboEnt = factory_->createImage(
		Vector2D(TUBES_X_OFFSET + (DISTANCE_BETWEEN_TUBES * dist), - 40),
		Vector2D(TUBE_WIDTH,TUBE_HEITH), 
		&sdlutils().images().at("tubo" + std::to_string(dist + 1)));

	Trigger* tuboTri = tuboEnt->addComponent<Trigger>();
	PackageChecker* tuboCheck = tuboEnt->addComponent<PackageChecker>(dist,this);
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
void ecs::MainScene::createGarbage()
{
	/*TDOO Meter en un metdo */
	// papelera
	Entity* papelera = addEntity(ecs::layer::FOREGROUND);
	papelera->addComponent<Transform>(50, 650, 100, 150);
	papelera->addComponent<RenderImage>(&sdlutils().images().at("papelera"));
	Trigger* papTrig = papelera->addComponent<Trigger>();
	papelera->addComponent<PackageChecker>(Erroneo, this);
}
#ifdef DEV_TOOLS


void ecs::MainScene::makeDataWindow()
{
	ImGui::Begin("Paquetes Scene Data");
	//Reloj del timepo de la partida
	std::string time = "Current Game Time: " + std::to_string(timer_);
	ImGui::Text(time.c_str());
	//Contador de aciertos
	std::string data = "Aciertos: " + std::to_string(generalData().getCorrects());
	ImGui::Text(data.c_str());
	//contador de Fallos
	data = "Fallos: " + std::to_string(generalData().getFails());
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
	static bool customPackage;
	ImGui::Begin("Controls");
	if (ImGui::CollapsingHeader("Paquetes"))
	{
		//panel para crear un paquete custom
		static int dist,calle,tipo,nivPeso,peso = 0;
		static bool correcto,fragil, carta = false;
		ImGui::Checkbox("Custom Package", &customPackage);
		if (customPackage) {
			//Los valores pueden ser de 0 a 7
			ImGui::InputInt("Distrito", &dist);
			//Los valores pueden ser de 0 a 3
			ImGui::InputInt("Calle",&calle);
			//Los valores son de 0 a 4
			ImGui::InputInt("Tipo",&tipo);
			ImGui::Checkbox("SelloCorrecto", &correcto);
			ImGui::InputInt("NivPeso",&nivPeso);
			ImGui::InputInt("Peso", &peso);
			ImGui::Checkbox("Fragil", &fragil);
			ImGui::Checkbox("Carta", &carta);
		}
		//ImGui::Checkbox("Next Pacage Correct", &nextPacageCorrect_);
		if (ImGui::Button("Create pacage")) {
			if (customPackage) {
				mPaqBuild_->customPackage((pq::Distrito)dist,(pq::Calle)calle,"Sujeto de Pruebas", (pq::TipoPaquete)tipo, 
					correcto, (pq::NivelPeso)nivPeso, peso, fragil, carta);
			}
			else {
				createPaquete(generalData().getPaqueteLevel());
			}
		}
	}
	//Todavia no es funcinal ya que no hay forma actual de limitar las mecánicas
	if (ImGui::CollapsingHeader("Mecánicas"))
	{
		int lvl = generalData().getPaqueteLevel();
		ImGui::InputInt("Nivel del Paquete", &lvl);
		generalData().setPaqueteLevel(lvl);
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
}


void ecs::MainScene::createPaquete (int lv) {
	auto pac = mPaqBuild_->buildPackage(lv, this);
	pac->addComponent<MoverTransform>(pac->getComponent<Transform>()->getPos()-Vector2D(200,0),
		1,Easing::EaseOutBack)->enable();
}
#include "MainScene.h"
#include "../architecture/Entity.h"
#include <iostream>
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
#include "../sistemas/PaqueteBuilder.h"
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

ecs::MainScene::MainScene():Scene(),fails_(0),correct_(0), timerPaused_(false), timerTexture_(nullptr),timerEnt_(nullptr)
{
	timeFont_ = new Font("recursos/fonts/ARIAL.ttf", 30);
	timer_ = MINIGAME_TIME;
#ifdef DEV_TOOLS
	stampsUnloked_= true;
	timeToAdd_ = 5;
#endif // DEV_TOOLS

}

ecs::MainScene::~MainScene()
{
}


void ecs::MainScene::update()
{
	Scene::update();
	if (!timerPaused_)
	{
		gm().requestChangeScene(ecs::sc::MAIN_SCENE, ecs::sc::END_WORK_SCENE);

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

	ImGui::Begin("Paquetes Scene Data");
	std::string time = "Current Game Time: " + std::to_string(timer_);
	ImGui::Text(time.c_str());
	std::string data = "Aciertos: " + std::to_string(correct_);
	ImGui::Text(data.c_str());
	data = "Fallos: " + std::to_string(fails_);
	ImGui::Text(data.c_str());
	data = "Pacage Level: " + std::to_string(generalData().getPaqueteLevel());
	ImGui::Text(data.c_str());
	ImGui::End();


	ImGui::Begin("Controls");
	if (ImGui::CollapsingHeader("Paquetes"))
	{
		ImGui::Checkbox("Next Pacage Correct",&nextPacageCorrect_);
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
	ImGui::Render();

	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
#endif // DEV_TOOLS

}

void ecs::MainScene::init()
{
	std::cout << "Hola Main" << std::endl;
	sdlutils().clearRenderer(build_sdlcolor(0xFFFFFFFF));
	//crear objetos
	ComonObjectsFactory factory(this);
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
		createTubo((Paquete::Distrito)i);
	}

	createHerramientas();
  
  	//cinta envolver
	factory.setLayer(ecs::layer::TAPE);
	Entity* cinta = factory.createImage(Vector2D(560, 500), Vector2D(100, 150), &sdlutils().images().at("cinta"));
	cinta->addComponent<Gravity>();
	cinta->addComponent<DragAndDrop>();
	factory.setLayer(ecs::layer::DEFAULT);

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

void ecs::MainScene::createHerramientas() {
	float scaleSelladores = 0.2f;

	// Sellador rojo (1)
	Entity* selloA = addEntity(layer::OFFICEELEMENTS);
	Texture* selloATex = &sdlutils().images().at("selladorA");
	Transform* selloATR = selloA->addComponent<Transform>(100, 300, selloATex->width(), selloATex->height());
	selloATR->setScale(scaleSelladores);
	selloA->addComponent<DragAndDrop>(true, [selloA]() {
		selloA->addComponent<MoverTransform>(Vector2D(100,300), 0.5, Easing::EaseOutCubic);
		});
	selloA->addComponent<RenderImage>(selloATex);
	Herramientas* herrSelladorA = selloA->addComponent<Herramientas>();
	herrSelladorA->setFunctionality(SelloCalleA);
	
	// Sellador azul (2)
	Entity* selloB = addEntity(layer::OFFICEELEMENTS);
	Texture* selloBTex = &sdlutils().images().at("selladorB");
	Transform* selloBTR = selloB->addComponent<Transform>(100, 410, selloBTex->width(), selloBTex->height());
	selloBTR->setScale(scaleSelladores);
	selloB->addComponent<DragAndDrop>(true, [selloB]() {
		selloB->addComponent<MoverTransform>(Vector2D(100, 410), 0.5, Easing::EaseOutCubic);
		});
	selloB->addComponent<RenderImage>(selloBTex);
	Herramientas* herrSelladorB = selloB->addComponent<Herramientas>();
	herrSelladorB->setFunctionality(SelloCalleB);

	// Sellador verde (3)
	Entity* selloC = addEntity(layer::OFFICEELEMENTS);
	Texture* selloCTex = &sdlutils().images().at("selladorC");
	Transform* selloCTR = selloC->addComponent<Transform>(100, 520, selloCTex->width()
, selloCTex->height());
	selloCTR->setScale(scaleSelladores);
	selloC->addComponent<DragAndDrop>(true, [selloC]() {
		selloC->addComponent<MoverTransform>(Vector2D(100, 520), 0.5, Easing::EaseOutCubic);
		});
	selloC->addComponent<RenderImage>(selloCTex);
	Herramientas* herrSelladorC = selloC->addComponent<Herramientas>();
	herrSelladorC->setFunctionality(SelloCalleC);

	// Balanza
	createBalanza();


}

void ecs::MainScene::createTubo(Paquete::Distrito dist) {
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

			std::cout << "crazy! " << dist << std::endl;
		}

		});
}

void ecs::MainScene::createManual()
{
	ComonObjectsFactory fact(this);
	Entity* manual = addEntity(ecs::layer::MANUAL);
	//se puede hacer un for
	Texture* manualTexture = &sdlutils().images().at("book1");
	Texture* manualTexture2 = &sdlutils().images().at("book2");
	Texture* manualTexture3 = &sdlutils().images().at("book3");
	Texture* manualTexture4 = &sdlutils().images().at("book4");
	Texture* manualTexture5 = &sdlutils().images().at("book5");
	Texture* buttonTexture = &sdlutils().images().at("flechaTest");

	std::vector<Texture*> bookTextures = {
		manualTexture,
		manualTexture2,
		manualTexture3,
		manualTexture4,
		manualTexture5
	};
	float scaleManual = 0.075;
	Transform* manualTransform = manual->addComponent<Transform>(500.0f, 500.0f, manualTexture->width(), manualTexture->height());
	manualTransform->setScale(scaleManual);
	RenderImage* manualRender = manual->addComponent<RenderImage>();
	manual->addComponent<Gravity>();
	manual->addComponent<DragAndDrop>(true);
	MultipleTextures* multTextures = manual->addComponent<MultipleTextures>(bookTextures);
	manualRender->setTexture(multTextures->getCurrentTexture());


	Vector2D buttonSize(100, 40);
	fact.setLayer(ecs::layer::FOREGROUND);

	auto next = [multTextures]() {multTextures->nextTexture();};
	auto right = fact.createImageButton(Vector2D(400, 300), buttonSize, buttonTexture, next);
	right->getComponent<Transform>()->setParent(manualTransform);

	auto previous = [multTextures]() {multTextures->previousTexture();};
	auto left = fact.createImageButton(Vector2D(100, 300), buttonSize, buttonTexture, previous);
	left->getComponent<Transform>()->setParent(manualTransform);


	fact.setLayer(ecs::layer::DEFAULT);

	manual->addComponent<Depth>();
}

void ecs::MainScene::initTexts() {
	// inicializamos el timer
#ifndef DEV_TOOLS
	timerEnt_ = addEntity(ecs::layer::UI);
	timerEnt_->addComponent<Transform>(1250, 50, 200, 200);
	timerEnt_->addComponent<RenderImage>();
	updateTimer();
#endif // DEV_TOOLS
}

void ecs::MainScene::createBalanza() {
	Entity* balanzaBase = addEntity(layer::DEFAULT);
	Entity* balanzaA = addEntity(layer::DEFAULT);
	Entity* balanzaB = addEntity(layer::TAPE);
	Texture* balanzaBaseTex = &sdlutils().images().at("weightMachineBase");
	Texture* balanzaATex = &sdlutils().images().at("weightMachineBalanzaA");
	Texture* balanzaBTex = &sdlutils().images().at("weightMachineBalanzaB");
	Transform* balanzaBaseTR = balanzaBase->addComponent<Transform>(250, 520, balanzaBaseTex->width()
		, balanzaBaseTex->height());
	Transform* balanzaATR = balanzaA->addComponent<Transform>(0, 0, balanzaATex->width()
		, balanzaATex->height());
	Transform* balanzaBTR = balanzaB->addComponent<Transform>(0, 0, balanzaBTex->width()
		, balanzaBTex->height());
	balanzaBaseTR->setScale(0.5);
	balanzaATR->setScale(0.5);
	balanzaBTR->setScale(0.5);
	balanzaATR->setParent(balanzaBaseTR);
	balanzaBTR->setParent(balanzaBaseTR);
	balanzaBase->addComponent<DragAndDrop>();
	balanzaBase->addComponent<Gravity>();
	balanzaBase->addComponent<RenderImage>(balanzaBaseTex);
	balanzaA->addComponent<RenderImage>(balanzaATex);
	balanzaB->addComponent<RenderImage>(balanzaBTex);
	Herramientas* herrBalanza = balanzaBase->addComponent<Herramientas>();
	herrBalanza->setFunctionality(WeightMachine);
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
	float paqueteScale = 0.25f;
	Entity* paqEnt = addEntity (ecs::layer::PACKAGE);

	Texture* texturaPaquet = &sdlutils ().images ().at ("boxTest");

	std::vector<Texture*> textures = {
		texturaPaquet,
		&sdlutils().images().at("caja25"),
		&sdlutils().images().at("caja50"),
		&sdlutils().images().at("caja75"),
		&sdlutils().images().at("caja100")
	};

	Transform* trPq = paqEnt->addComponent<Transform> (1600.0f, 600.0f, texturaPaquet->width (), texturaPaquet->height ());
	trPq->setScale(paqueteScale);+
	paqEnt->addComponent<Depth>();
	RenderImage* rd = paqEnt->addComponent<RenderImage> (texturaPaquet);
	paqEnt->addComponent<Gravity>();
	DragAndDrop* drgPq = paqEnt->addComponent<DragAndDrop>(true);
	std::list<int> route {pointRoute::LeftUp, pointRoute::MiddleUp, pointRoute::MiddleMid, pointRoute::MiddleDown, pointRoute::RightDown};

	MultipleTextures* multTexturesPaq = paqEnt->addComponent<MultipleTextures>(textures);

	multTexturesPaq->initComponent();

	//Wrap debe ir despues del Transform, Trigger y Multitextures
	paqEnt->addComponent<Wrap>(20, 0, route);


	PaqueteBuilder* paqBuildInstance = PaqueteBuilder::getInstance();
	paqBuildInstance->paqueteRND(lv, paqEnt);

	// añadimos que pueda ser interactuado por selladores
	paqEnt->getComponent<Trigger>()->addCallback([paqEnt](ecs::Entity* entRec) {
		Herramientas* herrEnt = entRec->getComponent<Herramientas>();
		if (herrEnt != nullptr)
		{
			herrEnt->interact(paqEnt);
		}
		});

	paqEnt->addComponent<MoverTransform>(Vector2D(1200,600), 1, EaseOutBack);
}
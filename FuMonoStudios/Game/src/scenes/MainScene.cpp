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
#include <string>
#include <list>
#include "../sdlutils/Texture.h"
#include "../components/PackageChecker.h"
#include "../components/Gravity.h"
#include "../components/MoverTransform.h"
#include "../architecture/Time.h"
#include "../architecture/GameConstants.h"
#include "../components/SelfDestruct.h"
#include "../architecture/GeneralData.h"
#include "../sistemas/ComonObjectsFactory.h"
#include "../components/Depth.h"
#include <QATools/DataCollector.h>
#include "../components/ErrorNote.h"
#include "../entities/ClockAux.h"

ecs::MainScene::MainScene():Scene(),fails_(0),correct_(0), timerPaused_(false)
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

	//for (int i = 0; i < 7; i++) {
	//	createTubo((pq::Distrito)i);
	//}

	createManual();

	createClock();
	
	createPaquete(generalData().getPaqueteLevel());

	createGarbage();


	//creacion de las herramientas
	// En el caso de que los tubos no estén ordenados, habrá que ordenarlos
	int numTubos = generalData().getTubesAmount(); // coge el numero de tubos que están desbloqueados
	int j = 0;
	for (int i = 0;i < numTubos; i++) {
		createTubo((pq::Distrito)i, true);
		j++;
	}
	//Creación de paquetes bloqueados
	for (int z = j; z < 7; z++) { //grande jose la los numeros magicos te la sabes
		createTubo((pq::Distrito)z, false);
	}

	//createSelladores();

	createInks();
  
  	//cinta envolver
	factory_->setLayer(ecs::layer::TAPE);
	Entity* cinta = factory_->createImage(Vector2D(560, 500), Vector2D(100, 150), &sdlutils().images().at("cinta"));
	cinta->addComponent<Gravity>();
	cinta->addComponent<DragAndDrop>();
	cinta->addComponent<Depth>();
	factory_->setLayer(ecs::layer::DEFAULT);

	//Luis: dejo esto comentado porque con la refactorizacion se va a poder hacer de forma mas elegante

	// A medida que se vaya avanzando en el desarrollo, se tendra que expandir esto de apajo para que en X dia suceda algo o aparezcan nuevas herramientas
	// Me gustaría que todo lo relacionado con los eventos de los dias y los paquetes y herramientas correspondientes estuviera documentado
	// En el miro había un esquema, pero este estaba con poco detalle, lo suyo es en gdd ver estas cosas, pero se va trabajando en ello

	int dia = generalData().getDia();
	if (dia > 0 && dia < 2) {
		Texture* texturaSellador = &sdlutils().images().at("sellador0");
		Entity* sellador = addEntity(ecs::layer::STAMP);
		Transform* transformSellador = sellador->addComponent<Transform>(560, 0, texturaSellador->width(), texturaSellador->height());
		transformSellador->setScale(1);
		RenderImage* renderSellador = sellador->addComponent<RenderImage>(texturaSellador);
		sellador->addComponent<Gravity>();
		sellador->addComponent<DragAndDrop>();
		sellador->addComponent<Herramientas>();
		sellador->getComponent<Herramientas>()->setFunctionality(TipoHerramienta::SelloCalleA);
	}
	else if (dia >= 2 && dia < 4) {
		Texture* texturaCinta = &sdlutils().images().at("cinta");
		Entity* cinta = addEntity();
		Transform* transformCinta = cinta->addComponent<Transform>(560, 0, texturaCinta->width() / 2, texturaCinta->height() / 2);
		RenderImage* renderCinta = cinta->addComponent<RenderImage>(texturaCinta);
		cinta->addComponent<Gravity>();
		cinta->addComponent<DragAndDrop>();
	}
	else if (dia >= 4 && dia < 6) {}
	else if (dia >= 6 && dia < 8) {}
	else if (dia >= 8 && dia < 10) {}

	/*switch (dia) {
	case 1: {
		Texture* texturaSellador1 = &sdlutils().images().at("sellador");
		Entity* sellador1 = addEntity();
		Transform* transformSellador1 = sellador1->addComponent<Transform>(460, 0, texturaSellador1->width() / 2, texturaSellador1->height() / 2);
		RenderImage* renderSellador1 = sellador1->addComponent<RenderImage>(texturaSellador1);
		sellador1->addComponent<Gravity>();
		sellador1->addComponent<DragAndDrop>();
		sellador1->addComponent<Herramientas>();
		sellador1->getComponent<Herramientas>()->setFunctionality(TipoHerramienta::SelloCalleA);
		break;
		}
	case 2: {
		Texture* texturaCinta1 = &sdlutils().images().at("cinta");
		Entity* cinta1 = addEntity();
		Transform* transformCinta1 = cinta1->addComponent<Transform>(460, 0, texturaCinta1->width() / 2, texturaCinta1->height() / 2);
		RenderImage* renderCinta1 = cinta1->addComponent<RenderImage>(texturaCinta1);
		cinta1->addComponent<Gravity>();
		cinta1->addComponent<DragAndDrop>();
		break;
		}
	}*/
}

void ecs::MainScene::close() {
	ecs::Scene::close();
	generalData().updateMoney(correct_,fails_);
}

void ecs::MainScene::createClock() {
	Entity* clock = addEntity(ecs::layer::BACKGROUND);
	clock->addComponent<ClockAux>(MINIGAME_TIME);
}

void ecs::MainScene::createInks() {

	// Tinta rojo (1)
	Entity* inkA = addEntity(layer::INK);
	Texture* inkATex = &sdlutils().images().at("tintaA");
	Transform* selloATR = inkA->addComponent<Transform>(300, 500, inkATex->width(), inkATex->height());

	selloATR->setScale(0.5);

	inkA->addComponent<RenderImage>(inkATex);

	Trigger* inkATri = inkA->addComponent<Trigger>();

	inkATri->addCallback([this](ecs::Entity* entRec) {

		if (entRec->getLayer() == ecs::layer::STAMP) {

			Herramientas* stampHerramienta = entRec->getComponent<Herramientas>();

			RenderImage* stampRender = entRec->getComponent<RenderImage>();

			stampHerramienta->setFunctionality(SelloCalleA);

			stampRender->setTexture(&sdlutils().images().at("sellador0"));

		}

	});

	


	// Tinta azul (2)
	Entity* inkB = addEntity(layer::INK);
	Texture* inkBTex = &sdlutils().images().at("tintaB");
	Transform* selloBTR = inkB->addComponent<Transform>(425, 500, inkBTex->width(), inkBTex->height());

	selloBTR->setScale(0.5);

	inkB->addComponent<RenderImage>(inkBTex);

	Trigger* inkBTri = inkB->addComponent<Trigger>();

	inkBTri->addCallback([this](ecs::Entity* entRec) {

		if (entRec->getLayer() == ecs::layer::STAMP) {

			Herramientas* stampHerramienta = entRec->getComponent<Herramientas>();

			RenderImage* stampRender = entRec->getComponent<RenderImage>();

			stampHerramienta->setFunctionality(SelloCalleB);

			stampRender->setTexture(&sdlutils().images().at("sellador1"));

		}

	});

	// Tinta verde (3)
	Entity* inkC = addEntity(layer::INK);
	Texture* inkCTex = &sdlutils().images().at("tintaC");
	Transform* selloCTR = inkC->addComponent<Transform>(550, 500, inkCTex->width(), inkCTex->height());

	selloCTR->setScale(0.5);

	inkC->addComponent<RenderImage>(inkCTex);

	Trigger* inkCTri = inkC->addComponent<Trigger>();

	inkCTri->addCallback([this](ecs::Entity* entRec) {

		if (entRec->getLayer() == ecs::layer::STAMP) {

			Herramientas* stampHerramienta = entRec->getComponent<Herramientas>();

			RenderImage* stampRender = entRec->getComponent<RenderImage>();

			stampHerramienta->setFunctionality(SelloCalleC);

			stampRender->setTexture(&sdlutils().images().at("sellador2"));

		}

		});

}


void ecs::MainScene::createErrorMessage(Paquete* paqComp, bool basura, bool tuboIncorrecto) {
	Entity* NotaErronea = addEntity(ecs::layer::BACKGROUND);	
	NotaErronea->addComponent<ErrorNote>(paqComp, basura, tuboIncorrecto);
	Texture* NotaTex = &sdlutils().images().at("notaError");
	Transform* selloATR = NotaErronea->addComponent<Transform>(100, 1400, NotaTex->width()*2, NotaTex->height()*2);
	selloATR->setScale(0.2f);
	NotaErronea->addComponent<DragAndDrop>(true, [NotaErronea]() {
		NotaErronea->addComponent<MoverTransform>(Vector2D(100, 1400), 0.5, Easing::EaseOutCubic, [NotaErronea]() {
			NotaErronea->setAlive(false);
			});
		});
	NotaErronea->addComponent<RenderImage>(NotaTex);
	
	//El texto de la nota
	Entity* texto_ = addEntity(ecs::layer::STAMP);
	Font* textFont = new Font("recursos/fonts/ARIAL.ttf", 40);
	Texture* textureText_ = new Texture(sdlutils().renderer(), NotaErronea->getComponent<ErrorNote>()->text_, *textFont, build_sdlcolor(0x000000ff), 500);
	Transform* distritoTr = texto_->addComponent<Transform>(25, 70, 250, 100);
	RenderImage* distritoRender = texto_->addComponent<RenderImage>();
	distritoRender->setTexture(textureText_);
	distritoTr->setParent(NotaErronea->getComponent<Transform>());

	NotaErronea->addComponent<MoverTransform>(Vector2D(100, 880), 0.5, Easing::EaseOutCubic);

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

void ecs::MainScene::createTubo(pq::Distrito dist,bool unlock) {
	constexpr float TUBE_WIDTH = 138;
	constexpr float TUBE_HEITH = 282;
	constexpr float TUBES_X_OFFSET = 200;
	constexpr float DISTANCE_BETWEEN_TUBES = 220;
	factory_->setLayer(ecs::layer::BACKGROUND);

	Entity* tuboEnt = factory_->createImage(
		Vector2D(TUBES_X_OFFSET + (DISTANCE_BETWEEN_TUBES * dist), -40),
		Vector2D(TUBE_WIDTH, TUBE_HEITH),
		&sdlutils().images().at("tubo" + std::to_string(dist + 1)));
	if (unlock) {

		Trigger* tuboTri = tuboEnt->addComponent<Trigger>();
		PackageChecker* tuboCheck = tuboEnt->addComponent<PackageChecker>(dist, this);
	}
	else {
		factory_->setLayer(layer::UI);
		auto tubeTr = tuboEnt->getComponent<Transform>();

		auto cross = factory_->createImage(Vector2D(0, 120),
			Vector2D(tubeTr->getWidth(), tubeTr->getWidth()),
			&sdlutils().images().at("cruz"));

		cross->getComponent<Transform>()->setParent(tubeTr);

	}
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
				auto custom = mPaqBuild_->customPackage((pq::Distrito)dist,(pq::Calle)calle,"Sujeto de Pruebas", (pq::TipoPaquete)tipo, 
					correcto, (pq::NivelPeso)nivPeso, peso, fragil, carta);
				custom->getComponent<MoverTransform>()->enable();
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



void ecs::MainScene::createPaquete (int lv) {
	auto pac = mPaqBuild_->buildPackage(lv, this);
	pac->getComponent<MoverTransform>()->enable();
}
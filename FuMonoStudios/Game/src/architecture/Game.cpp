#include "Game.h"
#include <list>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <SDL.h>
#include <algorithm>
#include "../sdlutils/InputHandler.h"
#include "../scenes/MainScene.h"
#include "../scenes/MainMenu.h"
#include "../scenes/ExplorationScene.h"
#include "../scenes/EndWorkScene.h"
#include "Time.h"
#include "GeneralData.h"

Game::Game() :exit_(false) {
	SDLUtils::init("Mail To Atlantis", 1600, 900, "recursos/config/mail.resources.json");

	auto& sdl = *SDLUtils::instance();

	sdl.showCursor();
	window_ = sdl.window();
	renderer_ = sdl.renderer();
	gameScenes_ = { new ecs::MainScene(),new ecs::ExplorationScene(),new EndWorkScene(),new ecs::MainMenu() };

	loadScene(ecs::sc::MENU_SCENE);
}

Game::~Game()
{
	for (auto s : gameScenes_) {
		delete s;
	}
}


void Game::run()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplSDL2_InitForSDLRenderer(sdlutils().window(), sdlutils().renderer());
	ImGui_ImplSDLRenderer2_Init(sdlutils().renderer());

	while (!exit_)
	{
		if (sceneChange_)
		{
			changeScene(scene1_, scene2_);
			sceneChange_ = false;
		}
		//SDL_Event e;
		//while (SDL_PollEvent(&e)) {
		//	ImGui_ImplSDL2_ProcessEvent(&e);
		//}
		refresh();
		ih().refresh();
		Uint32 startTime = sdlutils().virtualTimer().currTime();

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE) || ih().closeWindowEvent()) {
			exit_ = true;
		}
		if (ih().isKeyDown(SDL_SCANCODE_F)) {
			sdlutils().toggleFullScreen();
		}
		if (ih().isKeyDown(SDL_SCANCODE_E)) {
			changeScene(ecs::sc::MENU_SCENE, ecs::sc::MAIN_SCENE);
		}
		if (ih().isKeyDown(SDL_SCANCODE_W)) {
			changeScene(ecs::sc::MAIN_SCENE, ecs::sc::MENU_SCENE);
		}


		update();
		sdlutils().clearRenderer();

		render();

		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		/**/

		sdlutils().presentRenderer();

		Time::deltaTime_ = (sdlutils().virtualTimer().currTime() - startTime) / 1000.0;


	}
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

//void Game::writeMessage() {
//
//	
//}

/// <summary>
/// Carga la escena indicada por el Id
/// Se ejecutara la ultima de la cadena de proceso
/// </summary>
/// <param name="scene"></param>

//void Game::loadScene(ecs::sc::sceneId scene)
//{
//	//llamar al init de la escena a cargar????
//	gameScenes[scene]->init();
//	//cargamos la escena
//	loadedScenes.push_back(gameScenes[scene]);
//}

void Game::loadScene(ecs::sc::sceneId scene)
{
	auto it = std::find(loadedScenes_.begin(), loadedScenes_.end(), gameScenes_[scene]);
	if (it == loadedScenes_.end()) {
		//llamar al init de la escena a cargar????
		gameScenes_[scene]->init();
		//cargamos la escena
		loadedScenes_.push_back(gameScenes_[scene]);
	}
}

/// <summary>
/// Descarga al escena pedida
/// </summary>
/// <param name="scene"></param>
void Game::killScene(ecs::sc::sceneId scene)
{
	auto it = std::find(loadedScenes_.begin(), loadedScenes_.end(), gameScenes_[scene]);
	if (it != loadedScenes_.end()) {
		(*it)->close();
		loadedScenes_.erase(it);
		std::cout << "Scene Killed" << std::endl;
	}
}

void Game::requestChangeScene(ecs::sc::sceneId scene1, ecs::sc::sceneId scene2)
{
	sceneChange_ = true;
	scene1_ = scene1;
	scene2_ = scene2;
}

void Game::changeScene(ecs::sc::sceneId scene1, ecs::sc::sceneId scene2) {
	//Más adelante el changeScene deberá de tener más parámetros correspondientes a lo que se va a guardar en
	//El GeneralData para compartir información entre escenas, pero por ahora nos bastamos con esto

	//Estas comprobaciones van a ser una prueba de que se puede modificar la clase GeneralData, no estará así en la versión final
	if (scene1 == ecs::sc::MENU_SCENE) {
		generalData().setFinalID(1);
		generalData().setEventoID(1);
	}
	else if (scene1 == ecs::sc::EXPLORE_SCENE) {
		generalData().setFinalID(2);
		generalData().setEventoID(2);
	}
	else if (scene1 == ecs::sc::MAIN_SCENE) {
		generalData().setFinalID(3);
		generalData().setEventoID(3);
	}
	killScene(scene1);
	loadScene(scene2);
	/*if (loadedScenes.size() < 1) {
		loadScene(scene2);
	}*/
}

/// <summary>
/// Actualiza el juego
/// </summary>
void Game::update()
{
	for (auto& scene : loadedScenes_) {
		scene->update();
	}
}
/// <summary>
/// renderiza en pantalla el juego
/// no llamar a render clear o present se llamaran antes y despues de la llamada a este metodo
/// </summary>
void Game::render()
{
	for (auto& scene : loadedScenes_) {
		scene->render();
	}
}

void Game::refresh()
{
	for (auto& scene : loadedScenes_) {
		scene->refresh();
	}
}

#include "Game.h"
#include <list>
#include <SDL.h>
#include <algorithm>
#include "../sdlutils/InputHandler.h"
#include "../scenes/MainScene.h"
#include "../scenes/MainMenu.h"
#include "../scenes/ExplorationScene.h"
#include "../components/Time.h"
#include "GeneralData.h"
//#include "Game.h"
/*
TODO
Anadir fichero de configuracion el init de SDLUtils cuando haya recursos que cargar
*/

Game::Game() :exit(false) {
	SDLUtils::init("Mail To Atlantis", 1600, 900, "recursos/config/mail.resources.json");

	auto& sdl = *SDLUtils::instance();

	sdl.showCursor();
	window = sdl.window();
	renderer = sdl.renderer();
	gameScenes = { new ecs::MainScene(),new ecs::ExplorationScene(),new ecs::MainMenu() };

	loadScene(ecs::sc::MENU_SCENE);
}

Game::~Game()
{
	for (auto s : gameScenes) {
		delete s;
	}
}


void Game::run()
{
	while (!exit)
	{
		if (sceneChange)
		{
			changeScene(scene1_, scene2_);
			sceneChange = false;
		}

		ih().refresh();
		Uint32 startTime = sdlutils().virtualTimer().currTime();

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE) || ih().closeWindowEvent()) {
			exit = true;
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
		sdlutils().presentRenderer();

		Time::deltaTime = (sdlutils().virtualTimer().currTime() - startTime) / 1000.0;
	}
}

//void Game::writeMessage() {
//
//	
//}

/// <summary>
/// carga la escena indicada por el Id
/// se ejecutara la ultima de la cadena de proceso
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
	auto it = std::find(loadedScenes.begin(), loadedScenes.end(), gameScenes[scene]);
	if (it == loadedScenes.end()) {
		//llamar al init de la escena a cargar????
		gameScenes[scene]->init();
		//cargamos la escena
		loadedScenes.push_back(gameScenes[scene]);
	}
}

/// <summary>
/// descarga al escena pedida
/// </summary>
/// <param name="scene"></param>
void Game::killScene(ecs::sc::sceneId scene)
{
	auto it = std::find(loadedScenes.begin(), loadedScenes.end(), gameScenes[scene]);
	if (it != loadedScenes.end()) {
		loadedScenes.erase(it);
		std::cout << "Scene Killed" << std::endl;
	}
}

void Game::requestChangeScene(ecs::sc::sceneId scene1, ecs::sc::sceneId scene2)
{
	sceneChange = true;
	scene1_ = scene1;
	scene2_ = scene2;
}

void Game::changeScene(ecs::sc::sceneId scene1, ecs::sc::sceneId scene2) {
	//Más adelante el changeScene deberá de tener más parámetros correspondientes a lo que se va a guardar en
	//el GeneralData para compartir información entre escenas, pero por ahora nos bastamos con esto

	//Estas comprobaciones van a ser una prueba de que se puede modificar la clase GeneralData, no estará así en la versión final
	if (scene1 == ecs::sc::MENU_SCENE) {
		generalData().SetFinalID(1);
		generalData().SetEventoID(1);
	}
	else if (scene1 == ecs::sc::EXPLORE_SCENE) {
		generalData().SetFinalID(2);
		generalData().SetEventoID(2);
	}
	else if (scene1 == ecs::sc::MAIN_SCENE) {
		generalData().SetFinalID(3);
		generalData().SetEventoID(3);
	}
	killScene(scene1);
	loadScene(scene2);
	/*if (loadedScenes.size() < 1) {
		loadScene(scene2);
	}*/
}

/// <summary>
/// actualiza el juego
/// </summary>
void Game::update()
{
	for (auto scene : loadedScenes) {
		scene->update();
	}
}
/// <summary>
/// renderiza en pantalla el juego
/// no llamar a render clear o present se llamaran antes y despues de la llamada a este metodo
/// </summary>
void Game::render()
{
	for (auto scene : loadedScenes) {
		scene->render();
	}
}

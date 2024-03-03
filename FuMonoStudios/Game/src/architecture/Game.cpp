#include "Game.h"
#include <list>
#include <SDL.h>
#include <algorithm>
#include "../sdlutils/InputHandler.h"
#include "../scenes/MainScene.h"
#include "../scenes/ExplorationScene.h"
#include "Game.h"
/*
TODO
A�adir fichero de configuracion el init de SDLUtils cuando haya recursos que cargar
*/

Game::Game():exit(false){
	SDLUtils::init("Mail To Atlantis",1600 , 900, "recursos/config/mail.resources.json");

	auto& sdl = *SDLUtils::instance();

	sdl.showCursor();
	window = sdl.window();
	renderer = sdl.renderer();
	gameScenes = {new ecs::MainScene(),new ecs::MainMenu(),new ecs::ExplorationScene() };

	sceneChange = false;

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
		Uint32 startTime = SDL_GetTicks();

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE) || ih().closeWindowEvent()) {
			exit = true;
		}
		if (ih().isKeyDown(SDL_SCANCODE_F)) {
			sdlutils().toggleFullScreen();
		}
		if (ih().isKeyDown(SDL_SCANCODE_E)) {
			requestChangeScene(ecs::sc::MENU_SCENE, ecs::sc::MAIN_SCENE);
		}
		if (ih().isKeyDown(SDL_SCANCODE_W)) {
			requestChangeScene(ecs::sc::MAIN_SCENE, ecs::sc::MENU_SCENE);
		}

		update();
		sdlutils().clearRenderer();
		render();
		sdlutils().presentRenderer();

		Uint32 frameTime = SDL_GetTicks() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}
}

/// <summary>
/// carga la escena indicada por el Id
/// se ejecutara la ultima de la cadena de proceso
/// </summary>
/// <param name="scene"></param>
void Game::loadScene(ecs::sc::sceneId scene)
{
	//llamar al init de la escena a cargar????
	gameScenes[scene]->init();
	//cargamos la escena
	loadedScenes.push_back(gameScenes[scene]);
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
		std::cout << "Scene Killed"<<std::endl;
	}
}

void Game::requestChangeScene(ecs::sc::sceneId scene1, ecs::sc::sceneId scene2)
{
	sceneChange = true;
	scene1_ = scene1;
	scene2_ = scene2;
}

void Game::changeScene(ecs::sc::sceneId scene1, ecs::sc::sceneId scene2) {
	auto it = std::find(gameScenes.begin(), gameScenes.end(), gameScenes[scene1]);
	(*it)->deleteAllEntities();
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

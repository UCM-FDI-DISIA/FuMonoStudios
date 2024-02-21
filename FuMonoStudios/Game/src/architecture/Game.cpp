#include "Game.h"
#include <list>
#include <SDL.h>
#include <algorithm>
#include "../sdlutils/InputHandler.h"
#include "../scenes/MainScene.h"
#include "../scenes/MainMenu.h"
#include "../scenes/ExplorationScene.h"
//#include "Game.h"
/*
TODO
Añadir fichero de configuracion el init de SDLUtils cuando haya recursos que cargar
*/

Game::Game():exit(false){
	SDLUtils::init("Mail To Atlantis",1600 , 900, "recursos/config/mail.resources.json");
	auto& sdl = *SDLUtils::instance();

	sdl.showCursor();
	window = sdl.window();
	renderer = sdl.renderer();
	gameScenes = {new ecs::MainScene(),new ecs::MainMenu(),new ecs::ExplorationScene() };
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
		ih().refresh();
		Uint32 startTime = SDL_GetTicks();

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE) || ih().closeWindowEvent()) {
			exit = true;
		}
		if (ih().isKeyDown(SDL_SCANCODE_F)) {
			sdlutils().toggleFullScreen();
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

//void Game::writeMessage() {
//
//	
//}

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

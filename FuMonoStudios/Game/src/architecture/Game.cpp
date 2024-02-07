#include "Game.h"
#include <list>
#include <SDL.h>
#include "../sdlutils/InputHandler.h"
/*
TODO
Añadir fichero de configuracion el init de SDLUtils cuando haya recursos que cargar
*/

Game::Game():exit(false) {
	SDLUtils::init("Mail To Atlantis", 800, 600);

	auto& sdl = *SDLUtils::instance();

	sdl.showCursor();
	window = sdl.window();
	renderer = sdl.renderer();

}

Game::~Game()
{

}


void Game::run()
{
	while (!exit)
	{
		ih().refresh();
		Uint32 startTime = SDL_GetTicks();

		if (ih().keyDownEvent() || ih().closeWindowEvent()) {
			exit = true;
		}

		update();

		render();

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
	//gameScenes[scene].init();
	//cargamos la escena
	loadedScenes.push_back(&gameScenes[scene]);
}


void Game::update()
{
	for (auto& scene : loadedScenes) {
		scene->update();
	}	
}

void Game::render()
{
	for (auto& scene : loadedScenes) {
		scene->render();
	}
}

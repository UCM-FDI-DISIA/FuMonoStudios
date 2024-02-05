#include "Game.h"
#include <list>
#include <SDL.h>
Game::Game():exit(false) {

}

Game::~Game()
{

}


void Game::run()
{
	while (!exit)
	{
		Uint32 startTime = SDL_GetTicks();

		update();

		render();

		Uint32 frameTime = SDL_GetTicks() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}
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

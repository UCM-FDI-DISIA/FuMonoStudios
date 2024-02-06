#pragma once
#include<list>
#include "Scene.h"
#include <SDL.h>
#include "../sdlutils/SDLUtils.h"
class Game
{
public:
	Game();
	~Game();
	void run();
private:
	void update();
	void render();
	//lista de escenas a procesar
	std::vector<ecs::Scene*> loadedScenes;
	//lista de todas las escenas del juego
	std::vector<ecs::Scene> gameScenes;
	bool exit;
	SDL_Window* window;
	SDL_Renderer* renderer;

};


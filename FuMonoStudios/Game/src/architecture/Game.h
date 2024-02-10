#pragma once
#include<list>
#include <SDL.h>
#include <array>
#include "../architecture/ecs.h"
#include "../sdlutils/SDLUtils.h"
#include "Scene.h"
class Game
{
public:
	Game();
	~Game();
	void run();
	void loadScene(ecs::sc::sceneId scene);
	void killScene(ecs::sc::sceneId scene);
private:
	void update();
	void render();
	//lista de escenas a procesar
	std::vector<ecs::Scene*> loadedScenes;
	//lista de todas las escenas del juego
	std::array<ecs::Scene*,ecs::sc::maxSceneId> gameScenes;
	bool exit;
	SDL_Window* window;
	SDL_Renderer* renderer;

};


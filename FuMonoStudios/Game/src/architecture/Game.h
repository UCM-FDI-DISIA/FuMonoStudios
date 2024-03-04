#pragma once
#include<list>
#include <SDL.h>
#include <array>
#include "../utils/Singleton.h"
#include "../architecture/ecs.h"
#include "../sdlutils/SDLUtils.h"
#include "Scene.h"

class Game: public Singleton<Game> {

	friend Singleton<Game> ;

public:
	Game();
	~Game();
	void run();
	/// <summary>
	/// Metodo para cargar una escena
	/// </summary>
	/// <param name="scene"></param>
	void loadScene(ecs::sc::sceneId scene);
	/// <summary>
	/// Metodo para descargar una escena
	/// </summary>
	/// <param name="scene"></param>
	void killScene(ecs::sc::sceneId scene);
	void changeScene(ecs::sc::sceneId scene1, ecs::sc::sceneId scene2);
	inline void writeMessage() {
		std::cout << "Funcionaaaaaaaaa" << std::endl;
	};
private:
	void update();
	void render();
	/// <summary>
	/// lista de escenas a procesar
	/// </summary>
	std::vector<ecs::Scene*> loadedScenes;
	/// <summary>
	/// lista de escenas del juego
	/// </summary>
	std::array<ecs::Scene*,ecs::sc::maxSceneId> gameScenes;
	bool exit;
	SDL_Window* window;
	SDL_Renderer* renderer;

};

inline Game& gm() {
	return *Game::instance();
}


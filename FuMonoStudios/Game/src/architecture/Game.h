#pragma once
#include<list>
#include <SDL.h>
#include <array>
#include "../utils/Singleton.h"
#include "../architecture/ecs.h"
#include "../sdlutils/SDLUtils.h"
#include "Scene.h"


class Game : public Singleton<Game> {

	friend Singleton<Game>;

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

	/// <summary>
	/// metodo para solicitar cambio de una escena a otra
	/// </summary>
	/// <param name="scene1"></param>
	/// <param name="scene2"></param>
	void requestChangeScene(ecs::sc::sceneId scene1, ecs::sc::sceneId scene2);

	/// <summary>
	/// metodo para cambiar de una escena a otra
	/// </summary>
	/// <param name="scene1"></param>
	/// <param name="scene2"></param>
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
	std::array<ecs::Scene*, ecs::sc::maxSceneId> gameScenes;
	bool exit;
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool sceneChange;
	ecs::sc::sceneId scene1_, scene2_; //una guarrada lo se, pero ahora mismo quiero que el juego no explote, ya se hara bonito

};

inline Game& gm() {
	return *Game::instance();
}

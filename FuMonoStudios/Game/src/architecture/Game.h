#pragma once
#include<list>
#include <SDL.h>
#include <array>
#include "../utils/Singleton.h"
#include "../architecture/ecs.h"
#include "../sdlutils/SDLUtils.h"
#include "Scene.h"
#include <functional>

class Game : public Singleton<Game> {

	friend Singleton<Game>;

public:
	Game();
	~Game();
	void run();
	/// <summary>
	/// Metodo para cargar una escena
	/// </summary>
	/// <param name="scene">Id de la escena a cargar</param>
	void loadScene(ecs::sc::sceneId scene);
	/// <summary>
	/// Metodo para descargar una escena
	/// </summary>
	/// <param name="scene">Id de la escena a matar</param>
	void killScene(ecs::sc::sceneId scene);

	/// <summary>
	/// Metodo para solicitar cambio de una escena a otra
	/// </summary>
	/// <param name="scene1"></param>
	/// <param name="scene2"></param>
	void requestChangeScene(ecs::sc::sceneId scene1, ecs::sc::sceneId scene2);

	inline void writeMessage() {
		std::cout << "Funcionaaaaaaaaa" << std::endl;
	};

private:
	/// <summary>
	/// Metodo para cambiar de una escena a otra
	/// </summary>
	/// <param name="scene1"></param>
	/// <param name="scene2"></param>
	void changeScene(ecs::sc::sceneId scene1, ecs::sc::sceneId scene2);

	void update();
	void render();
	void refresh();

	/// <summary>
	/// Lista de escenas a procesar
	/// </summary>
	std::vector<ecs::Scene*> loadedScenes_;
	/// <summary>
	/// Lista de escenas del juego
	/// </summary>
	std::array<ecs::Scene*, ecs::sc::maxSceneId> gameScenes_;
	bool exit_;
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	bool sceneChange_;
	ecs::sc::sceneId scene1_, scene2_; //una guarrada lo se, pero ahora mismo quiero que el juego no explote, ya se hara bonito


	std::list<std::function<void(void)>> requets;
};

inline Game& gm() {
	return *Game::instance();
}

#pragma once
#include<list>
#include <SDL.h>
#include <array>
#include <utils/Singleton.h>
#include <architecture/ecs.h>
#include <architecture/Config.h>
#include <architecture/Scene.h>
#include <functional>


#ifdef _DEBUG
#define DEV_TOOLS
#endif // _DEBUG
//#define QA_TOOLS


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
	/// Devuelve el puntero a una escena especificada
	/// </summary>
	/// <param name="sc"></param>
	/// <returns></returns>
	ecs::Scene* getScene(ecs::sc::sceneId sc) {
		return gameScenes_.at(sc);
	}
	/// <summary>
	/// Metodo para solicitar cambio de una escena a otra
	/// </summary>
	/// <param name="scene1"></param>
	/// <param name="scene2"></param>
	void requestChangeScene(ecs::sc::sceneId scene1, ecs::sc::sceneId scene2);
	/// <summary>
    /// Despausa el juego
    /// </summary>
	inline void pauseGame() {
		gamePaused_ = true;
	}
	/// <summary>
	/// Despausa el juego
	/// </summary>
	inline void unpauseGame() {
		gamePaused_ = false;
	}
	/// <summary>
	/// Indica si el juego esta pausado
	/// </summary>
	/// <returns></returns>
	inline bool gamePaused() {
		return gamePaused_;
	}
	/// <summary>
	/// Para la ejecucion del juego
	/// </summary>
	void endGame() { exit_ = true; }
private:
	/// <summary>
	/// Metodo para cambiar de una escena a otra
	/// </summary>
	/// <param name="scene1"></param>
	/// <param name="scene2"></param>
	void changeScene(ecs::sc::sceneId scene1, ecs::sc::sceneId scene2);

	/// <summary>
	/// Llama al update de cada entidad
	/// </summary>
	void update();
	/// <summary>
	/// Llama al render de cada entidad
	/// </summary>
	void render();
	/// <summary>
	/// Destruye todas las entidades que esten marcadas como alive false
	/// </summary>
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
	/// <summary>
	/// Puntero a la ventana de sdl
	/// </summary>
	SDL_Window* window_;
	/// <summary>
	/// Puntero al renderer de sdl
	/// </summary>
	SDL_Renderer* renderer_;

	/// <summary>
	/// Indica si en el frame se debe hacer la operacion de cambiar de escena
	/// </summary>
	bool sceneChange_;
	/// <summary>
	/// Indica si el juego esta pausado
	/// </summary>
	bool gamePaused_;
	/// <summary>
	/// Id de las escenas a cambiar
	/// </summary>
	ecs::sc::sceneId scene1_, scene2_;

	//las dos variables de mas adelante no estan en uso tal vez se use mas adelante
	std::queue<std::function<void(void)>> requets;

	float autoRecodTime = 0;
};

inline Game& gm() {
	return *Game::instance();
}

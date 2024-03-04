#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include "architecture/Game.h"
#include "sdlutils/SDLUtils.h"

int main(int argc, char* argv[]) {
	std::cout << "Hola Buenas Tardes";
	try {
		auto& game = *Game::instance();
		game.run(); 
	}
	catch (std::string e) {
		std::cout <<"ERROR: " << e << std::endl;
	}

	return 0;
}
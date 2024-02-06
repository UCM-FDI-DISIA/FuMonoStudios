#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "architecture/Game.h"
#include "sdlutils/SDLUtils.h"

int main(int argc, char* argv[]) {
	std::cout << "Hola Buenas Tardes";
	Game().run();

	return 0;
}
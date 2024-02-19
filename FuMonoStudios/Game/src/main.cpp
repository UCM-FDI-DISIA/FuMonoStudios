#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include "architecture/Game.h"
#include "sdlutils/SDLUtils.h"
#include "Dialogo.h"

int main(int argc, char* argv[]) {
	std::cout << "Hola Buenas Tardes";
	try {
		Game().run();
		Dialogo dialogo("resources/dialogos/dialogo.txt");
		dialogo.Run();
	}
	catch (std::string e) {
		std::cout <<"ERROR: " << e << std::endl;
	}

	

		return 0;
	}



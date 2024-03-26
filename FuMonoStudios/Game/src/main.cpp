#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include "architecture/Game.h"
#include "sdlutils/SDLUtils.h"
#include "utils/checkML.h"
#include "../rapidCSV/rapidcsv.h"



int main(int argc, char* argv[]) {
	std::cout << "Hola Buenas Tardes";
	/*rapidcsv::Document doc ("src/prueba.csv");
	std::vector<float> row = { 1,2,3,4,5,6,7,8 };
	doc.InsertRow<float>(0,row);*/
	try {
		Game::instance()->run();
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}
	catch (std::string e) {
		std::cout <<"ERROR: " << e << std::endl;
	}

	return 0;
}
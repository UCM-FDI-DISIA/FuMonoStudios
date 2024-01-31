#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window* window = SDL_CreateWindow("The Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,800, 600,SDL_WINDOW_RESIZABLE);
	SDL_Event evento;

	bool quit = false;

	while (!quit) {
		while (SDL_PollEvent(&evento)) {
			if (evento.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	return 0;
}


#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <SDL_ttf.h>

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    // create window and renderer

    SDL_Window* Window = SDL_CreateWindow("Text Rendering", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, 0);
    if (Window == NULL) { printf("Window creation failed: %s\n", SDL_GetError()); }
    SDL_Renderer* Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (Renderer == NULL) { printf("Renderer creation failed\n: %s", SDL_GetError()); }

    // create text texture

    TTF_Init();

    TTF_Font* Font = TTF_OpenFont("resources/fonts/ARIAL.ttf", 40);
    if (Font == NULL) { printf("Font loading failed: %s\n", TTF_GetError()); }

    SDL_Color textColor = { 255, 255, 255, 255 };

    SDL_Surface* TextSurface = TTF_RenderText_Blended_Wrapped(Font, "Mars is the fourth planet from the Sun and the second-smallest planet in the Solar System, being larger than only Mercury.", textColor, 500);
    if (TextSurface == NULL) { printf("Surface creation failed: %s\n", TTF_GetError()); }

    SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(Renderer, TextSurface);
    if (TextSurface == NULL) { printf("Texture creation failed: %s\n", TTF_GetError()); }

    uint32_t Running = 1;

    SDL_Event Event = { 0 };

    while (Running) {
        while (SDL_PollEvent(&Event)) {
            switch (Event.type) {
            case SDL_QUIT: { Running = 0; } break;
            case SDL_KEYDOWN: {
                switch (Event.key.keysym.sym) {
                case SDLK_o: { Running = 0; } break;
                }
            } break;
            }
        }

        SDL_SetRenderDrawColor(Renderer, 30, 30, 30, 255);
        SDL_RenderClear(Renderer);

        // display text

        SDL_Rect destRect = { 640 / 2 - TextSurface->w / 2, 640 / 2 - TextSurface->h / 2, TextSurface->w, TextSurface->h };
        SDL_RenderCopy(Renderer, TextTexture, NULL, &destRect);

        SDL_RenderPresent(Renderer);
    }

    SDL_Quit();

    return 0;
}


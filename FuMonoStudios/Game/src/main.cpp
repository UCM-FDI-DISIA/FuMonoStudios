#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <SDL_ttf.h>

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    // create window and renderer

    SDL_Window* Window = SDL_CreateWindow("Text Rendering", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, 0);
    if (Window == NULL) { printf("Window creation failed: %s\n", SDL_GetError()); return 1; }
    SDL_Renderer* Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (Renderer == NULL) { printf("Renderer creation failed\n: %s", SDL_GetError()); return 1; }

    // create text texture

    TTF_Init();

    TTF_Font* Font = TTF_OpenFont("resources/fonts/ARIAL.ttf", 20);
    if (Font == NULL) { printf("Font loading failed: %s\n", TTF_GetError()); return 1; }

    SDL_Color textColor = { 255, 255, 255, 255 };

    const char* textToWrite = "Día 1: El vagabundo estará en su caja de cartón en la calle donde está la oficina. El juego te indicará que puedes hablar con él y te forzará a hablar con él.";

    int textLength = 0;
    while (textToWrite[textLength] != '\0') {
        textLength++;
    }

    char* displayedText = (char*)malloc(textLength + 1);  // +1 for the null terminator
    displayedText[0] = '\0';  // Initialize as an empty string

    SDL_Surface* TextSurface = NULL;
    SDL_Texture* TextTexture = NULL;

    // Create a rectangle for the text box
    SDL_Rect textBoxRect = { 20, 480, 600, 120 }; // Adjust position and size as needed

    uint32_t Running = 1;

    SDL_Event Event = { 0 };

    int currentCharIndex = 0;
    int delayCounter = 0;
    int delayAmount = 50;  // Adjust the delay amount as needed

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

        if (currentCharIndex < textLength) {
            // Append the next character to the displayed text
            displayedText[currentCharIndex] = textToWrite[currentCharIndex];
            currentCharIndex++;
            displayedText[currentCharIndex] = '\0';  // Null-terminate the string

            // Update the text surface and texture
            if (TextSurface != NULL) {
                SDL_FreeSurface(TextSurface);
            }
            TextSurface = TTF_RenderText_Blended_Wrapped(Font, displayedText, textColor, 500);

            // Check that the surface is valid before updating the texture
            if (TextSurface != NULL && TextSurface->w > 0) {
                // Update the texture
                if (TextTexture != NULL) {
                    SDL_DestroyTexture(TextTexture);
                }
                TextTexture = SDL_CreateTextureFromSurface(Renderer, TextSurface);
            }
        }

        SDL_SetRenderDrawColor(Renderer, 30, 30, 30, 255);
        SDL_RenderClear(Renderer);

        // Render the text box
        SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(Renderer, &textBoxRect);

        // Display text inside the text box
        if (TextTexture != NULL) {
            SDL_Rect destRect = { textBoxRect.x + 10, textBoxRect.y + 10, TextSurface->w, TextSurface->h };
            SDL_RenderCopy(Renderer, TextTexture, NULL, &destRect);
        }

        SDL_RenderPresent(Renderer);

        // Delay between characters
        SDL_Delay(delayAmount);
    }

    free(displayedText);
    SDL_DestroyTexture(TextTexture);
    SDL_FreeSurface(TextSurface);
    SDL_Quit();

    return 0;
}

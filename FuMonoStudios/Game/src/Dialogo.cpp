// dialogo.cpp

#include "dialogo.h"
#include <iostream>

Dialogo::Dialogo()
    : window(nullptr), renderer(nullptr), font(nullptr),
    textToWrite("Día 1: ..."), textLength(0),
    displayedText(nullptr), TextSurface(nullptr), TextTexture(nullptr),
    currentCharIndex(0), delayCounter(0), delayAmount(50) {
    InitializeSDL();

    window = SDL_CreateWindow("Text Rendering", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    TTF_Init();
    font = TTF_OpenFont("resources/fonts/ARIAL.ttf", 20);

    textColor = { 255, 255, 255, 255 };

    while (textToWrite[textLength] != '\0') {
        textLength++;
    }

    displayedText = std::make_unique<char[]>(textLength + 1);
    displayedText[0] = '\0';

    TextSurface = nullptr;
    TextTexture = nullptr;

    textBoxRect = { 20, 480, 600, 120 };
}

Dialogo::~Dialogo() {
    Clean();
}

void Dialogo::InitializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Dialogo::CreateTextTexture() {
    if (TextSurface != nullptr) {
        SDL_FreeSurface(TextSurface);
    }

    TextSurface = TTF_RenderText_Blended_Wrapped(font, displayedText.get(), textColor, 500);

    if (TextSurface != nullptr && TextSurface->w > 0) {
        if (TextTexture != nullptr) {
            SDL_DestroyTexture(TextTexture);
        }
        TextTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);
    }
}

void Dialogo::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_o:
                exit(0);
                break;
            }
            break;
        }
    }
}

void Dialogo::UpdateText() {
    if (currentCharIndex < textLength) {
        displayedText[currentCharIndex] = textToWrite[currentCharIndex];
        currentCharIndex++;
        displayedText[currentCharIndex] = '\0';

        CreateTextTexture();
    }
}

void Dialogo::Render() {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &textBoxRect);

    if (TextTexture != nullptr) {
        SDL_Rect destRect = { textBoxRect.x + 10, textBoxRect.y + 10, TextSurface->w, TextSurface->h };
        SDL_RenderCopy(renderer, TextTexture, nullptr, &destRect);
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(delayAmount);
}

void Dialogo::Clean() {
    if (TextTexture != nullptr) {
        SDL_DestroyTexture(TextTexture);
        TextTexture = nullptr;
    }

    if (TextSurface != nullptr) {
        SDL_FreeSurface(TextSurface);
        TextSurface = nullptr;
    }
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Dialogo::Run() {
    while (true) {
        HandleEvents();
        UpdateText();
        Render();
    }
}

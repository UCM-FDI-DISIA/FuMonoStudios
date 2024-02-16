#include "dialogo.h"


Dialogo::Dialogo() {
  InitializeSDL();

  window = SDL_CreateWindow("Text Rendering", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  TTF_Init();
  font = TTF_OpenFont("resources/fonts/ARIAL.ttf", 20);

  textColor = { 255, 255, 255, 255 };

  textToWrite = "Día 1: El vagabundo estará en su caja de cartón en la calle donde está la oficina. El juego te indicará que puedes hablar con él y te forzará a hablar con él.";

  textLength = 0;
  while (textToWrite[textLength] != '\0') {
    textLength++;
  }

  displayedText = (char*)malloc(textLength + 1);
  displayedText[0] = '\0';

  TextSurface = NULL;
  TextTexture = NULL;

  textBoxRect = { 20, 480, 600, 120 };

  currentCharIndex = 0;
  delayCounter = 0;
  delayAmount = 50;
}

Dialogo::~Dialogo() {
  Clean();
}

void Dialogo::InitializeSDL() {
  SDL_Init(SDL_INIT_VIDEO);
}

void Dialogo::CreateTextTexture() {
  if (TextSurface != NULL) {
    SDL_FreeSurface(TextSurface);
  }

  TextSurface = TTF_RenderText_Blended_Wrapped(font, displayedText, textColor, 500);

  if (TextSurface != NULL && TextSurface->w > 0) {
    if (TextTexture != NULL) {
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

  if (TextTexture != NULL) {
    SDL_Rect destRect = { textBoxRect.x + 10, textBoxRect.y + 10, TextSurface->w, TextSurface->h };
    SDL_RenderCopy(renderer, TextTexture, NULL, &destRect);
  }

  SDL_RenderPresent(renderer);

  SDL_Delay(delayAmount);
}

void Dialogo::Clean() {
  free(displayedText);
  SDL_DestroyTexture(TextTexture);
  SDL_FreeSurface(TextSurface);
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

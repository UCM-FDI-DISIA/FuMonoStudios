#ifndef DIALOGO_H
#define DIALOGO_H

#include <SDL.h>
#include <SDL_ttf.h>

class Dialogo {
public:
  Dialogo();
  ~Dialogo();

  void Run();

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
  SDL_Color textColor;

  const char* textToWrite;
  int textLength;
  char* displayedText;

  SDL_Surface* TextSurface;
  SDL_Texture* TextTexture;

  SDL_Rect textBoxRect;

  int currentCharIndex;
  int delayCounter;
  int delayAmount;

  void InitializeSDL();
  void CreateTextTexture();
  void HandleEvents();
  void UpdateText();
  void Render();
  void Clean();
};

#endif // DIALOGO_H

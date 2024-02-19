
#ifndef DIALOGO_H
#define DIALOGO_H

#include "Dialog_Manager.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include <string> 
#include "architecture/Component.h"
using namespace std;
class Dialogo : public ecs::Component{
public:
    Dialogo(const std::string& dialogFilePath);
    ~Dialogo();

    void Run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color textColor;

    const char* textToWrite;
    int textLength;
    std::unique_ptr<char[]> displayedText;

    SDL_Surface* TextSurface;
    SDL_Texture* TextTexture;

    SDL_Rect textBoxRect;

    int currentCharIndex;
    int delayCounter;
    int delayAmount;
    int initialTextBoxY;

    DialogManager dialogManager;
    bool spacePressed;

    void InitializeSDL();
    void CreateTextTexture();
    void HandleEvents();
    void UpdateText();
    void render() const override;
    void Clean();
};

#endif // DIALOGO_H

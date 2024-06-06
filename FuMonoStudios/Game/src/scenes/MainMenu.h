#pragma once
#ifndef DEV_TOOLS
#include <utils/checkML.h>
#endif // !DEV_TOOLS
#include <architecture/Scene.h>

class Game;

namespace ecs {
    class MainMenu :
        public Scene
    {
        __SC_DECL__(ecs::sc::MAIN_SCENE)
    public:
        MainMenu();
        virtual ~MainMenu();

        void init() override;
    private:
        ecs::Entity* buildStartButton(Vector2D& pos,bool saveExist);
        ecs::Entity* buildLoadSaveButton(Vector2D& pos);
        ecs::Entity* buildShowEndsButton(Vector2D& pos);
        ecs::Entity* buildConfigButton(Vector2D& pos);
        ecs::Entity* buildExitButton(Vector2D& pos);

        const SDL_Color textColor_ = build_sdlcolor(0x111111ff);
        const SDL_Color hilightColor_ = build_sdlcolor(0x555555ff);
    };
}


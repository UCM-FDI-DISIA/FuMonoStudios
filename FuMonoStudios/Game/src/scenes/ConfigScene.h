#pragma once
#ifndef DEV_TOOLS
#include <utils/checkML.h>
#endif // !DEV_TOOLS
#include <architecture/Scene.h>

class Game;

namespace ecs {
    class ConfigScene : public Scene
    {
        __SC_DECL__(ecs::sc::CONFIG_SCENE)
    public:
        ConfigScene();
        virtual ~ConfigScene();
        void init() override;
    protected:
        Entity* mainMenuButton;
        const SDL_Color baseColor = build_sdlcolor(0x000000ff);
        const SDL_Color hilightColor = build_sdlcolor(0x444444ff);

    private:
        Texture* musicIconTexture_;
        Entity* musicIconEnt_;
        Texture* sfxIconTexture_;
        Entity* sfxIconEnt_;

        Texture* screenModeIconTexture_;
        Entity* screenModeIconEnt_;
        Texture* skipTutoIconTexture_;
        Entity* skipTutoIconEnt_;

        void createMusicOptions();
        void createSFXOptions();
        void createFullscreenOptions();
        void createSkipTutorialOptions();
    };

}


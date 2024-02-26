#pragma once
#include "../architecture/Scene.h"
#include "../architecture/ecs.h"

class Game;

namespace ecs {
    class MainMenu :
        public Scene
    {
    public:
        MainMenu();
        virtual ~MainMenu();

        void init() override;
        void changeToMainScene();
    };
}


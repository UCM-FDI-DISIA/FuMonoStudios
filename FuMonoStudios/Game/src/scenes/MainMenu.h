#pragma once
#include "../architecture/Scene.h"
#include "../architecture/ecs.h"

namespace ecs {
    class MainMenu :
        public Scene
    {
    public:
        MainMenu();
        virtual ~MainMenu();

        void init() override;
    };
}


#pragma once
#include "../architecture/Scene.h"
#include "../components/Transform.h"
namespace ecs {
    class Game;
    class MainScene :public Scene
    {
    public:
        MainScene();
        virtual ~MainScene();

        void init() override;
    };
}


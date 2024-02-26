#pragma once
#include "../architecture/Scene.h"
#include "../components/Transform.h"
namespace ecs {
    class Game;
    class MainScene :public Scene
    {
    private:
        void createManual();
    public:
        MainScene();
        virtual ~MainScene();

        void init() override;
    };
}


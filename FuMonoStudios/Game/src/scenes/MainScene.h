#pragma once
#include "../architecture/Scene.h"
#include "../components/Transform.h"
namespace ecs {
    class Game;
    class MainScene :public Scene
    {
    private:
        void createManual();
        void createPaquete(int lv);
    public:
        MainScene();
        virtual ~MainScene();

        void init() override;
    };
}


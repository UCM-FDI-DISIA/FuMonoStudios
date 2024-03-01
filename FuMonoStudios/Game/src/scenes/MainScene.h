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
        float timer = 10.0; 
    public:
        MainScene();
        virtual ~MainScene();

        void update() override;
        void init() override;
    };
}


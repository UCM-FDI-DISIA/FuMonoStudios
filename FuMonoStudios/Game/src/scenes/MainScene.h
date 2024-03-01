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
        bool timerPaused;
    public:
        MainScene();
        virtual ~MainScene();

        void update() override;
        void init() override;

        void controlTimer(bool onOff) { timerPaused = onOff; }
        void setTimer(float time) { timer = time; }
    };
}


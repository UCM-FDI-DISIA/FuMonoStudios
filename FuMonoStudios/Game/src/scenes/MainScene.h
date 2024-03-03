#pragma once
#include "../architecture/Scene.h"
#include "../components/Transform.h"
namespace ecs {
    class Game;
    class MainScene :public Scene
    {
    private:
        int fails;
        int correct;

        void createManual();
        void createPaquete(int lv);
        float timer; 
        bool timerPaused;
    public:
        MainScene();
        virtual ~MainScene();

        void update() override;
        void init() override;

        void switchTimer() { timerPaused = !timerPaused; }
        void setTimer(float time) { timer = time; }
    };
}


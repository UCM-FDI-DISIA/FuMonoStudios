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
        float timer;
        bool timerPaused;

        void createManual();
        void createPaquete(int lv);
        
    public:
        MainScene();
        virtual ~MainScene();

        virtual void update() override;
        void init() override;
        void switchTimer() { timerPaused = !timerPaused; }
        void setTimer(float time) { timer = time; }
    };
}


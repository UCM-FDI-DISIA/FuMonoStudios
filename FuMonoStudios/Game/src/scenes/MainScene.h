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

        virtual void update() override;
        void init() override;
        void switchTimer() { timerPaused = !timerPaused; }
        void setTimer(float time) { timer = time; }

    private:
        void createManual();
        void createPaquete(int lv);
        
        int fails;
        int correct;
        float timer;
        bool timerPaused;
        Font* timeFont;

        // objects
        Entity* timerEnt;
        Texture* timerTexture = nullptr;
        void updateTimer();
    };
}


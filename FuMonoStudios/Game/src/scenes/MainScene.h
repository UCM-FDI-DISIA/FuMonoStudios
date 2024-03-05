#pragma once
#include "../architecture/Scene.h"
#include "../components/Transform.h"
#include "../components/Paquete.h"

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

        Font* getFont() { return timeFont; }
    private:
        void createManual();
        void createTubo(Paquete::Distrito dist);
        void createSelladores();
        void createPaquete(int lv);
        
        int fails;
        int correct;
        float timer;
        bool timerPaused;
        Font* timeFont;

        // objects
        void initTexts(); // metodo auxiliar para limpio
        Entity* timerEnt;
        Texture* timerTexture;
        void updateTimer();

        Entity* failsEnt;
        Texture* failsTexture = nullptr;
        Entity* successEnt;
        Texture* successTexture = nullptr;
        void updateFailsText();
    };
}


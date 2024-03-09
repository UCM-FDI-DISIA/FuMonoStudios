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
        void switchTimer() { timerPaused_ = !timerPaused_; }
        void setTimer(float time) { timer_ = time; }

        Font* getFont() { return timeFont_; }
    private:
        void createManual();
        void createTubo(Paquete::Distrito dist);
        void createSelladores();
        void createPaquete(int lv);
        
        void updateTimer();

        void updateFailsText();

        int fails_;
        int correct_;
        float timer_;
        bool timerPaused_;
        Font* timeFont_;

        // objects
        void initTexts(); // metodo auxiliar para limpio
        Entity* timerEnt_;
        Texture* timerTexture_;

        Entity* failsEnt_;
        Texture* failsTexture_ = nullptr;
        Entity* successEnt_;
        Texture* successTexture_ = nullptr;
    };
}


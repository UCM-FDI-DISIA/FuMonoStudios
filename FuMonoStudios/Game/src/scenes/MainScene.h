#pragma once
#include "../architecture/Game.h"
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
        virtual void render() override;
        void close() override;
        void init() override;
        void switchTimer() { timerPaused_ = !timerPaused_; }
        void setTimer(float time) { timer_ = time; }

        Font* getFont() { return timeFont_; }
    private:
        void createManual();
        void createBalanza();
        void createClock();
        void createTubo(Paquete::Distrito dist);
        void createHerramientas();
        void createPaquete(int lv);
        
        void updateTimer();

        int fails_;
        int correct_;
        float timer_;
        bool timerPaused_;
        Font* timeFont_;
        
        int i = 0;
        float timeMultiplier = 1;
        float hours = 0;
        float minutes = 0;
        Vector2D clockCenter;
        Transform* trManecillaL;
        Transform* trManecillaS;
        // numeros magiquisimos para que roten las manecillas en el centro del reloj
        const float CONST_ROT = 57.3;
        const Vector2D offsetL = Vector2D(-14, -10);
        const float radiusManL = 13.2;
        const Vector2D offsetS = Vector2D(-15, 1);
        const float radiusManS = 6;
        // 

#ifdef DEV_TOOLS
        bool nextPacageCorrect_;
        bool stampsUnloked_;
        bool weightUnloked_;
        bool cintaUnloked_;
        int timeToAdd_;
#endif // DEV_TOOLS

        // objects
        void initTexts(); // metodo auxiliar para limpio
        Entity* timerEnt_;
        Texture* timerTexture_;
    };
}


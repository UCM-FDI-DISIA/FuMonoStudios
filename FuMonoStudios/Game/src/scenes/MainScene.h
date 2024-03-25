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
    private:
        void createManual();

        void createTubo(Paquete::Distrito dist, bool desbloqueado);

        void createClock();

        void createErrorMessage(Paquete* paqComp, bool, bool);

        void createSelladores();
        void createPaquete(int lv);

        void createInks();

        int fails_;
        int correct_;

        float timer_;
        bool timerPaused_;
        
        

#ifdef DEV_TOOLS
        bool nextPacageCorrect_;
        bool stampsUnloked_;
        bool weightUnloked_;
        bool cintaUnloked_;
        int timeToAdd_;
#endif // DEV_TOOLS

        // objects
    };
}


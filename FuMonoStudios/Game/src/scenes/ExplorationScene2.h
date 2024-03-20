#pragma once
#include "../architecture/Scene.h"
#include "../components/Transform.h"
#include "../components/Paquete.h"

namespace ecs {
    class Game;
    class ExplorationScene2 :public Scene
    {
    public:
        ExplorationScene2();
        virtual ~ExplorationScene2();

        virtual void update() override;
        void close() override;
        void init() override;

    private:




#ifdef _DEBUG

#endif // _DEBUG
    };
}



#pragma once
#include "../architecture/Scene.h"
#include "../../Mapa.h"
namespace ecs {
    class ExplorationScene :
        public Scene
    {
    private:
        Mapa map = Mapa();
    public:
        ExplorationScene();
        virtual ~ExplorationScene();
        void init() override;

    };
}



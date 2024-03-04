#pragma once
#include "../architecture/Scene.h"
#include "../sistemas/Mapa.h"
#include "../components/Dialog_Manager.h"


namespace ecs {

    class ExplorationScene :
        public Scene
    {
    public:
        ExplorationScene();
        virtual ~ExplorationScene();
        void init() override;
        void render();
    private:
         Mapa map;
    };
}



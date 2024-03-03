#pragma once
#include "../architecture/Scene.h"
#include "../components/Mapa.h"
#include "../components/Dialog_Manager.h"


namespace ecs {

    class ExplorationScene :
        public Scene
    {
    public:
        ExplorationScene();
        virtual ~ExplorationScene();
        void init() override;



    private:
        DialogManager dialogMngr_;
         Mapa map = Mapa();
    };
}



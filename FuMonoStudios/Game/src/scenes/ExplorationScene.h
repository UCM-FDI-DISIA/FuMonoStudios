#pragma once
#include "../architecture/Scene.h"
namespace ecs {
    class ExplorationScene :
        public Scene
    {
    public:
        ExplorationScene();
        virtual ~ExplorationScene();

        void init() override;
        virtual void render();


    private:
        DialogManager dialogMngr_;
         Mapa map;
    };
}



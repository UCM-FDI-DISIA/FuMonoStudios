#pragma once
#include "../architecture/Scene.h"
#include "../Dialog_Manager.h"
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
    };
}



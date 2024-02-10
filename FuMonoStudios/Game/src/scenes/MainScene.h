#pragma once
#include "../architecture/Scene.h"
namespace ecs {
    class MainScene :public Scene
    {
    public:
        MainScene();
        virtual ~MainScene();

        void init() override;
    };
}


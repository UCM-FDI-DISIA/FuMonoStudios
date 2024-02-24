#pragma once
#include "../architecture/Component.h"
#include "../Dialog_Manager.h"

class Transform;
class RenderImage;

class DialogComponent :
    public ecs::Component
{
public:
    __CMP_DECL__(ecs::cmp::DIALOGUE)

    DialogComponent(DialogManager* manager);
    ~DialogComponent(){};
    void initComponent()override;
    void update()override;
private:
    Transform* mTr_;
    RenderImage* mRend_;
    DialogManager* mDialogMngr_;

    int dialogueWidth_;
    int dialogueIndex;

    uint32_t lasTimePaused = 0;
    //Font* dialogueFont_;
};


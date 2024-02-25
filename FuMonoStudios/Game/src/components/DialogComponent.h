#pragma once
#include "../architecture/Component.h"
#include "../Dialog_Manager.h"
#include "../sdlutils/Font.h"
#include <string>


class Transform;
class RenderImage;
class Font;
class Texture;

class DialogComponent :
    public ecs::Component
{
public:
    __CMP_DECL__(ecs::cmp::DIALOGUE)

    //mas adelante hacer que la fuente se inicie sola
    DialogComponent(DialogManager* manager);
    ~DialogComponent();
    void initComponent()override;
    void update()override;
private:

    void setCurrentDialogue();

    Transform* mTr_;
    RenderImage* mRend_;
    DialogManager* mDialogMngr_;

    Font* mFont_;
    Texture* textTexture_;

    int dialogueWidth_;
    int dialogueIndex;




    uint32_t lasTimePaused = 0;
    //Font* dialogueFont_;
};


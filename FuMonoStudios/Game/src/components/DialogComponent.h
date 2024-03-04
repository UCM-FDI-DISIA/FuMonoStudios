#pragma once
#include "../architecture/Component.h"
#include "Dialog_Manager.h"
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

    //mas adelante hacer que la fuente se inicie solaz
    DialogComponent(DialogManager* manager);
    ~DialogComponent();
    void initComponent()override;
    void update()override;
private:
    /// <summary>
    /// Metodo para actualizar la textura de di�logo
    /// </summary>
    void setCurrentDialogue();

    Transform* mTr_;
    RenderImage* mRend_;
    DialogManager* mDialogMngr_;

    Font* mFont_;
    Texture* textTexture_;
    /// <summary>
    /// Ancho maximo al que va a llegar el texto
    /// </summary>
    int dialogueWidth_;
    /// <summary>
    /// Indice de hasta que caracter se va a escribir
    /// </summary>
    int dialogueIndex;

    uint32_t lasTimePaused = 0;
    //Font* dialogueFont_;
};


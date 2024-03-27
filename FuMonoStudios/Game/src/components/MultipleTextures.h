#pragma once
#include "Render.h"
#include "../architecture/Component.h"

class Texture;

/*
SCRIPT OBSOLETO USAR RENDER IMAGE
*/
class MultipleTextures : public ecs::Component
{
public:
    __CMP_DECL__(ecs::cmp::MULTIPLETEXTURES)
    MultipleTextures();
    MultipleTextures(const std::vector<Texture*>& textures);
    ~MultipleTextures();

    void initComponent() override;
    void addTexture(Texture* texture);
    void nextTexture();
    void previousTexture();
    void restartTexture();
    Texture* getCurrentTexture() { return *currentTexture_; } 
private:
    std::vector<Texture*> texturesVector_;
    std::vector<Texture*>::iterator currentTexture_;
    RenderImage* mRend_;
};


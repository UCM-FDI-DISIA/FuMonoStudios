#pragma once
#include "Render.h"
#include "../architecture/Component.h"

class Texture;

class MultipleTextures : public ecs::Component
{
private:
    std::vector<Texture*> texturesVector_;
    std::vector<Texture*>::iterator currentTexture_;
    RenderImage* renderImage_;
public:
    __CMP_DECL__(ecs::cmp::MULTIPLETEXTURES)
    MultipleTextures();
    MultipleTextures(const std::vector<Texture*>& textures);
    ~MultipleTextures();

    void initComponent() override;
    void addTexture(Texture* texture);
    void nextTexture();
    void previousTexture();
    Texture* getCurrentTexture() { return *currentTexture_; }
};


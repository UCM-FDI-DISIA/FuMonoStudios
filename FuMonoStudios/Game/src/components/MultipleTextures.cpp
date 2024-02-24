#include "MultipleTextures.h"

#include "Render.h"
#include "../architecture/Entity.h"

MultipleTextures::MultipleTextures()
{
}

MultipleTextures::MultipleTextures(const std::vector<Texture*>& textures)
{
    texturesVector_ = textures;
}

MultipleTextures::~MultipleTextures()
{
}

void MultipleTextures::addTexture(Texture* texture)
{
    texturesVector_.push_back(texture);
}

void MultipleTextures::nextTexture()
{
    currentTexture_++;
    //llamada a cambio de textura del render image
}

void MultipleTextures::previousTexture()
{
    currentTexture_--;
    //llamada a cambio de textura del render image
}

void MultipleTextures::initComponent()
{
    renderImage_ = ent_->getComponent<RenderImage>();
    if (texturesVector_.size() != 0)
        currentTexture_ = texturesVector_.begin();
}

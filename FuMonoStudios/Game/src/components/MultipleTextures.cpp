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
    if (currentTexture_ == texturesVector_.end() - 1) //por si acaso, pero lo ideal seria que los botones de siguiente pag no aparecieran si no se puede avanzar mas en el libro en esa direccion
        return;
    currentTexture_++;
    mRend_->setTexture(*currentTexture_);
}

void MultipleTextures::previousTexture()
{
    if(currentTexture_ == texturesVector_.begin()) //por si acaso, pero lo ideal seria que los botones de siguiente pag no aparecieran si no se puede avanzar mas en el libro en esa direccion
        return;
    currentTexture_--;
    mRend_->setTexture(*currentTexture_);
}

void MultipleTextures::restartTexture() {

    currentTexture_ = texturesVector_.begin();

    mRend_->setTexture(*currentTexture_);

}

void MultipleTextures::initComponent()
{
    mRend_ = ent_->getComponent<RenderImage>();
    if (texturesVector_.size() != 0)
        currentTexture_ = texturesVector_.begin();
}

#pragma once
#include "Render.h"
#include "../architecture/Component.h"

class Texture;

/*
Componente que almacena un vector de texturas para una entidad
Como usar este componente:
- Poner a la entidad un RenderImage
- Poner este componente y todas las texturas que se vayan a usar (una a una mediante addTexture() o todas a la vez en un vector
al ponets el componente)
- Llamar al init de este componente
- Llamar al setTexture del RenderImage pasandole getCurrentTexture()
- Si se quiere pasar a la siguiente o anterior textura llamar al método correspondiente
*/
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


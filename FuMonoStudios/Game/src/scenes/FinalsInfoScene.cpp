#include "FinalsInfoScene.h"
#include <sistemas/ComonObjectsFactory.h>
#include "entities/Final.h"
#include <architecture/Game.h>

FinalsInfoScene::FinalsInfoScene()
{

    // Fondo escena
    factory_->setLayer(ecs::layer::BACKGROUND);
    ecs::Entity* fondo = factory_->createImage(Vector2D(0, 0), &sdlutils().images().at("finalFondo"));

    // Final
    final_ = new Final(factory_, Vector2D(1600, 600), Vector2D(100, 200));
    final_->setActive(false);

    // IDs de las imagenes de los emblemasNpcs por orden segun el enum de NPC.h porque vamos a recorrerlo
    std::vector<std::string> npcIDs_ = { "AnemosEmblema","GargafielEmblema", "PancracioEmblema",
    "PaulinoEmblema", "abiEmblema", "SoldadoEmblema", "GloverEmblema"};

    factory_->setLayer(ecs::layer::UI);

    // Boton de atras
    CallbackClickeable callback = [this]() {
        setActiveButtons(true, npcButtons_); // activa los npcButtons_
        setActiveButtons(false, finalButtons_); // desactiva los finalButtons_
        setActiveButtons(false, finalButtonsAdicionales_);
        final_->setActive(false); // desactiva periodico con el final
    };
    auto textColor = build_sdlcolor(0xffffffff);
    factory_->setFont("hvdComicSerif");
    auto backButton = factory_->createTextuButton(Vector2D(210, 50), "Atras", 80, callback, "click", textColor);
    factory_->addHoverColorMod(backButton);

    finalButtons_.push_back(backButton);

    // Creamos los npcButtons_
    int i = 0;
    int offsetX = 50;
    int offsetY = 180;
    for (const auto& id : npcIDs_) {
        CallbackClickeable callback = [this, i]() {
            selectedPer_ = (Personaje)i;
            setActiveButtons(true, finalButtons_); // Activa los finalButtons_
            if (selectedPer_ == Personaje::Vagabundo || selectedPer_ == Personaje::Secretario) {
                setActiveButtons(true, finalButtonsAdicionales_);
            }
            else {
                setActiveButtons(false, finalButtonsAdicionales_);
            }
        };
        Texture* emblemaTex = &sdlutils().images().at(id);
        ecs::Entity* button = factory_->createImageButton(Vector2D(250 * (i % 3) + offsetX, 250 * (i / 3) + offsetY), Vector2D(250, 250), emblemaTex, callback, "click");
        i++;

        factory_->addHoverColorMod(button, build_sdlcolor(0xaaaaaaff));

        npcButtons_.push_back(button);
    }

    // Creamos los finalButtons_
    for (int i = 0; i < 4; i++) {
        CallbackClickeable callback = [this, i, backButton]() {
            setActiveButtons(false, npcButtons_); // desactiva los npcButtons_
            setActiveButtons(false, finalButtons_); // desactiva los finalButtons_
            setActiveButtons(false, finalButtonsAdicionales_);
            final_->loadFinal(selectedPer_, (Felicidad)(i + 2));
            final_->setActive(true);
            backButton->setActive(true);
        };

        auto button = factory_->createTextuButton(Vector2D(850, 300 + 100* i), "Final con Felicidad " + gD().felicidadToString((Felicidad)(i + 2)), 70, callback, "click", textColor);
        factory_->addHoverColorMod(button);

        finalButtons_.push_back(button);
    }

    // Creamos los finalButtonsAdicionales_ que son los dos finales adicionales que vagabundo y secretario incluyen
    for (int i = 0; i < 2; i++) {
        CallbackClickeable callback = [this, i, backButton]() {
            setActiveButtons(false, npcButtons_); // desactiva los npcButtons_
            setActiveButtons(false, finalButtons_); // desactiva los finalButtons_
            setActiveButtons(false, finalButtonsAdicionales_); // desactiva los finalButtons_
            final_->loadFinal(selectedPer_, (Felicidad)(i + 7));
            final_->setActive(true);
            backButton->setActive(true);
        };

        auto button = factory_->createTextuButton(Vector2D(850, 700 + 100 * i), "Final secreto " + std::to_string(i + 1), 70, callback, "click", textColor);
        factory_->addHoverColorMod(button);

        finalButtonsAdicionales_.push_back(button);
    }

    // Boton para volver al menu
    CallbackClickeable callbackMenu = [this]() {
        gm().requestChangeScene(ecs::sc::FINALS_INFO_SCENE , ecs::sc::MENU_SCENE);
    };

    auto menuButton = factory_->createTextuButton(Vector2D(120, 970), "Menu", 80, callbackMenu, "click", textColor);
    factory_->addHoverColorMod(menuButton);

    // Start Confi
    setActiveButtons(false, finalButtons_); // desactiva los finalButtons_
    setActiveButtons(false, finalButtonsAdicionales_);
    setActiveButtons(true, npcButtons_); // activa los npcButtons_
    backButton->setActive(false);
    menuButton->setActive(true);
}

void FinalsInfoScene::init()
{

}

void FinalsInfoScene::update()
{
    Scene::update();
}

void FinalsInfoScene::close()
{
    setActiveButtons(false, finalButtons_);
    setActiveButtons(false, finalButtonsAdicionales_);
    setActiveButtons(true, npcButtons_);
    final_->setActive(false);
}

void FinalsInfoScene::setActiveButtons(bool enable, std::vector<ecs::Entity*> buttons)
{
    for (const auto& button : buttons) {
        button->setActive(enable);
    }
}



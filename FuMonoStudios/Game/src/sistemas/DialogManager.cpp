// dialog_manager.cpp
#ifndef DEV_TOOLS
#include <utils/checkML.h>
#endif // !DEV_TOOLS
#include "DialogManager.h"
#include <components/DialogComponent.h>
#include <components/Render.h>
#include <QATools/DataCollector.h>
#include <sistemas/ComonObjectsFactory.h>
#include <sistemas/SoundEmiter.h>


DialogManager::DialogManager() : scene_(nullptr), currentDialogIndex_(0),boxBackground(nullptr), textDialogue(nullptr), endDialogueCallback(nullptr),
                                dialogSound_("")
{

}

DialogManager::~DialogManager()
{
}


void DialogManager::init(ecs::Scene* scene)
{
    init(scene, "recursos/data/dialogos.json");
}

void DialogManager::init(ecs::Scene* scene, const std::string& path) {

    scene_ = scene;

    jsonPath = path;

    canStartConversation = true;

    dialogueCooldownTime = 100;
    timer_ = sdlutils().virtualTimer().currTime();
    dialogueCooldown = dialogueCooldownTime + sdlutils().virtualTimer().currTime();
    controlTimer = false;
}

void DialogManager::update()
{
    if(controlTimer)
    {
        timer_ = sdlutils().virtualTimer().currTime();
        if(timer_ > dialogueCooldown)
        {
            canStartConversation = true;
            controlTimer = false;
        }
    }
}

std::string DialogManager::getCurrentDialog() {
    if (currentDialogIndex_ < dialogs_.size()) {
        return dialogs_[currentDialogIndex_];
    }
    else {
        return " "; // No hay m�s di�logos. cleon: ultramegamaxi MAL
    }
}


bool DialogManager::nextDialog() {

    bool isEndOfConversation = (currentDialogIndex_ >= dialogs_.size() - 1);

    if (isEndOfConversation) {

        currentDialogIndex_ = 0;
    }
    else {
        currentDialogIndex_++;
    }
    return isEndOfConversation;
}

void DialogManager::setDialogues(const DialogSelection ds, const std::string& tipoDialogo, int dialogueIteration)
{
    //eliminamos los dialogos anteriores
    dialogs_.clear();
    //reseteamos la posicon del indice
    currentDialogIndex_ = 0;

    std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(jsonPath));

    // check it was loaded correctly
    // the root must be a JSON object
    if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
        throw config_File_Missing(jsonPath);
    }
    // we know the root is JSONObject
    JSONObject root = jValueRoot->AsObject();
    JSONValue* jsonEntry = nullptr;

    const std::string& stringDialogSel = dialogSelectionToString(ds);
    auto a =gD().getDay();
    jsonEntry = root[stringDialogSel];
    if (jsonEntry != nullptr)
    {
        std::string strDialogo = tipoDialogo;

        // Si hemos elegido un setDialogue tipo 3
        if (strDialogo == "NULL")
        {
            if (!jsonEntry->IsArray())
                throw std::runtime_error("No es array el dialogo: " + stringDialogSel);

            for (auto& value : jsonEntry->AsArray())
            {
                if (value->IsString()) {
                    std::string valueText = value->AsString();

                    fixText(valueText);

                    dialogs_.push_back(valueText);
                }
                else {
                    throw std::runtime_error("Valor no string en el array: " + stringDialogSel);
                }
            }
        }
        // si hemos elegido un setDialogue tipo 2
        else if (dialogueIteration == -1)
        {
            JSONObject jsonEntryObj = jsonEntry->AsObject();
            // Accede al tipo de diálogo específico
            jsonEntry = jsonEntryObj[strDialogo];

            if (!jsonEntry->IsArray())
                throw std::runtime_error("No es array el dialogo: " + stringDialogSel);

            for (auto& value : jsonEntry->AsArray())
            {
                if (value->IsString()) {
                    std::string valueText = value->AsString();

                    fixText(valueText);

                    dialogs_.push_back(valueText);
                }
                else {
                    throw std::runtime_error("Valor no string en el array: " + stringDialogSel);
                }
            }
        }
        // si hemos elegido setDialogue tipo 3 (como tipo 2 pero iterable)
        else
        {
            JSONObject jsonEntryObj = jsonEntry->AsObject();
            // Accede al tipo de diálogo específico
            jsonEntry = jsonEntryObj[strDialogo];

            jsonEntryObj = jsonEntry->AsObject();

            jsonEntry = jsonEntryObj[std::to_string(dialogueIteration)];

            for (auto& value : jsonEntry->AsArray())
            {
                if (value->IsString()) {
                    std::string valueText = value->AsString();

                    fixText(valueText);

                    dialogs_.push_back(valueText);
                }
                else {
                    throw std::runtime_error("Valor no string en el array: " + stringDialogSel);
                }
            }

            if (isNPC(ds))
            {
                gD().getNPCData(gD().stringToPersonaje(dialogSelectionToString(ds)))->iterateDialogues();
            }
        }
    }
    else
    {
        throw std::runtime_error("Fallo en la carga de dialogo: " + stringDialogSel);
    }
}

void DialogManager::setDialogues(std::string& dialogo, std::string character) //mirar en el .h por que no es const juro que tiene sentido
{
    dialogs_.clear();

    fixText(dialogo);
    setCurrentDialogSound(character);
    SoundEmiter::instance()->playSound(dialogSound_);

    dialogs_.push_back(dialogo);
}

void DialogManager::startConversation(const std::string& character)
{
    if(canStartConversation)
    {
        auto charac = gD().stringToPersonaje(character); //de que personaje queremos el dialogo
        auto data = gD().getNPCData(charac); //data de dicho personaje
        setCurrentDialogSound(character);
        if (dialogSound_ != "") {
            SoundEmiter::instance()->playSound(dialogSound_);
        }   

        // activamos los dialogos correspondientes
        std::pair<const std::string, int> aux = data->getDialogueInfo(); 


        setDialogues((DialogSelection)gD().stringToPersonaje(character), aux.first, aux.second);

        setDialogueEntitiesActive(true);

#ifdef _DEBUG
        std::cout << "jefe otro dialogo que este tenia un agujero\n";
#endif // _DEBUG

#ifdef QA_TOOLS
        dataCollector().recordNPC(charac + 1, aux.second, gD().getNPCData(charac)->felicidad);
#endif // QA_TOOLS

        canStartConversation = false;
    }
}

void DialogManager::startConversationWithObj(const std::string& interactableObj)
{
    if (canStartConversation)
    {
        const std::string aux1 = std::to_string(gD().getDay());

        const std::string aux2 = std::to_string(sdlutils().rand().nextInt(0, 2));

        setDialogues((DialogManager::DialogSelection)(gD().stringToObjInt(interactableObj) + DialogManager::DialogSelection::CasaGrande), "Texto"+interactableObj+aux1+aux2);

        setDialogueEntitiesActive(true);
#ifdef _DEBUG
        std::cout << "jefe otro dialogo que este tenia un agujero\n";
#endif // _DEBUG

        canStartConversation = false;
    }
}

void DialogManager::startConversation(DialogSelection enter, int numIteration, const std::string& character) {
    if (canStartConversation) {

        setDialogues(enter, std::to_string(numIteration));

        setCurrentDialogSound(character);
        /*if (dialogSound_ != "") {
            SoundEmiter::instance()->playSound(dialogSound_);
        }*/

        setDialogueEntitiesActive(true);

        canStartConversation = false;
    }
}

void DialogManager::closeDialogue()
{
    setDialogueEntitiesActive(false);

    timer_ = sdlutils().virtualTimer().currTime();
    dialogueCooldown = sdlutils().virtualTimer().currTime() + dialogueCooldownTime  ;
    controlTimer = true;
    dialogSound_ = "";

    if (endDialogueCallback != nullptr)
        endDialogueCallback();
}

void DialogManager::setDialogueEntitiesActive(bool onoff) //me sigue pareciendo estupido lo de crear y destruir las cosas constantemente cuando las podemos reutilizar pero bueno si lo quereis asi
{
    /*boxBackground->setActive(onoff);
    textDialogue->setActive(onoff);*/
    if (onoff)
    {
        createBox();
        createText();
    }
    else
    {
        if(boxBackground != nullptr)
            boxBackground->setAlive(false);
        if (textDialogue != nullptr)
            textDialogue->setAlive(false);
    }
    
}

void DialogManager::fixText(std::string& text)
{
  size_t pos = 0;
  while ((pos = text.find('$', pos)) != std::string::npos) {
    if (pos > 0) {
      std::string newChar;
      switch (text[pos + 1]) {
      case 'a':
        newChar = "á";
        break;
      case 'e':
        newChar = "é";
        break;
      case 'i':
        newChar = "í";
        break;
      case 'o':
        newChar = "ó";
        break;
      case 'u':
        newChar = "ú";
        break;
      case 'A':
        newChar = "Á";
        break;
      case 'E':
        newChar = "É";
        break;
      case 'I':
        newChar = "Í";
        break;
      case 'O':
        newChar = "Ó";
        break;
      case 'U':
        newChar = "Ú";
        break;
      case '!':
        newChar = "¡";
        break;
      case '?':
        newChar = "¿";
        break;
      case '%':
        newChar = "ñ";
        break;
      }
      text.replace(pos, 2, newChar);  // Reemplazar el carácter anterior y el $
    }
    pos++;  // Avanzar la posición de búsqueda para evitar un bucle infinito si se encuentra un $
  }
}

const std::string& DialogManager::getDialogSound()
{
    return dialogSound_;
}

std::string DialogManager::dialogSelectionToString(const DialogSelection ds)
{
    std::string aux;
    switch (ds)
    {
    case Vagabundo:
        aux = "Vagabundo";
        break;
    case Secretario:
        aux = "Secretario";
        break;
    case Campesino:
        aux = "Campesino";
        break;
    case Artesano:
        aux = "Artesano";
        break;
    case Tarotisa:
        aux = "Tarotisa";
        break;
    case Soldado:
        aux = "Soldado";
        break;
    case Contable:
        aux = "Contable";
        break;
    case Jefe:
        aux = "Jefe";
        break;
    case Tutorial:
        aux = "Tutorial";
        break;
    case Intro:
        aux = "Intro";
        break;
    case ExplorationEnter:
        aux = "ExplorationEnter";
        break;
    case NoHabladoWarning:
        aux = "NoHabladoWarning";
        break;

    //Dialogos objetos distritos
        //Hestia
    case CasaGrande: aux = "CasaGrande"; break;
    case CartelOficina: aux = "CartelOficina"; break;
    case Muro: aux = "Muro"; break;

        //Artemisa
    case TiendaPociones: aux = "TiendaPociones"; break;
    case TiendaBolas: aux = "TiendaBolas"; break;
    case TiendaJarrones: aux = "TiendaJarrones"; break;

        //Demeter
    case Molino: aux = "Molino"; break;
    case Arbol: aux = "Arbol"; break;
    case Carreta: aux = "Carreta"; break;

        //Hefesto
    case PulpoCartel: aux = "PulpoCartel"; break;
    case TiendaCeramica: aux = "TiendaCeramica"; break;
    case TiendaEsculturas: aux = "TiendaEsculturas"; break;

        //Hermes
    case TiendaDerecha: aux = "TiendaDerecha"; break;
    case PanteonIzq: aux = "PanteonIzq"; break;
    case PanteonDer: aux = "PanteonDer"; break;

        //Apolo
    case Panteon: aux = "Panteon"; break;
    case Edificios: aux = "Edificios"; break;
    case Charco: aux = "Charco"; break;

        //Poseidon
    case Estatua: aux = "Estatua"; break;
    case ArbolesIzq: aux = "ArbolesIzq"; break;
    case ArbolesDer: aux = "ArbolesDer"; break;

    //default: break;
    }
    return aux;
}

bool DialogManager::isNPC(const DialogSelection ds)
{
    return ds < Jefe;
}

void DialogManager::createBox()
{
    Vector2D pos = Vector2D(30, LOGICAL_RENDER_HEITH - 250);
    Vector2D size = Vector2D(LOGICAL_RENDER_WIDTH - 60, 225);
    scene_->getFactory()->setLayer(ecs::layer::UI);
    boxBackground = scene_->getFactory()->createImage(pos, size, &sdlutils().images().at("cuadroDialogo"));
    scene_->getFactory()->setLayer(ecs::layer::DEFAULT);
}

void DialogManager::createText()
{
    textDialogue = scene_->addEntity(ecs::layer::UI);
    auto textTr = textDialogue->addComponent<Transform>(100, 45, 80, 100);
    textTr->setParent(boxBackground->getComponent<Transform>());
    textDialogue->addComponent<RenderImage>();
    textDialogue->addComponent<DialogComponent>(this);
    scene_->getFactory()->setLayer(ecs::layer::DEFAULT);
}

void DialogManager::setCurrentDialogSound(const std::string& pers)
{
    if (pers == "Vagabundo")
        dialogSound_ = "dlgVag";
    else if (pers == "Secretario")
        dialogSound_ = "dlgSecr";
    else if (pers == "Campesino")
        dialogSound_ = "dlgCamp";
    else if (pers == "Artesano")
        dialogSound_ = "dlgArt";
    else if (pers == "Tarotisa")
        dialogSound_ = "dlgTart";
    else if (pers == "Soldado")
        dialogSound_ = "dlgSold";
    else if (pers == "Contable")
        dialogSound_ = "dlgCont";
    else if (pers == "Jefe")
        dialogSound_ = "dlgJef";
    /*else
        dialogSound_ = "typewritter";*/
}

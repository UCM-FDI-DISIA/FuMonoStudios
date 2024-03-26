// dialog_manager.cpp
#include "dialog_manager.h"
#include <fstream>
#include "../json/JSON.h"
#include "../json/JSONValue.h"

DialogManager::DialogManager() : currentDialogIndex_(0) {
}



std::string DialogManager::getCurrentDialog() {
    if (currentDialogIndex_ < dialogs_.size()) {
        return dialogs_[currentDialogIndex_];
    }
    else {
        return ""; // No hay m�s di�logos. cleon: ultramegamaxi MAL
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

// un string sin referencia es como un d�a sin sol: const string&
void DialogManager::setDialogues(const Personaje personaje, const TipoDialog tipoDialogo, int dialogueSelection) 
{
    //eliminamos los dialogos anteriores
    dialogs_.clear();
    //reseteamos la posicon del indice
    currentDialogIndex_ = 0;

    std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile("recursos/dialogos/dialogos.json"));

    // check it was loaded correctly
    // the root must be a JSON object
    if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
        throw "Something went wrong while load/parsing dialogues";
    }
    // we know the root is JSONObject
    JSONObject root = jValueRoot->AsObject();
    JSONValue* jValue = nullptr;

    const std::string& charName = personajeToString(personaje);

    const std::string& typeDialog = tipoDialogToString(tipoDialogo, dialogueSelection);

    jValue = root[charName];
    if (jValue != nullptr && jValue->IsObject())
    {
        JSONObject charObj = jValue->AsObject();
        if (tipoDialogo != NOTYPE)
            jValue = charObj[typeDialog]; // Accede al tipo de diálogo específico


        if (jValue != nullptr && jValue->IsArray())
        {
            for (auto& dialogValue : jValue->AsArray())
            {
                if (dialogValue->IsString())
                {
                    std::string dialogText = dialogValue->AsString();
#ifdef _DEBUG
                    std::cout << "Cargando diálogo: " << dialogText << std::endl;
#endif
                    dialogs_.push_back(dialogText);
                }
                else
                {
                    throw std::runtime_error("Valor inválido en el arreglo de dialogos");
                }
            }
        }
    }
}

const std::string DialogManager::personajeToString(const Personaje pers) {
    std::string aux = "";

    switch (pers) {
        case Campesino:
            aux = "Campesino";
            break;
        case Secretario:
            aux = "Secretario";
            break;
        case Vagabundo:
            aux = "Vagabundo";
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
            aux = "Campesino";
            break;
        case JefeOficina:
            aux = "JefeOficina";
            break;
    }

    return aux;
}

const std::string DialogManager::tipoDialogToString(const TipoDialog tipo, int dialogueSelection) {
    std::string aux = "";

    switch (tipo) {
    case Presentacion:
        aux = "Presentacion";
        break;
    case FelMinimo:
        aux = "FelicidadMinima";
        break;
    case FelMaximo:
        aux = "FelicidadMaxima";
        break;
    case Genericos:
        aux = "Genericos";
        break;
    case Eventos:
        aux = "Eventos";
        break;
    case NPCgrande:
        aux = "Dia";
        break;
    case NPCgrandePostConversacion:
        aux = "PostConversacionDia";
        break;
    case NOTYPE:
        aux = "NOTYPE";
        break;

    }

    if (dialogueSelection != -1)
        aux = aux + std::to_string(dialogueSelection);

    return aux;
}
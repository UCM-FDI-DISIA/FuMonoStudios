// dialog_manager.cpp
#include "DialogManager.h"
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

void DialogManager::setDialogues(const GeneralData::Personaje personaje, const std::string& tipoDialogo, int dialogueSelection)
{
    //eliminamos los dialogos anteriores
    dialogs_.clear();
    //reseteamos la posicon del indice
    currentDialogIndex_ = 0;

    std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile("recursos/data/dialogos.json"));

    // check it was loaded correctly
    // the root must be a JSON object
    if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
        throw "Something went wrong while load/parsing dialogues";
    }
    // we know the root is JSONObject
    JSONObject root = jValueRoot->AsObject();
    JSONValue* jValue = nullptr;

    const std::string& charName = generalData().personajeToString(personaje);

    jValue = root[charName];
    if (jValue != nullptr && jValue->IsObject())
    {
        std::string strDialogo = tipoDialogo;
        JSONObject charObj = jValue->AsObject();
        if (dialogueSelection != -1)
            strDialogo = strDialogo + std::to_string(dialogueSelection);
        if (strDialogo != "NOTYPE")
            jValue = charObj[strDialogo]; // Accede al tipo de diálogo específico


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

                    if (dialogueSelection != -1)
                    {
                        generalData().getNPCData(personaje)->iterateDialogues();
                        if (dialogueSelection > 3)
                            dialogueSelection = 0;
                    }
                        
                        
                }
                else
                {
                    throw std::runtime_error("Valor inválido en el arreglo de dialogos");
                }
            }
        }
    }
}
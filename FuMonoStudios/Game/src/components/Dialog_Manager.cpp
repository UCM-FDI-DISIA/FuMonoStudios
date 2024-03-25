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
void DialogManager::setDialogues(const std::string& filename, std::string charName, std::string typeDialog, std::string typeGeneric) 
{
    //eliminamos los dialogos anteriores
    dialogs_.clear();
    //reseteamos la posicon del indice
    currentDialogIndex_ = 0;

    std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

    // check it was loaded correctly
    // the root must be a JSON object
    if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
        throw "Something went wrong while load/parsing '" + filename + "'";
    }

    // we know the root is JSONObject
    JSONObject root = jValueRoot->AsObject();
    JSONValue* jValue = nullptr;

    jValue = root[charName];
    if (jValue != nullptr && jValue->IsObject())
    {
        JSONObject charObj = jValue->AsObject();
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
                    throw std::runtime_error("Valor inválido en el arreglo de '" + filename + "'");
                }
            }
        }
    }
}

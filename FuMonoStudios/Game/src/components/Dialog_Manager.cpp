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


void DialogManager::nextDialog() {
    if (currentDialogIndex_ < dialogs_.size() - 1) {
        currentDialogIndex_++;
    }
    else {
        currentDialogIndex_ = resetDialogueIndex_;
    }
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
    if (jValue != nullptr) {
      if (jValue->IsArray()) {
        dialogs_.reserve(jValue->AsArray().size());
        for (auto v : jValue->AsArray()) {
          if (v->IsObject()) {
            JSONObject vObj = v->AsObject();
            std::string type = vObj[typeDialog]->AsString();
#ifdef _DEBUG
            std::cout << "Loading dialogo with id: " << type << std::endl;
#endif
            dialogs_.push_back(type);
          }
          else {
            throw "'Dialogs' array in '" + filename
              + "' includes and invalid value";
          }
        }
      }
    }

}

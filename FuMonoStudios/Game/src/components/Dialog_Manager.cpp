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
void DialogManager::setDialogues(const std::string& filename) {
    //eliminamos los dialogos anteriores
    dialogs_.clear();
    //reseteamos la posicon del indice
    currentDialogIndex_ = 0;
    //std::ifstream file(path);
    //if (file.is_open()) { // estamos en 2�. is_open es para beb�s programadores. usad librer�a de carga
    //    //std::string line;
    //    //std::string currentDialog;

    //    //while (std::getline(file, line)) {
    //    //    size_t pos = line.find('$');
    //    //    //si hay contenido
    //    //    if (pos != std::string::npos) {
    //    //        // Agrega el contenido antes del $
    //    //        currentDialog += line.substr(0, pos);
    //    //        // a�adimos el dialogo
    //    //        dialogs_.push_back(currentDialog);
    //    //        currentDialog.clear();
    //    //file.close();
    //}
    //else {
    //    std::cerr << "Error al abrir el archivo: " << path << std::endl;
    //    throw std::runtime_error("No se pudo abrir el archivo de di�logo");
    //}

    std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

    // check it was loaded correctly
    // the root must be a JSON object
    if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
        throw "Something went wrong while load/parsing '" + filename + "'";
    }

    // we know the root is JSONObject
    JSONObject root = jValueRoot->AsObject();
    JSONValue* jValue = nullptr;

    // Iterate over each character/dialog in the JSON
    for (const auto& [character, dialogData] : root) {
        if (dialogData->IsObject()) {
            JSONObject dialogObject = dialogData->AsObject();
            // Iterate over each section of dialog for the character
            for (const auto& [section, dialogs] : dialogObject) {
                // Check if the section contains an array of dialogs
                if (dialogs->IsArray()) {
                    JSONArray dialogArray = dialogs->AsArray();
                    // Add each dialog to the list
                    for (const auto& dialogValue : dialogArray) {
                        if (dialogValue->IsString()) {
                            dialogs_.push_back(dialogValue->AsString());
                        }
                    }
                }
            }
        }
    }


}

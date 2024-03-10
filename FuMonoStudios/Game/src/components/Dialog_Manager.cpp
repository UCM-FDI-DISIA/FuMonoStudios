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
void DialogManager::setDialogues(const std::string& path) {
    //eliminamos los dialogos anteriores
    dialogs_.clear();
    //reseteamos la posicon del indice
    currentDialogIndex_ = 0;
    std::ifstream file(path);
    if (file.is_open()) { // estamos en 2�. is_open es para beb�s programadores. usad librer�a de carga
        std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        JSONValue* jsonValue = JSON::Parse(fileContent.c_str());


        if (jsonValue) {
            // Verificar si es un objeto JSON
            if (jsonValue->IsObject()) {
                const JSONObject& jsonObject = jsonValue->AsObject();

                // Iterar a través de las claves del objeto JSON
                for (auto it = jsonObject.begin(); it != jsonObject.end(); ++it) {
                    const std::string& key = it->first;
                    const JSONValue* value = it->second;

                    // Verificar si el valor asociado a la clave es una cadena
                    if (value->IsString()) {
                        // Agregar el diálogo al vector
                        dialogs_.push_back(value->AsString());
                    }
                }
            }

            // Liberar memoria del objeto JSONValue
            delete jsonValue;
        }
        else {
            std::cerr << "Error al parsear el archivo JSON: " << path << std::endl;
            throw std::runtime_error("No se pudo parsear el archivo JSON");
        }
    }
    else {
        std::cerr << "Error al abrir el archivo: " << path << std::endl;
        throw std::runtime_error("No se pudo abrir el archivo de di�logo");
    }


}

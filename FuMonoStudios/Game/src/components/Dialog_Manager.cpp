// dialog_manager.cpp
#include "dialog_manager.h"
#include <fstream>
#include "../json/JSON.h"

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


void DialogManager::setDialogues(const std::string& path) {
    //eliminamos los dialogos anteriores
    dialogs_.clear();
    //reseteamos la posicon del indice
    currentDialogIndex_ = 0;
    std::ifstream file(path);
    if (file.is_open()) { // estamos en 2�. is_open es para beb�s programadores. usad librer�a de carga
        std::string line;
        std::string currentDialog;

        while (std::getline(file, line)) {
            size_t pos = line.find('$');
            //si hay contenido
            if (pos != std::string::npos) {
                // Agrega el contenido antes del $
                currentDialog += line.substr(0, pos);  
                // a�adimos el dialogo
                dialogs_.push_back(currentDialog);
                currentDialog.clear();
            }
        }

        file.close();
    }
    else {
        std::cerr << "Error al abrir el archivo: " << path << std::endl;
        throw std::runtime_error("No se pudo abrir el archivo de di�logo");
    }


}

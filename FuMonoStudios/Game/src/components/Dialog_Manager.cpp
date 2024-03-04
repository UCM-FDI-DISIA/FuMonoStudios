// dialog_manager.cpp
#include "dialog_manager.h"
#include <fstream>

DialogManager::DialogManager() : currentDialogIndex(0) {
}



std::string DialogManager::GetCurrentDialog() {
    if (currentDialogIndex < dialogs.size()) {
        return dialogs[currentDialogIndex];
    }
    else {
        return ""; // No hay m�s di�logos
    }
}


void DialogManager::NextDialog() {
    if (currentDialogIndex < dialogs.size() - 1) {
        currentDialogIndex++;
    }
}

void DialogManager::setDialogues(std::string path) {
    //eliminamos los dialogos anteriores
    dialogs.clear();
    //reseteamos la posicon del indice
    currentDialogIndex = 0;
    std::ifstream file(path);
    if (file.is_open()) {
        std::string line;
        std::string currentDialog;

        while (std::getline(file, line)) {
            size_t pos = line.find('$');
            //si hay contenido
            if (pos != std::string::npos) {
                // Agrega el contenido antes del $
                currentDialog += line.substr(0, pos);  
                // a�adimos el dialogo
                dialogs.push_back(currentDialog);
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

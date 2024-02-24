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
        return ""; // No hay más diálogos
    }
}


void DialogManager::NextDialog() {
    if (currentDialogIndex < dialogs.size() - 1) {
        currentDialogIndex++;
    }
}

void DialogManager::setDialogues(std::string path) {
    dialogs.clear();
    std::ifstream file(path);
    if (file.is_open()) {
        std::string line;
        std::string currentDialog;

        while (std::getline(file, line)) {
            size_t pos = line.find('$');

            if (pos != std::string::npos) {
                currentDialog += line.substr(0, pos);  // Agrega el contenido antes del $ (Tenemos que buscar el siguiente texto, ahora mismo pilla los espacios de antes del $ también)

                //currentDialog += line.substr(pos + 1) + "\n";  // Agrega el contenido después del $
                dialogs.push_back(currentDialog);
                currentDialog.clear();
            }
            else if(line != "") {
                currentDialog += line + "\n";
            }
        }

        if (!currentDialog.empty()) {
            dialogs.push_back(currentDialog);
        }

        file.close();
    }
    else {
        std::cerr << "Error al abrir el archivo: " << path << std::endl;
        throw std::runtime_error("No se pudo abrir el archivo de diálogo");
    }
}

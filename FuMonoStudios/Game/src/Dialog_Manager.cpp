// dialog_manager.cpp
#include "dialog_manager.h"
#include <fstream>

DialogManager::DialogManager(const std::string& filePath) : currentDialogIndex(0) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        std::string currentDialog;

        while (std::getline(file, line)) {
            size_t pos = line.find('$');

            if (pos != std::string::npos) {
                currentDialog += line.substr(0, pos);  // Agrega el contenido antes del $
                dialogs.push_back(currentDialog);
                currentDialog.clear();

                currentDialog += line.substr(pos + 1) + "\n";  // Agrega el contenido después del $
            }
            else {
                currentDialog += line + "\n";
            }
        }

        if (!currentDialog.empty()) {
            dialogs.push_back(currentDialog);
        }

        file.close();
    }
    else {
        std::cerr << "Error al abrir el archivo: " << filePath << std::endl;
        throw std::runtime_error("No se pudo abrir el archivo de diálogo");
    }
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

// dialog_manager.cpp
#include "dialog_manager.h"
#include <fstream>
#include "../json/JSON.h"

DialogManager::DialogManager() : currentDialogIndex(0) {
}



std::string DialogManager::GetCurrentDialog() {
    if (currentDialogIndex < dialogs.size()) {
        return dialogs[currentDialogIndex];
    }
    else {
        return ""; // No hay m�s di�logos. cleon: ultramegamaxi MAL
    }
}


void DialogManager::NextDialog() {
    if (currentDialogIndex < dialogs.size() - 1) {
        currentDialogIndex++;
    }
    else {
        currentDialogIndex = resetDialogueIndex;
    }
}
// un string sin referencia es como un d�a sin sol: const string&
void DialogManager::setDialogues(const std::string& path) {
    //eliminamos los dialogos anteriores
    dialogs.clear();
    //reseteamos la posicon del indice
    currentDialogIndex = 0;
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

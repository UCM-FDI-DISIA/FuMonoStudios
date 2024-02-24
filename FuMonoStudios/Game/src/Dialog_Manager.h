// dialog_manager.h
#ifndef DIALOG_MANAGER_H
#define DIALOG_MANAGER_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class DialogManager {
public:
    DialogManager();

    // Obtener el texto del diálogo actual
    std::string GetCurrentDialog();

    // Cambiar al siguiente cuadro de diálogo
    void NextDialog();

    void setDialogues(std::string path);

private:
    std::vector<std::string> dialogs;
    size_t currentDialogIndex;
};

#endif // DIALOG_MANAGER_H

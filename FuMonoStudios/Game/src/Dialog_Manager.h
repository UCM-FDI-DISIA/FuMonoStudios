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

    /// <summary>
    /// Devuelve el dialogo acutal segun el indice de dialogo
    /// </summary>
    /// <returns></returns>
    std::string GetCurrentDialog();

    /// <summary>
    /// Avanza al siguente dialogo. 
    /// Si ya está en el ultimo diálogo no avanza y se queda en ese
    /// </summary>
    void NextDialog();
    /// <summary>
    /// Toma una ruta del fichero de donde actualizar el vector de diálogos
    /// Vacia el vector de dialogos anterior y resetea el indice de dialogos
    /// </summary>
    /// <param name="path"></param>
    void setDialogues(std::string path);

private:
    /// <summary>
    /// Vector donde se almacenan todos los diálogos que se van a soltar
    /// </summary>
    std::vector<std::string> dialogs;
    /// <summary>
    /// Indice que indica en que diálogo nos encontramos
    /// </summary>
    size_t currentDialogIndex;
};

#endif // DIALOG_MANAGER_H

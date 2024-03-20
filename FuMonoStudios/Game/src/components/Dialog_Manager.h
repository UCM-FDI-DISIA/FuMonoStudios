// dialog_manager.h
#ifndef DIALOG_MANAGER_H
#define DIALOG_MANAGER_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;
/*
Clase que genera los dialogos que se van a escribir
Carga los dialogos de un fichero te texto que tenemos codificado
*/
class DialogManager {
public:
    DialogManager();

    /// <summary>
    /// Devuelve el dialogo acutal segun el indice de dialogo
    /// </summary>
    /// <returns></returns>
    std::string getCurrentDialog();

    /// <summary>
    /// Avanza al siguente dialogo. 
    /// Si ya est� en el ultimo di�logo devuelve false y resetea
    /// el index a 0
    /// </summary>
    bool nextDialog();
    /// <summary>
    /// Toma una ruta del fichero de donde actualizar el vector de di�logos
    /// Vacia el vector de dialogos anterior y resetea el indice de dialogos
    /// </summary>
    /// <param name="path"></param>
    void setDialogues(const std::string& path);

private:
    /// <summary>
    /// Vector donde se almacenan todos los di�logos que se van a soltar
    /// </summary>
    std::vector<std::string> dialogs_;
    /// <summary>
    /// Indice que indica en que di�logo nos encontramos
    /// </summary>
    size_t currentDialogIndex_;
};

#endif // DIALOG_MANAGER_H

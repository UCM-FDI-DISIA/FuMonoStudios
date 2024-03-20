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
    /// enum con todos los NPCs
    /// </summary>
    enum Personaje { Campesino, Secretario, Vagabundo, Artesano, Tarotisa, Soldado, Contable };
    /// <summary>
    /// enum con todos los tipos de dialogos
    /// </summary>
    enum TipoDialog { Presentacion, FelMinimo, FelMaximo, Genericos, Eventos };
    /// <summary>
    /// enum con todos los tipos de dialogos genericos
    /// </summary>
    enum TipoGenerico { Alimento, Medicinas, Joyas, Materiales, Armamento };

    /// <summary>
    /// Devuelve el dialogo acutal segun el indice de dialogo
    /// </summary>
    /// <returns></returns>
    std::string getCurrentDialog();

    /// <summary>
    /// Avanza al siguente dialogo. 
    /// Si ya está en el ultimo diálogo devuelve false y resetea
    /// el index a 0
    /// </summary>
    bool nextDialog();
    /// <summary>
    /// Toma una ruta del fichero de donde actualizar el vector de diálogos
    /// Vacia el vector de dialogos anterior y resetea el indice de dialogos
    /// </summary>
    /// <param name="path"></param>
    void setDialogues(const std::string& filename, std::string charName, std::string typeDialog, std::string typeGeneric);

private:
    /// <summary>
    /// Vector donde se almacenan todos los diálogos que se van a soltar
    /// </summary>
    std::vector<std::string> dialogs_;
    /// <summary>
    /// Indice que indica en que diálogo nos encontramos
    /// </summary>
    size_t currentDialogIndex_;
};

#endif // DIALOG_MANAGER_H

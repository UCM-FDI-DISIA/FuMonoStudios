// dialog_manager.h
#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "../architecture/GeneralData.h"

/*
Clase que genera los dialogos que se van a escribir
Carga los dialogos de un fichero te texto que tenemos codificado

PARA LOS TIPOS DE DIALOGOS: Presentacion, FelMinimo, FelMaximo,
GenericosMalo, GenericosNormal, GenericosBueno,
Eventos, NPCgrande, NPCgrandePostConversacion, NOTYPE
Los tipos de Presentación, felicidad, genericos y eventos están dedicados a NPCmenores,
mientras que los de NPCgrande para los grandes. El NOTYPE se usa para cosas interactuables
del entorno que usen solo un diálogo.
*/
class DialogManager {
public:
    DialogManager();

    /* COMENTADO POR DEPENDENCIA CIRCULAR DE ENUMS (CRAZY)
    /// <summary>
    /// enum con todos los tipos de dialogos
    /// Los tipos de Presentación, felicidad, genericos y eventos están dedicados a NPCmenores,
    /// mientras que los de NPCgrande para los grandes. El NOTYPE se usa para cosas interactuables
    /// del entorno que usen solo un diálogo.
    /// </summary>
    enum TipoDialog {
        Presentacion, FelMinimo, FelMaximo,
        GenericosMalo, GenericosNormal, GenericosBueno,
        Eventos, NPCgrande, NPCgrandePostConversacion, NOTYPE
    };*/

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
    
    // Establece los dialogos del personaje introducido, y busca dentro de su
    // seccion en el json el tipoDialogo, mas el numero introducido en el 
    // dialogueSelection. Poner un -1 para no usar el numero de dialogueSelection
    void setDialogues(const GeneralData::Personaje pers, const std::string& tipoDialogo, int dialogueSelection);
    void setDialogues(const GeneralData::Personaje a, const std::string& t) { setDialogues(a, t, -1); }
private:
    std::string crearTildes(std::string aux);
    /// <summary>
    /// Vector donde se almacenan todos los diálogos que se van a soltar
    /// </summary>
    std::vector<std::string> dialogs_;
    /// <summary>
    /// Indice que indica en que diálogo nos encontramos
    /// </summary>
    size_t currentDialogIndex_;
};
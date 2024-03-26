// dialog_manager.h
#ifndef DIALOG_MANAGER_H
#define DIALOG_MANAGER_H

#include <string>
#include <vector>
#include <iostream>
/*
Clase que genera los dialogos que se van a escribir
Carga los dialogos de un fichero te texto que tenemos codificado
*/
class DialogManager {
public:
    DialogManager();

    /// <summary>
    /// enum con todos los nombres de cosas interactuables
    /// </summary>
    enum Personaje { Vagabundo, Secretario, Campesino, Artesano, Tarotisa, Soldado, Contable,
        JefeOficina };
    /// <summary>
    /// enum con todos los tipos de dialogos
    /// Los tipos de Presentación, felicidad, genericos y eventos están dedicados a NPCmenores,
    /// mientras que los de NPCgrande para los grandes. El NOTYPE se usa para cosas interactuables
    /// del entorno que usen solo un diálogo.
    /// </summary>
    enum TipoDialog { Presentacion, FelMinimo, FelMaximo, 
        GenericosMalo, GenericosNormal, GenericosBueno, 
        Eventos, NPCgrande, NPCgrandePostConversacion, NOTYPE };

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
    void setDialogues(const Personaje pers, const TipoDialog tipoDialogo, int dialogueSelection);
    void setDialogues(const Personaje a, const TipoDialog t) { setDialogues(a, t, -1); }

    // convierte Personaje a string
    const std::string personajeToString(const Personaje pers);
    // convierte TipoDialog a string y añade el indice de dialogo en caso de usarlo
    const std::string tipoDialogToString(const TipoDialog tipo, int dialogueSelection);
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

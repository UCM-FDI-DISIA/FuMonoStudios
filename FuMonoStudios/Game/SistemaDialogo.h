#ifndef SISTEMADIALOGO_H
#define SISTEMADIALOGO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct DialogoNode {
  std::string texto;
  std::vector<DialogoNode*> respuestas;

  DialogoNode(const std::string& texto) : texto(texto) {}
  ~DialogoNode() {
    for (DialogoNode* respuesta : respuestas) {
      delete respuesta;
    }
  }
};

class SistemaDialogos {
public:
  SistemaDialogos(const std::string& archivo);
  ~SistemaDialogos();

  void IniciarDialogo();

private:
  DialogoNode* raizActual;
  std::vector<DialogoNode*> nodos;

  DialogoNode* ConstruirArbolDesdeArchivo(const std::string& archivo);
};

#endif // SISTEMADIALOGO_H

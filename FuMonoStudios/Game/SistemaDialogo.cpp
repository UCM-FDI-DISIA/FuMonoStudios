#include "SistemaDialogo.h"


SistemaDialogos::SistemaDialogos(const std::string& archivo) {
  raizActual = ConstruirArbolDesdeArchivo(archivo);
}

SistemaDialogos::~SistemaDialogos() {
  delete raizActual;
}

DialogoNode* SistemaDialogos::ConstruirArbolDesdeArchivo(const std::string& archivo) {
  std::ifstream file(archivo);
  if (!file.is_open()) {
    std::cerr << "Error al abrir el archivo: " << archivo << std::endl;
    exit(1);
  }

  std::vector<DialogoNode*> nodosTemp;
  std::string linea;
  while (std::getline(file, linea)) {
    nodosTemp.push_back(new DialogoNode(linea));
  }

  for (size_t i = 0; i < nodosTemp.size(); ++i) {
    size_t respuestaIndex;
    file >> respuestaIndex;

    if (respuestaIndex != 0) {
      nodosTemp[i]->respuestas.push_back(nodosTemp[respuestaIndex - 1]);
    }
  }

  file.close();
  return nodosTemp[0];
}

void SistemaDialogos::IniciarDialogo() {
  DialogoNode* nodoActual = raizActual;
  while (nodoActual != nullptr) {
    std::cout << nodoActual->texto << std::endl;

    if (!nodoActual->respuestas.empty()) {
      std::cout << "Presiona Enter para continuar..." << std::endl;
      std::cin.ignore(); // Espera hasta que el usuario presione Enter
      nodoActual = nodoActual->respuestas[0];
    }
    else {
      std::cout << "Fin del diálogo." << std::endl;
      nodoActual = nullptr;
    }
  }
}


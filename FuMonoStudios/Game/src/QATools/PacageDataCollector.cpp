#include "PacageDataCollector.h"


std::ofstream& PacageDataCollector::operator<<(Paquete& pacage)
{
    //hay que mejorar y decidir que datos meter
    dataFile << "Distrito: "<<pacage.getDistrito() << "Calle: " <<pacage.getCalle() << SEPARATOR
        <<pacage.getTipo() << SEPARATOR
        <<pacage.getPeso()
        << "\n";
    // TODO: Insertar una instrucción "return" aquí
    return dataFile;
}

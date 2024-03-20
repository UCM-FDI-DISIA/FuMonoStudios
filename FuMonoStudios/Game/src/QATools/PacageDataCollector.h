#pragma once
#include "DataCollector.h"
#include <components/Paquete.h>
class PacageDataCollector :
    public DataCollector
{
public:
    PacageDataCollector() :DataCollector("QAdata/pacages.csv"),nextVoidRow(0) {
        doc.Clear();
        dataFile << "Direccion" << SEPARATOR << "Tipo de Sello" << SEPARATOR << "Tipo de Peso" << "\n";
    }
    ~PacageDataCollector() {};

    void writePacageData(Paquete&);

private:
    int nextVoidRow;
};


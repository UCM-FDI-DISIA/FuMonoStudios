#pragma once
#include "DataCollector.h"
#include <components/Paquete.h>
class PacageDataCollector :
    public DataCollector
{
public:
    PacageDataCollector() :DataCollector() {
        dataFile.open("QAdata/pacages.csv",std::ios::app);
        dataFile << "Direccion" << SEPARATOR << "Tipo de Sello" << SEPARATOR << "Tipo de Peso" << "\n";
    }
    ~PacageDataCollector() {};

    //cambiar mas adelante para que pueda ser const
    virtual std::ofstream& operator<<(Paquete&);

};


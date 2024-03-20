#pragma once
#include "DataCollector.h"
#include <components/Paquete.h>
class PacageDataCollector :
    public DataCollector
{
public:
    PacageDataCollector() :DataCollector("QAdata/pacages.csv"),nextVoidRow(0) {
        doc.Clear();
        doc.SetColumnName(0, "Distrito");
        doc.SetColumnName(1, "Calle");
        doc.SetColumnName(2, "Peso");
        doc.SetColumnName(3, "Fragil");

    }
    ~PacageDataCollector() {};

    void writePacageData(const Paquete&);

private:
    int nextVoidRow;
};


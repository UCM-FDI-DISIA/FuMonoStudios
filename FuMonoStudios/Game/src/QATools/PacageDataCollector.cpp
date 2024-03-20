#include "PacageDataCollector.h"


void PacageDataCollector::writePacageData(Paquete& pacage) {
	doc.SetCell(0, nextVoidRow, (int) pacage.getDistrito()+1);
	doc.SetCell(1, nextVoidRow, (int) pacage.getCalle()+1);
	doc.SetCell(2, nextVoidRow, (int) pacage.getPeso());
	doc.SetCell(3, nextVoidRow, (int) pacage.getFragil());
	nextVoidRow++;
}

#include "GeneralData.h"

void GeneralData::updateMoney(int writePacages, int wrongPacages)
{
	//funcion de ejemplo seguramente haya que cambiarlo
	if (wrongPacages < 0) {
		wrongPacages = 0;
	}
	if (writePacages < 0) {
		writePacages = 0;
	}
	dinero_ += writePacages * WRITE_PACAGES_VALUE - wrongPacages * WRONG_PACAGES_VALUE;
}

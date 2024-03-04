#include "GeneralData.h"

void GeneralData::updateMoney()
{
	//funcion de ejemplo seguramente haya que cambiarlo
	if (wrongPacages < 0) {
		wrongPacages = 0;
	}
	if (rightPacages < 0) {
		rightPacages = 0;
	}
	//Aquí se escribiría algo como "En este tiempo de trabajo, has conseguido x paquetes correctos y x paquetes incorrectos"
	dinero_ += rightPacages * WRITE_PACAGES_VALUE - wrongPacages * WRONG_PACAGES_VALUE;
	resetRightWrong();
}

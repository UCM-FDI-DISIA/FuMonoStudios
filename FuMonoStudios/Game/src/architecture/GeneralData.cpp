#include "GeneralData.h"
#include <iostream>
#include <string>

void GeneralData::updateMoney(int correct, int wrong)
{
	int rightPackages = correct;
	corrects_ = correct;
	int wrongPackages = wrong;
	fails_ = wrong;
	//funcion de ejemplo seguramente haya que cambiarlo
	if (wrong < failsMargin_) {
		wrongPackages = 0;
	}
	if (correct < 0) {
		rightPackages = 0;
	}
	dinero_ += rightPackages * WRITE_PACAGES_VALUE - wrongPackages * WRONG_PACAGES_VALUE;
}

//A medida que el proyecto avance, la lista de variables deber� de ampliarse, pero por ahora tenemos esto:

void GeneralData::setFinalID(int final) {
	finalID_ = final;
	std::cout << "El ID del final del juego es: " << finalID_ << std::endl;
}

int GeneralData::getFinalID() {
	std::cout << "El ID del final del juego que quieres obtener es: " << finalID_ << std::endl;
	return finalID_;
}

void GeneralData::setEventoID(int evento) {
	eventoID_ = evento;
	std::cout << "El ID del evento es: " << eventoID_ << std::endl;
}

int GeneralData::getEventoID() {
	std::cout << "El ID del evento que quieres obtener es: " << eventoID_ << std::endl;
	return eventoID_;
}

int GeneralData::getPaqueteLevel() {
	//Aqui habra que decidir el paquete level en funci�n del d�a
	return paqueteLvl_;
}

void GeneralData::changeParamID(int i, bool suma) {
	if (suma) {
		paramAjustes_[i] += 10;
		if (paramAjustes_[i] >= 100) {
			paramAjustes_[i] = 100;
		}
	}
	else {
		paramAjustes_[i] -= 10;
		if (paramAjustes_[i] <= 0) {
			paramAjustes_[i] = 0;
		}
	}

	std::cout << "El valor del parametro ahora es: " << paramAjustes_[i] << std::endl;
}
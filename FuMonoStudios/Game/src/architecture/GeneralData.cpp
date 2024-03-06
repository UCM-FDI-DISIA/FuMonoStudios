#include "GeneralData.h"
#include <iostream>
#include <string>

void GeneralData::updateMoney()
{
	int rightPackages = corrects;
	int wrongPackages = fails;
	//funcion de ejemplo seguramente haya que cambiarlo
	if (fails < failsMargin_) {
		wrongPackages = 0;
	}
	if (corrects < 0) {
		rightPackages = 0;
	}
	dinero_ += rightPackages * WRITE_PACAGES_VALUE - wrongPackages * WRONG_PACAGES_VALUE;
}

//A medida que el proyecto avance, la lista de variables deberá de ampliarse, pero por ahora tenemos esto:

void GeneralData::SetFinalID(int final) {
	finalID_ = final;
	std::cout << "El ID del final del juego es: " << finalID_ << std::endl;
}

int GeneralData::GetFinalID() {
	std::cout << "El ID del final del juego que quieres obtener es: " << finalID_ << std::endl;
	return finalID_;
}

void GeneralData::SetEventoID(int evento) {
	eventoID_ = evento;
	std::cout << "El ID del evento es: " << eventoID_ << std::endl;
}

int GeneralData::GetEventoID() {
	std::cout << "El ID del evento que quieres obtener es: " << eventoID_ << std::endl;
	return eventoID_;
}

int GeneralData::getPaqueteLevel() {
	//Aqui habra que decidir el paquete level en función del día
	return paqueteLvl;
}

#include "GeneralData.h"
#include <iostream>
#include <string>

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

void GeneralData::SetDiaID(int dia) {
	diaID_ = dia;
	std::cout << "El ID del dia es: " << diaID_ << std::endl;
}

int GeneralData::GetDiaID() {
	std::cout << "El ID del dia en el que estas es: " << diaID_ << std::endl;
	return diaID_;
}

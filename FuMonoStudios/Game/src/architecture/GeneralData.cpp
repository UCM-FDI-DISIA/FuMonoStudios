#include "GeneralData.h"
#include <iostream>
#include <string>

GeneralData::GeneralData()
{
	// Esto habra que cargarlo desde un archivo de guardado
	dinero_ = INITIAL_MONEY;
	finalID_ = INITIAL_FINAL;
	eventoID_ = INITIAL_EVENT; 
	failsMargin_ = INITIAL_FAILS_MARGIN;
	corrects_ = 0;
	fails_ = 0;
	dia_ = 1;
	numTubos_ = INITIAL_TUBE_AMOUNT;

	readNPCData();
}

GeneralData::~GeneralData() {

}


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

void GeneralData::setPaqueteLevel(int lvl) {
	paqueteLvl_ = lvl;
}

void GeneralData::readNPCData() {

}

void GeneralData::writeNPCData() {

}

// Struct NPCdata
#pragma region NPCdata
// NPC MENOR
NPCMenorData::NPCMenorData(Felicidad Felicidad, std::vector<bool> DiasDanEvento) {
	felicidad = Felicidad;
	iteration = 1;
	diasDanEvento = DiasDanEvento;
}

std::pair<DialogManager::TipoDialog, int> NPCMenorData::getDialogueInfo() {
	
	DialogManager::TipoDialog tipo;
	int iterationNum = -1;

	if (felicidad == Minima || felicidad == Maxima)
	{
		tipo = felicidad == Minima ? DialogManager::FelMinimo : DialogManager::FelMaximo;
	}
	else if (giveEvent)
	{
		tipo = DialogManager::Eventos;
	}
	else
	{
		switch (felicidad){
			case Mala:
				tipo = DialogManager::GenericosMalo;
				iterateDialogue();
				iterationNum = iteration;
				break;
			case Normal:
				tipo = DialogManager::GenericosNormal;
				iterateDialogue();
				iterationNum = iteration;
				break;
			case Buena:
				tipo = DialogManager::GenericosBueno;
				iterateDialogue();
				iterationNum = iteration;
				break;
			case NoHabladoAun:
				tipo = DialogManager::Presentacion;
				felicidad = Normal;
				break;
		}
	}
	return std::make_pair(tipo, iterationNum);
}

void NPCMenorData::setupDayData() {
	iteration = 1;
	giveEvent = diasDanEvento[generalData().getDia() - 1];
}

void NPCMenorData::iterateDialogue() {
	iteration++;
	if (iteration > 3)
		iteration = 1;
}

void NPCMenorData::activateEvent(){
	giveEvent = true;
}

void NPCMenorData::deactivateEvent() {
	giveEvent = false;
}

// NPC GRANDE

NPCMayorData::NPCMayorData(Felicidad Felicidad) {
	felicidad = Felicidad;
	postConversation = false;
}

std::pair<DialogManager::TipoDialog, int> NPCMayorData::getDialogueInfo() {
	DialogManager::TipoDialog tipo;

	switch (felicidad)
	{
		case NoHabladoAun:
			tipo = DialogManager::Presentacion;
			felicidad = Normal;
			break;
		case Minima:
			tipo = DialogManager::FelMinimo;
			break;
		default:
			tipo = postConversation ?
				DialogManager::NPCgrandePostConversacion : DialogManager::NPCgrande;
			postConversation = true;
			break;
	}

	return std::make_pair(tipo, -1);
}

void NPCMayorData::setupDayData() {
	postConversation = false;
}
#pragma endregion
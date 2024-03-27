#include "../components/DialogManager.h"
#include "GeneralData.h"
#include <iostream>
#include <string>
#include <fstream>
#include "../json/JSON.h"
#include "../json/JSONValue.h"

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
	std::unique_ptr<JSONValue> jsonFile(JSON::ParseFromFile("recursos/dialogos/npcData.json"));

	if (jsonFile == nullptr || !jsonFile->IsObject()) {
		throw "Something went wrong while load/parsing npcData";
	}
	
	JSONObject root = jsonFile->AsObject();
	JSONValue* jValue = nullptr;

	// cargamos los 7 personajes

	for (int i = 0; i < 7; i++)
	{
		jValue = root[personajeToString((Personaje)i)];

		JSONObject jObject = jValue->AsObject();
		JSONValue felicidadStr = jObject["Felicidad"];

		if (i < 2) // npc grandes
		{
			npcData.push_back(new NPCMayorData(stringToFelicidad(felicidadStr.AsString())));
		}
		else
		{
			std::vector<bool> diasDanEventos;
			jValue = root["DiasConEvento"];
			jObject = jValue->AsObject();

			// leemos los 14 booleanos
			for (int i = 0; i < 14; i++)
			{
				diasDanEventos.push_back(jObject[std::to_string(i)]);
			}
			npcData.push_back(new NPCMenorData(stringToFelicidad(felicidadStr.AsString()),diasDanEventos));
		}
		
	}
	
}

void GeneralData::writeNPCData() {

}

const std::string GeneralData::personajeToString(Personaje pers) {

	std::string aux = "";
	switch (pers) {
		case Vagabundo:
			aux = "Vagabundo";
			break;
		case Secretario:
			aux = "Secretario";
			break;
		case Campesino:
			aux = "Campesino";
			break;
		case Artesano:
			aux = "Artesano";
			break;
		case Tarotisa:
			aux = "Tarotisa";
			break;
		case Soldado:
			aux = "Soldado";
			break;
		case Contable:
			aux = "Contable";
			break;
		case JefeOficina:
			aux = "JefeOficina";
			break;
	}
	return aux;
}

GeneralData::Personaje GeneralData::stringToPersonaje(const std::string& pers) {
	Personaje aux;
	// no deja hacer switch y es una cochinada pero es la unica forma de hacerlo
	if (pers == "Vagabundo")
		aux = Vagabundo;
	else if (pers == "Secretario")
		aux = Secretario;
	else if (pers == "Campesino")
		aux = Campesino;
	else if (pers == "Artesano")
		aux = Artesano;
	else if (pers == "Tarotisa")
		aux = Tarotisa;
	else if (pers == "Soldado")
		aux = Soldado;
	else if (pers == "Contable")
		aux = Contable;
	
	return aux;
}

GeneralData::Felicidad GeneralData::stringToFelicidad(const std::string& str)
{
	Felicidad aux;
	if (str == "Minima")
		aux = Felicidad::Minima;
	else if (str == "Mala")
		aux = Felicidad::Mala;
	else if (str == "Normal")
		aux = Felicidad::Normal;
	else if (str == "Buena")
		aux = Felicidad::Buena;
	else if (str == "Maxima")
		aux = Felicidad::Maxima;
	else if (str == "NoHabladoAun")
		aux = Felicidad::NoHabladoAun;

	return aux;
}

// Struct NPCdata
#pragma region NPCdata

GeneralData::NPCdata* GeneralData::getNPCData(Personaje personaje) {
	NPCdata* npc = nullptr;

	npc = npcData[personaje];

	return npc;
}

// NPC MENOR
GeneralData::NPCMenorData::NPCMenorData(Felicidad Felicidad, std::vector<bool> DiasDanEvento) {
	felicidad = Felicidad;
	iteration = 1;
	diasDanEvento = DiasDanEvento;
}

std::pair<DialogManager::TipoDialog, int> GeneralData::NPCMenorData::getDialogueInfo() {
	
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

void GeneralData::NPCMenorData::setupDayData() {
	iteration = 1;
	giveEvent = diasDanEvento[generalData().getDia() - 1];
}

void GeneralData::NPCMenorData::iterateDialogue() {
	iteration++;
	if (iteration > 3)
		iteration = 1;
}

void GeneralData::NPCMenorData::activateEvent(){
	giveEvent = true;
}

void GeneralData::NPCMenorData::deactivateEvent() {
	giveEvent = false;
}

// NPC GRANDE

GeneralData::NPCMayorData::NPCMayorData(Felicidad Felicidad) {
	felicidad = Felicidad;
	postConversation = false;
}

std::pair<DialogManager::TipoDialog, int> GeneralData::NPCMayorData::getDialogueInfo() {
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

void GeneralData::NPCMayorData::setupDayData() {
	postConversation = false;
}
#pragma endregion
#ifndef DEV_TOOLS
#include <utils/checkML.h>
#endif // !DEV_TOOLS
#include "GeneralData.h"
#include <sistemas/SoundEmiter.h>
#include <sistemas/PaqueteBuilder.h>
#include <architecture/Game.h>
#include <sistemas/NPCeventSystem.h>
#include <architecture/GameConstants.h>
#include <iostream>

GeneralData::GeneralData()
{
	setNewGameValues();

	loadPersistentData();
#ifdef _DEBUG
	std::cout << "Tamanyo vector de mejoras: " << upgrades_.size() << std::endl;
#endif // _DEBUG
#ifdef _DEBUG
	std::cout << "Volumen SFX: " << paramVolSfx_ << std::endl;
#endif // _DEBUG
	soundEmiter().setMusicVolume(paramVolMusic_);
	soundEmiter().setSoundVolumes(paramVolSfx_);
	//readNPCData();
}

GeneralData::~GeneralData() {
	savePersistentData();
	for (auto& npc : npcData) {
		delete npc.second;
		npc.second = nullptr;
	}
	for (auto obj : intObjData) {
		delete obj;
	}
	for (auto package : paquetesNPCs) {
		delete package;
	}
	delete npcEventSys;
}

void GeneralData::loadSaveFile()
{
	std::ifstream in;
	in.open(SAVE_PATH);
	if (in.is_open()) {
		in.close();

		/*if (!npcData.empty())
			npcData.clear();*/

		std::unique_ptr<JSONValue> jsonFile(JSON::ParseFromFile(SAVE_PATH));

		JSONObject root = jsonFile->AsObject();

		dia_ = root["Dia"]->AsNumber();
		dinero_ = root["Dinero"]->AsNumber();

		JSONObject saveFileRoot = jsonFile->AsObject();
		JSONObject personajesRoot = saveFileRoot["Personajes"]->AsObject();
		loadNPCsData(personajesRoot);
	}
	else {
		throw save_Missing("error al cargar los datos del fichero de guardado");
	}
}

void GeneralData::newGame()
{
	setNewGameValues();
	for (auto npcDataVal : npcData) {
		npcDataVal.second->reset();
	}
}

void GeneralData::setNewGameValues()
{
	numTubos_ = INITIAL_TUBE_AMOUNT;

	dinero_ = INITIAL_MONEY;
	finalID_ = INITIAL_FINAL;
	failsMargin_ = INITIAL_FAILS_MARGIN;
	corrects_ = 0;
	fails_ = 0;
	dia_ = INITIAL_DAY;
	rent_ = RENT_VALUE;
	//reset de las mejoras
	upgrades_.reset();
}

void GeneralData::updateMoney()
{
	int rightPackages = corrects_;
	int wrongPackages = fails_;
	//funcion de ejemplo seguramente haya que cambiarlo
	if (fails_ < failsMargin_) {
		wrongPackages = 0;
	}
	if (corrects_ < 0) {
		rightPackages = 0;
	}

	dinero_ += calcularDineroGanado() - rent_;
}

int GeneralData::calcularDineroGanado()
{
	int rightPackages = corrects_;
	int wrongPackages = fails_;
	int totalRightMoney = 0;

	if (upgrades_[ecs::upg::MONEY_UPGRADE]) {
		totalRightMoney = rightPackages * (WRITE_PACAGES_VALUE + CONTABLE_PLUS_MONEY);
	}
	else {
		totalRightMoney = rightPackages * WRITE_PACAGES_VALUE;
	}

	if (GeneralData::instance()->getUpgradeValue(ecs::upg::FALLOS_UPGRADE)) failsMargin_ = SOLDIER_NUM_FAIL;
	else failsMargin_ = 0;

	if (fails_ < failsMargin_) {
		wrongPackages = 0;
	}
	else {
		wrongPackages -= failsMargin_;
	}

	return 		totalRightMoney - (wrongPackages * WRONG_PACAGES_VALUE);
}

void GeneralData::resetMoney()
{
	dinero_ = INITIAL_MONEY;
}

//A medida que el proyecto avance, la lista de variables deber� de ampliarse, pero por ahora tenemos esto:

void GeneralData::setFinalID(int final) {
	finalID_ = final;
#ifdef _DEBUG
	std::cout << "El ID del final del juego es: " << finalID_ << std::endl;
#endif // _DEBUG

}

int GeneralData::getFinalID() {
#ifdef _DEBUG
	std::cout << "El ID del final del juego que quieres obtener es: " << finalID_ << std::endl;
#endif // _DEBUG
	return finalID_;
}

void GeneralData::setRent(int rent) {
	rent_ = rent;
#ifdef _DEBUG
	std::cout << "el nuevo alquiler es: " << rent_ << std::endl;
#endif // _DEBUG
}


int GeneralData::getRent() {

	return rent_;

}

void GeneralData::updateDia()
{
	placesToActive_.clear();
	updateDistrictsPerDay(dia_);
	// actualizar los datos para todos los npc
	for (auto it : npcData)
	{
		it.second->setupDayData();
	}

	if (dia_ == 1) {
		dinero_ = INITIAL_MONEY;
	}
}

std::string GeneralData::fromDistritoToString(int i) {

	std::string sol;

	switch (i) {
	case Distrito::Hestia:
		sol = "Hestia";
		break;
	case Distrito::Artemisa:
		sol = "Artemisa";
		break;
	case Distrito::Demeter:
		sol = "Demeter";
		break;
	case Distrito::Hefesto:
		sol = "Hefesto";
		break;
	case Distrito::Hermes:
		sol = "Hermes";
		break;
	case Distrito::Apolo:
		sol = "Apolo";
		break;
	case Distrito::Poseidon:
		sol = "Poseidon";
		break;
	default:
		sol = "Erroneo";
		break;
	}

	return sol;

}

int GeneralData::fromStringToDistrito(std::string place) {

	int sol;

	if (place == "Hestia") {

		return Distrito::Hestia;

	}
	else if (place == "Artemisa") {

		return Distrito::Artemisa;

	}
	else if (place == "Demeter") {

		return Distrito::Demeter;

	}
	else if (place == "Hefesto") {

		return Distrito::Hefesto;

	}
	else if (place == "Hermes") {

		return Distrito::Hermes;

	}
	else if (place == "Apolo") {

		return Distrito::Apolo;

	}
	else if (place == "Poseidon") {

		return Distrito::Poseidon;

	}
	else {

		return Distrito::Erroneo;

	}

}

void GeneralData::updateDistrictsPerDay(int dia)
{
	if (dia == 0)
		return;
	switch (dia)
	{
	case 1:
		//tutorial
		placesToActive_.push_back("Hestia");
		placesToActive_.push_back("Hefesto");
		placesToActive_.push_back("Demeter");
		placesToActive_.push_back("Artemisa");
		break;
	case 5:
		placesToActive_.push_back("Hermes");
		placesToActive_.push_back("Apolo");
		placesToActive_.push_back("Poseidon");
		break;
	default:
		break;
	}
	updateDistrictsPerDay(dia - 1);
}

void GeneralData::saveNPCData(JSONObject& obj)
{
	JSONObject characters;
	for (auto npc : npcData) {
		JSONObject charac;
		modifyJsonData(charac, "Felicidad", gD().felicidadToString(npc.second->felicidad));
		modifyJsonData(charac, "FelicidadNum", npc.second->numFelicidad);
		modifyJsonData(charac, "numMisionesAceptadas", npc.second->numMisionesAceptadas);
		modifyJsonData(charac, "unlockUpgrade", npc.second->unlockUpgrade);
		//Procesado de eventos completados
		auto& completedEvents = npc.second->eventosCompletados;
		JSONArray arrayEvents;
		for (auto evt : completedEvents) {
			arrayEvents.push_back(new JSONValue(evt.first ? evt.second : -evt.second));
		}
		modifyJsonData(charac, "EventosCompletados",arrayEvents);
		modifyJsonData(characters, personajeToString(npc.first), charac);
	}
	modifyJsonData(obj, "Personajes", characters);

}

void GeneralData::loadNPCsData(JSONObject& charRoot)
{
	for (int i = Vagabundo; i < Jefe; i++) {
		JSONObject charObj = charRoot[personajeToString((Personaje)i)]->AsObject();
		npcData[(Personaje)i]->loadDataFromSaveFile(charObj);
	}
}

void GeneralData::savePersistentData()
{
	std::ofstream in;
	//en el caso de que no exista el fichero se crea uno nuevo
	in.open("recursos/config/persistentData.json");

	JSONObject root;

	//modificacion de los valores en el json
	modifyJsonData(root, "musicVal", paramVolMusic_);
	modifyJsonData(root, "sfxVal", paramVolSfx_);
	modifyJsonData(root, "skipTutorial", skipTutorial_);
	modifyJsonData(root, "fullScreenEnable", fullScreen_);
	modifyJsonData(root, "gameEnded", gameEndedOnce_);

	JSONValue* jsonFile = new JSONValue(root);
	in << jsonFile->Stringify(true);
	delete jsonFile;
	in.close();
}

void GeneralData::loadPersistentData()
{
	std::unique_ptr<JSONValue> jsonPersistentData(JSON::ParseFromFile(PERSISTENT_DATA_PATH));

	if (jsonPersistentData == nullptr || !jsonPersistentData->IsObject()) {
		throw config_File_Missing(PERSISTENT_DATA_PATH);
	}

	JSONObject dataRoot = jsonPersistentData->AsObject();

	paramVolMusic_ = dataRoot["musicVal"]->AsNumber();
	paramVolSfx_ = dataRoot["sfxVal"]->AsNumber();
	skipTutorial_ = dataRoot["skipTutorial"]->AsBool();
	fullScreen_ = dataRoot["fullScreenEnable"]->AsBool();
	gameEndedOnce_ = dataRoot["gameEnded"]->AsBool();
}

int GeneralData::getPaqueteLevel() {
	//Aqui habra que decidir el paquete level en funci�n del d�a
	return paqueteLvl_;
}

void GeneralData::changeParamID(int i, bool suma) {
	if (suma) {
		if (i == 0) {
			paramVolMusic_ += 10;
			if (paramVolMusic_ >= 100) {
				paramVolMusic_ = 100;
			}
		}
		else if (i == 1) {
			paramVolSfx_ += 10;
			if (paramVolSfx_ >= 100) {
				paramVolSfx_ = 100;
			}
		}
	}
	else {
		if (i == 0) {
			paramVolMusic_ -= 10;
			if (paramVolMusic_ <= 0) {
				paramVolMusic_ = 0;
			}
		}
		else if (i == 1) {
			paramVolSfx_ -= 10;
			if (paramVolSfx_ <= 0) {
				paramVolSfx_ = 0;
			}
		}
	}

	soundEmiter().setSoundVolumes(paramVolSfx_);
	soundEmiter().setMusicVolume(paramVolMusic_);
#ifdef _DEBUG
	std::cout << "El valor de la musica ahora es " << paramVolMusic_ << " y el valor de los SFX ahora es " << paramVolSfx_ << std::endl;
#endif // _DEBUG
}
void GeneralData::setPaqueteLevel(int lvl) {
	paqueteLvl_ = lvl;
}

void GeneralData::readNPCData() {
	std::unique_ptr<JSONValue> jsonFileNpcData(JSON::ParseFromFile(NPC_DATA_PATH));

	if (jsonFileNpcData == nullptr || !jsonFileNpcData->IsObject()) {
		throw config_File_Missing(NPC_DATA_PATH);
	}

	JSONObject npcDataRoot = jsonFileNpcData->AsObject();

	// cargamos los 7 personajes

	for (int i = Vagabundo; i < Jefe; i++)
	{
		//localizamos el personaje segun el indice
		std::string aux = personajeToString((Personaje)i);
		//obtenemos los datos del personaje
		JSONObject charData = npcDataRoot[aux]->AsObject();
		NPCdata* data = nullptr;
		if (i < Campesino) // npc grandes
		{
			data = new NPCMayorData((Personaje)i, charData);
		}
		else
		{
			data = new NPCMenorData((Personaje)i,charData);
		}
		npcData.emplace((Personaje)i, data);
	}
	//creamos el sistema de eventos y lo inicializamos
	if (npcEventSys == nullptr)
		npcEventSys = new NPCeventSystem();
}


void GeneralData::saveGame() {

	std::ofstream in;
	//en el caso de que no exista el fichero se crea uno nuevo
	in.open(SAVE_PATH);

	// Para ampliar el guardado acceder a los datos como si fuera un map y 
	// asignar un new JsonValue al elemento a modificar
	JSONObject root;

	//modificacion de los valores en el json
	modifyJsonData(root, "Dia", std::min(dia_, MAX_DAYS));
	modifyJsonData(root, "Dinero", dinero_);

	//puede sustituir a la lectura del npcData que es un poco intrusiva
	saveNPCData(root);

	//guardado de datos
	JSONValue* jsonFile = new JSONValue(root);
	in << jsonFile->Stringify(true);
	delete jsonFile;
	in.close();
}

void GeneralData::incrementarFelicidad(Personaje p, int felicidadIncr)
{
	int actualFelicidad = getNPCData(p)->numFelicidad;
	int newFelicidadInt = actualFelicidad + felicidadIncr;
	if (newFelicidadInt < 0)
		newFelicidadInt = 0;
	else if (newFelicidadInt > 100)
		newFelicidadInt = 100;
	
	Felicidad newFelicidad = SeFue;
	if (newFelicidadInt < 1)
		newFelicidad = Minima;
	else if (newFelicidadInt > MAX_HAPPINES)
		newFelicidad = Maxima;
	else if (newFelicidadInt < BAD_HAPPINES)
		newFelicidad = Mala;
	else if (newFelicidadInt < NORMAL_HAPPINES)
		newFelicidad = Normal;
	else
		newFelicidad = Buena;

	getNPCData(p)->felicidad = newFelicidad;
	getNPCData(p)->numFelicidad = newFelicidadInt;
}

Texture* GeneralData::personajeToTexture(Personaje pers)
{
	return &sdlutils().images().at(personajeToString(pers));
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
	case Jefe:
		aux = "Jefe";
		break;
	}
	return aux;
}

Personaje GeneralData::stringToPersonaje(const std::string& pers) {
	Personaje aux = Vagabundo;
	// no deja hacer switch y es una cochinada pero es la unica forma de hacerlo
	//se puede usar un hasmap
	if (pers == "Vagabundo")
		aux = npc::Vagabundo;
	else if (pers == "Secretario")
		aux = npc::Secretario;
	else if (pers == "Campesino")
		aux = npc::Campesino;
	else if (pers == "Artesano")
		aux = npc::Artesano;
	else if (pers == "Tarotisa")
		aux = npc::Tarotisa;
	else if (pers == "Soldado")
		aux = npc::Soldado;
	else if (pers == "Contable")
		aux = npc::Contable;
	else if (pers == "Jefe")
		aux = npc::Jefe;

	return aux;
}

const std::string GeneralData::intObjetoToString(int pers) {

	std::string aux = "";
	switch (pers) {

		//Hestia
	case 0: aux = "CasaGrande"; break;
	case 1: aux = "CartelOficina"; break;
	case 2: aux = "Muro"; break;

		//Artemisa
	case 3: aux = "TiendaPociones"; break;
	case 4: aux = "TiendaBolas"; break;
	case 5: aux = "TiendaJarrones"; break;

		//Demeter
	case 6: aux = "Molino"; break;
	case 7: aux = "Arbol"; break;
	case 8: aux = "Carreta"; break;

		//Hefesto
	case 9: aux = "PulpoCartel"; break;
	case 10: aux = "TiendaCeramica"; break;
	case 11: aux = "TiendaEsculturas"; break;

		//Hermes
	case 12: aux = "TiendaDerecha"; break;
	case 13: aux = "PanteonIzq"; break;
	case 14: aux = "PanteonDer"; break;

		//Apolo
	case 15: aux = "Panteon"; break;
	case 16: aux = "Edificios"; break;
	case 17: aux = "Charco"; break;

		//Poseidon
	case 18: aux = "Estatua"; break;
	case 19: aux = "ArbolesIzq"; break;
	case 20: aux = "ArbolesDer"; break;

	default: break;
	}
	return aux;
}

int GeneralData::stringToObjInt(const std::string& pers) {
	int aux = 0;

	//Hestia
	if (pers == "CasaGrande") aux = 0;
	else if (pers == "CartelOficina") aux = 1;
	else if (pers == "Muro") aux = 2;

	//Artemisa
	else if (pers == "TiendaPociones") aux = 3;
	else if (pers == "TiendaBolas") aux = 4;
	else if (pers == "TiendaJarrones") aux = 5;

	//Demeter
	else if (pers == "Molino") aux = 6;
	else if (pers == "Arbol") aux = 7;
	else if (pers == "Carreta") aux = 8;

	//Hefesto
	else if (pers == "PulpoCartel") aux = 9;
	else if (pers == "TiendaCeramica") aux = 10;
	else if (pers == "TiendaEsculturas") aux = 11;

	//Hermes
	else if (pers == "TiendaDerecha") aux = 12;
	else if (pers == "PanteonIzq") aux = 13;
	else if (pers == "PanteonDer") aux = 14;

	//Apolo
	else if (pers == "Panteon") aux = 15;
	else if (pers == "Edificios") aux = 16;
	else if (pers == "Charco") aux = 17;

	//Poseidon
	else if (pers == "Estatua") aux = 18;
	else if (pers == "ArbolesIzq") aux = 19;
	else if (pers == "ArbolesDer") aux = 20;

	return aux;
}

Felicidad GeneralData::stringToFelicidad(const std::string& str)
{
	Felicidad aux = Normal;
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
	else if (str == "SeFue")
		aux = Felicidad::SeFue;

	return aux;
}

std::string GeneralData::felicidadToString(Felicidad f)
{
	std::string aux = "";
	if (f == Minima)
		aux = "Minima";
	else if (f == Mala)
		aux = "Mala";
	else if (f == Normal)
		aux = "Normal";
	else if (f == Buena)
		aux = "Buena";
	else if (f == Maxima)
		aux = "Maxima";
	else if (f == NoHabladoAun)
		aux = "NoHabladoAun";
	else if (f == SeFue)
		aux = "SeFue";
	return aux;
}

const std::string GeneralData::calleToString(Calle calle) {
	std::string aux = "";
	switch (calle) {
	case C1:
		aux = "C1";
		break;
	case C2:
		aux = "C2";
		break;
	case C3:
		aux = "C3";
		break;
	case Erronea:
		aux = "Erronea";
		break;
	}
	return aux;
}

Calle GeneralData::stringToCalle(const std::string& calle) {
	Calle aux = Erronea;
	if (calle == "C1")
		aux = C1;
	else if (calle == "C2")
		aux = C2;
	else if (calle == "C3")
		aux = C3;
	else if (calle == "Erronea")
		aux = Erronea;
	return aux;
}

const std::string GeneralData::tipoPaqueteToString(TipoPaquete tipo) {
	std::string aux = "";
	if (tipo == Alimento)
		aux = "Alimento";
	else if (tipo == Medicinas)
		aux = "Medicinas";
	else if (tipo == Joyas)
		aux = "Joyas";
	else if (tipo == Materiales)
		aux = "Materiales";
	else if (tipo == Armamento)
		aux = "Armamento";
	return aux;
}

TipoPaquete GeneralData::stringToTipoPaquete(const std::string& tipo) {
	TipoPaquete aux = Alimento;
	if (tipo == "Alimento")
		aux = Alimento;
	else if (tipo == "Medicinas")
		aux = Medicinas;
	else if (tipo == "Joyas")
		aux = Joyas;
	else if (tipo == "Materiales")
		aux = Materiales;
	else if (tipo == "Armamento")
		aux = Armamento;
	return aux;
}

const std::string GeneralData::nivelPesoToString(NivelPeso nivel)
{
	std::string aux = "";
	switch (nivel) {
	case NivelPeso::Bajo:
		aux = "Bajo";
	case NivelPeso::Medio:
		aux = "Medio";
	case NivelPeso::Alto:
		aux = "Alto";
	case NivelPeso::Ninguno:
		aux = "Ninguno";
	}
	return aux;
}

NivelPeso GeneralData::stringToNivelPeso(const std::string& nivel)
{
	NivelPeso aux = Ninguno;
	if (nivel == "Bajo")
		aux = Bajo;
	else if (nivel == "Medio")
		aux = Medio;
	else if (nivel == "Alto")
		aux = Alto;
	else if (nivel == "Ninguno")
		aux = Ninguno;
	return aux;
}



// Struct NPCdata
#pragma region NPCdata

NPCdata* GeneralData::getNPCData(Personaje personaje) {
	NPCdata* npc = nullptr;

	npc = npcData[personaje];

	return npc;
}

GeneralData::IntObjsData::IntObjsData(std::string text)
{
	objId = text;
}

#pragma endregion

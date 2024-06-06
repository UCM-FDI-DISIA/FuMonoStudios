#pragma once
#ifndef DEV_TOOLS
#include <utils/checkML.h>
#endif // !DEV_TOOLS
#include <utils/Singleton.h>
#include <architecture/ecs.h>
#include <sistemas/NPC.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <json/JSON.h>
#include <json/JSONValue.h>
#include <bitset>
#include <architecture/Exceptions.h>
#include <architecture/GameConstants.h>

class DialogManager;
class PaqueteBuilder;
class Game;
class Paquete;
class Texture;

class NPCevent;
class NPCeventSystem;

namespace pq {
	/// <summary>
	/// enum con todos los distritos posibles que pueden tener los paquetes
	/// IMPORTANTE: Erroneo siempre debe ser el ultimo
	/// </summary>
	enum Distrito { Hestia, Artemisa, Demeter, Hefesto, Hermes, Apolo, Poseidon, Erroneo };
	/// <summary>
	/// enum con todas las calles posibles que pueden tener los paquetes
	/// </summary>
	enum Calle { C1, C2, C3, Erronea };
	/// <summary>
	/// enum con todoos los tipos de cargamento que pueden tener los paquetes
	/// </summary>
	enum TipoPaquete { Alimento, Medicinas, Joyas, Materiales, Armamento, Carta };
	/// <summary>
	/// enum con todas los tipos de medici�n de peso que pueden tener los paquetes
	/// </summary>
	enum NivelPeso { Ninguno, Bajo, Medio, Alto };
}

using namespace pq;
using namespace npc;
class GeneralData : public Singleton<GeneralData>
{
public:
	friend Singleton<GeneralData>;

	Felicidad stringToFelicidad(const std::string& str);
	std::string felicidadToString(Felicidad);

	enum MoveType{DropIn, PickUp};

	/// <summary>
	/// Estructura que almacena la informacion de los objetos interactuables
	/// </summary>
	struct IntObjsData {
		IntObjsData(std::string text);
		std::string objId;
	};
	/// <summary>
	/// Carga los datos de los NPC basicos del npcData.json
	/// estos datos no cambian entre guardados.
	/// Esta llamada se puede considerar la inicializacion de los NPC
	/// </summary>
	void readNPCData();

	/// <summary>
	/// Devuelve los datos del npc solicitado
	/// </summary>
	/// <param name="personaje"></param>
	/// <returns></returns>
	NPCdata* getNPCData(Personaje personaje);
	/// <summary>
	/// Incrementa la felicidad del personaje indicado
	/// </summary>
	/// <param name="p"></param>
	/// <param name="felicidadIncr"></param>
	void incrementarFelicidad(Personaje p, int felicidadIncr);

	NPCeventSystem* npcEventSys = nullptr;

private:
	/// <summary>
	/// vector que contiene los datos de todos los objetos interactuables
	/// </summary>
	std::vector<IntObjsData*> intObjData;
#pragma endregion
public:
	GeneralData();
	~GeneralData();
	/// <summary>
	/// Caraga la partida guardada
	/// </summary>
	void loadSaveFile();
	/// <summary>
	/// Metodo que acutaliza cuanto dinero tienes en funcion de los fallos y aciertos que realices
	/// </summary>
	/// <param name="writePacages"></param>
	/// <param name="wrongPacages"></param>
	void updateMoney();

	/// <summary>
	/// Calcula el dinero que recibe el jugador en base a los aciertos y fallos.
	/// </summary>
	/// <returns></returns>
	int calcularDineroGanado();
	
	/// <summary>
	/// Reestablece el dinero a la cantidad inicial
	/// </summary>
	void resetMoney(); 

	/// <summary>
	/// Devuelve la cantidad de dinero que tiene el jugador
	/// </summary>
	/// <returns></returns>
	inline int getMoney() { return dinero_; }

	inline void setUpgradeValue(ecs::upg::upgradeId upgrade, bool value) {
		upgrades_[upgrade] = value;
	}

	inline bool getUpgradeValue(ecs::upg::upgradeId upgrade) {
		return upgrades_[upgrade];
	}

	inline bool getUpgradeValue(npc::Personaje pers) {
		bool ret = false;
		switch (pers) {
		case Vagabundo:
			ret = getUpgradeValue(ecs::upg::SELLO_UPGRADE);
			break;
		case Tarotisa:
			ret = getUpgradeValue(ecs::upg::BOLA_UPGRADE);
			break;
		case Artesano:
			ret = getUpgradeValue(ecs::upg::ENVOLVER_UPGRADE);
			break;
		case Campesino:
			ret = getUpgradeValue(ecs::upg::BALANZA_UPGRADE);
			break;
		case Contable:
			ret = getUpgradeValue(ecs::upg::MONEY_UPGRADE);
			break;
		case Soldado:
			ret = getUpgradeValue(ecs::upg::FALLOS_UPGRADE);
			break;
		case Secretario:
			ret = getUpgradeValue(ecs::upg::MANUAL_UPGRADE);
			break;
		}
		return ret;
	}

	inline void unlockUpgrade(npc::Personaje pers) {
		switch (pers) {
		case Vagabundo: 
			setUpgradeValue(ecs::upg::SELLO_UPGRADE, true);
			break;
		case Tarotisa:
			setUpgradeValue(ecs::upg::BOLA_UPGRADE, true);
			break;
		case Artesano:
			setUpgradeValue(ecs::upg::ENVOLVER_UPGRADE, true);
			break;
		case Campesino:
			setUpgradeValue(ecs::upg::BALANZA_UPGRADE, true);
			break;
		case Contable:
			setUpgradeValue(ecs::upg::MONEY_UPGRADE, true);
			break;
		case Soldado:
			setUpgradeValue(ecs::upg::FALLOS_UPGRADE, true);
			break;
		case Secretario:
			setUpgradeValue(ecs::upg::MANUAL_UPGRADE, true);
			break;
		}
	}

	

	void setFinalID(int final); //Cambia el ID del final
	int getFinalID(); //Devuelve el id del final del juego

	void changeParamID(int i, bool suma); //Modifica un parametro en especifico y decide si se suma o no
	inline int getParamMusic() {
#ifdef _DEBUG
		std::cout << "El valor del parametro de musica que quieres es: " << paramVolMusic_ << std::endl;
#endif // _DEBUG
		return paramVolMusic_; 
	}

	inline int getParamSfx() {
#ifdef _DEBUG
		std::cout << "El valor del parametro de sfx que quieres es: " << paramVolSfx_ << std::endl;
#endif // _DEBUG
		return paramVolSfx_;
	}

	void ToggleSkipTutorial() {
		skipTutorial_ = !skipTutorial_;
	}

	bool GetValueSkipTutorial() {
		return skipTutorial_;
	}

	void ToggleFullScreen() {
		fullScreen_ = !fullScreen_;
	}

	bool GetValueFullScreen() {
		return fullScreen_;
	}

	inline int getDay() { return dia_; }
	inline void setDay(int dia) { 	
		dia_ = dia; 
		if (dia < MAX_DAYS) {
			updateDia();
		}
	}

	inline int getNumDistritos() { return (Distrito::Erroneo); }


	void updateDia();

	inline std::vector<std::string> getPlacesToActive() { return placesToActive_; }

	inline void setTubesAmount(int tubos) { 
		if (tubos >= 7) numTubos_ = 7;
		else numTubos_ = tubos; 
	} // Aumenta el numero de tubos en el minijuego cuando se requiera (podría llamarse automáticamente
	// desde setDia modificado). Que jose lo haga cuando se sepan los días en los que un distrito y su tubo se desbloquean
	inline int getTubesAmount() { return numTubos_; }
	inline void correctPackage() { corrects_++; }
	inline void wrongPackage() { fails_++; }
	inline int getFails() { return fails_; }
	inline int getCorrects() { return corrects_; }

	inline void resetFailsCorrects() { fails_ = 0; corrects_ = 0; }

	int getPaqueteLevel(); // Devuelve el lvl del paquete correspondiente al d�a
	void setPaqueteLevel(int lvl);

	int getRent();
	void setRent(int rent);

	//Texturas personajes
	Texture* personajeToTexture(Personaje pers);

	//Textos personajes
	const std::string personajeToString(Personaje pers);
	Personaje stringToPersonaje(const std::string& pers);

	//Textos objetos
	const std::string intObjetoToString(int pers);
	int stringToObjInt(const std::string& obj);

	//Textos distritos
	std::string fromDistritoToString(int i);
	int fromStringToDistrito(std::string place);

	//Textos calles
	const std::string calleToString(Calle calle);
	Calle stringToCalle(const std::string& calle);

	//Textos paquetes
	const std::string tipoPaqueteToString(TipoPaquete tipo);
	TipoPaquete stringToTipoPaquete(const std::string& tipo);

	//Textos peso
	const std::string nivelPesoToString(NivelPeso nivel);
	NivelPeso stringToNivelPeso(const std::string& nivel);							

	/// <summary>
	/// Guarda el juego
	/// </summary>
	void saveGame();

	void newGame();

	inline void setEndGame(bool end) { gameEndedOnce_ = end; };
	inline bool hasGameEndedOnce() { return gameEndedOnce_; };

	int getNPCpackageProb() { return probabilidadPaqueteNpc; }
	void setNPCpackageProb(int prob) { probabilidadPaqueteNpc = prob; }
private:
	void setNewGameValues();
	void addMoney(int cant) { dinero_ += cant; }
	void reduceMoney(int cant) { dinero_ -= cant; }

	void updateDistrictsPerDay(int dia);

	void saveNPCData(JSONObject& obj);

	void loadNPCsData(JSONObject& persojaesRoot);

	void savePersistentData();

	void loadPersistentData();

	/// <summary>
	/// estructura que almacena los datos de los npc
	/// </summary>
	std::unordered_map<Personaje,NPCdata*> npcData;
	/// <summary>
	/// Fallos cometidos por el jugador
	/// </summary>
	int fails_;
	/// <summary>
	/// Aciertos conseguidos por el jugador
	/// </summary>
	int corrects_;
	/// <summary>
	/// Precio del alquiler
	/// </summary>
	int rent_;
	/// <summary>
	/// Dinero que tiene le jugador
	/// </summary>
	int dinero_;
	/// <summary>
	/// Margen de fallos que puede cometer el jugador
	/// </summary>
	int failsMargin_;

	// probabilidad de que salga un paqNPc
	int probabilidadPaqueteNpc;

	int finalID_; //Variable int que define en la �ltima escena cu�l final se va a reproducir
	/// <summary>
	/// Dia de juego en el que nos encontramos
	/// </summary>
	int dia_;
	/// <summary>
	/// Clasificacion de distribucion de la creacion de paquetes
	/// </summary>
	int paqueteLvl_ = 0;

	/// <summary>
	/// Parametreos correspondientes al nivel de volumen 
	/// nivel de volumen (maximo 100).
	/// </summary>
	int paramVolMusic_;
	int paramVolSfx_;

	/// <summary>
	/// booleano que indica si se salta o no los tutoriales
	/// </summary>
	bool skipTutorial_;

	/// <summary>
	/// booleano que indica si esta el juego en pantalla completa o no
	/// </summary>
	bool fullScreen_;
	/// <summary>
	/// indica si el juego se ha completado en algun momento
	/// </summary>
	bool gameEndedOnce_;

	// Si en verdad en cuanto desbloqueas un distrito que explorar, aparece el tubo correspondiente en la oficina,
	// podemos hacer que la variable de numero de tubos y del numero de distritos desbloqueados sean una sola para simplificar todo
	
	/// <summary>
	/// Numero de tubos que habrán en el minijuego de paquetes
	/// </summary>
	int numTubos_;
	/// <summary>
	/// Luis: no se que hace realmente este vector si alguien sabe especificar que lo ponga porfavor y gracias
	/// </summary>
	std::vector<Paquete*> paquetesNPCs;
	/// <summary>
	/// Vector que almacena que distritos están desbloqueados
	/// </summary>
	std::vector<std::string> placesToActive_;
	/// <summary>
	/// Vector con las mejoras desbloqueadas hasta el momento
	/// </summary>
	//std::vector<bool> upgrades_;

	std::bitset<ecs::upg::_LAST_UPGRADE> upgrades_;

	/*/// <summary>
	/// Vector que se borrara al terminar de relizar el guardado
	/// </summary>
	std::vector<JSONValue*> jsonValVec;*/
};
/// <summary>
/// Accesor de General Data
/// </summary>
/// <returns></returns>
inline GeneralData& gD() {
	return *GeneralData::instance();
}
/// <summary>
/// metodo template que te permite modificar objetos de un JsonObject
/// usado en el metodo en el saveGame
/// Si se internta modificar un valor ya existente se generar memoty leaks
/// </summary>
/// <typeparam name="T">tipo que tendra el objeto a insertal en el jsonObject</typeparam>
/// <param name="obj">raiz del objeto Json a modificar</param>
/// <param name="key"></param>
/// <param name="val"></param>
template<typename T>
inline void modifyJsonData(JSONObject& obj, const std::string& key, T val) {
	//Luis: hacer destrucccion provoca una perdida de iterador en algun punto de JSONValue
	if (obj.count(key) != 0)
		delete obj[key];
	auto jsonVal = new JSONValue(val);
	obj[key] = jsonVal;
	//jsonValVec.push_back(jsonVal);
}

inline bool file_exist(const std::string& path) {
	std::ifstream f(path.c_str());
	return f.good();
}
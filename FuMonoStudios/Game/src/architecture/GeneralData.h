#pragma once
#include "../utils/Singleton.h"
#include "../components/Paquete.h"
#include "GameConstants.h"
#include <vector>

class GeneralData : public Singleton<GeneralData>
{
	friend Singleton<GeneralData>;
public:
	GeneralData() :dinero_(INITIAL_MONEY), finalID_(INITIAL_FINAL), eventoID_(INITIAL_EVENT),failsMargin_(INITIAL_FAILS_MARGIN),
		corrects_(0),fails_(0), dia_(1) { };
	~GeneralData(){};

	/// <summary>
	/// Metodo que acutaliza cuanto dinero tienes en funcion de los fallos y aciertos que realices
	/// </summary>
	/// <param name="writePacages"></param>
	/// <param name="wrongPacages"></param>
	void updateMoney(int correct, int wrong);
	void setFinalID(int final); //Cambia el ID del final
	int getFinalID(); //Devuelve el id del final del juego
	void setEventoID(int evento); //Cambia el ID del evento a ocurrir
	int getEventoID(); //Devuelve el id del evento que ocurrir� en el juego
	int getMoney() { return dinero_; }

	void correctPackage() { corrects_++; }
	void wrongPackage() { fails_++; }
	int getFails() { return fails_; }
	int getCorrects() { return corrects_; }
	void resetFailsCorrects() { fails_ = 0; corrects_ = 0; }
	void addPaqueteNPC(Paquete p) { paquetesNPCs.push_back(p); }
	bool areTherePaquetesNPC() { return paquetesNPCs.size() != 0; }
	void resetPaquetesNPC() { while (areTherePaquetesNPC()) paquetesNPCs.pop_back(); }
	Paquete getPaqueteNPC() { Paquete p = paquetesNPCs.back(); paquetesNPCs.pop_back(); return p; }

	int getPaqueteLevel(); // Devuelve el lvl del paquete correspondiente al d�a
	void setPaqueteLevel(int lvl);

	inline int getCurrentDay() { return dia_; };

private:
	void addMoney(int cant) { dinero_ += cant; }
	void reduceMoney(int cant) { dinero_ -= cant; }

	int fails_;
	int corrects_;
	int dinero_;
	int failsMargin_;
	int finalID_; //Variable int que define en la �ltima escena cu�l final se va a reproducir
	int eventoID_; //Variable int que define cual evento especial de la historia deber� de ejecutarse
	int dia_;
	int paqueteLvl_; // de momento es 0
	std::vector<Paquete> paquetesNPCs;
};

inline GeneralData& generalData() {
	return *GeneralData::instance();
}
#pragma once
#include "../utils/Singleton.h"
#include "GameConstants.h"

class GeneralData : public Singleton<GeneralData>
{
	friend Singleton<GeneralData>;
public:
	GeneralData() :dinero_(INITIAL_MONEY), finalID_(INITIAL_FINAL), eventoID_(INITIAL_EVENT),failsMargin_(INITIAL_FAILS_MARGIN),
		corrects(0),fails(0), dia(1) { };
	~GeneralData(){};

	/// <summary>
	/// Metodo que acutaliza cuanto dinero tienes en funcion de los fallos y aciertos que realices
	/// </summary>
	/// <param name="writePacages"></param>
	/// <param name="wrongPacages"></param>
	void updateMoney(int writePacages, int wrongPacages);
	void SetFinalID(int final); //Cambia el ID del final
	int GetFinalID(); //Devuelve el id del final del juego
	void SetEventoID(int evento); //Cambia el ID del evento a ocurrir
	int GetEventoID(); //Devuelve el id del evento que ocurrir� en el juego
	int getMoney() { return dinero_; }
	void correctPackage() { corrects++; }
	void wrongPackage() { fails++; }

	int getPaqueteLevel(); // Devuelve el lvl del paquete correspondiente al d�a
private:
	void addMoney(int cant) { dinero_ += cant; }
	void reduceMoney(int cant) { dinero_ -= cant; }

	int fails;
	int corrects;
	int dinero_;
	int failsMargin_;
	int finalID_; //Variable int que define en la �ltima escena cu�l final se va a reproducir
	int eventoID_; //Variable int que define cual evento especial de la historia deber� de ejecutarse
	int dia;
	int paqueteLvl = 0; // de momento es 0
};

inline GeneralData& generalData() {
	return *GeneralData::instance();
}
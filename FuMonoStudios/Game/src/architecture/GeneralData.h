#pragma once
#include "../utils/Singleton.h"
#include "GameConstants.h"

class GeneralData : public Singleton<GeneralData>
{
	friend Singleton<GeneralData>;
public:
	GeneralData() :dinero_(INITIAL_MONEY), finalID_(INITIAL_FINAL), eventoID_(INITIAL_EVENT) { };
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
	int GetEventoID(); //Devuelve el id del evento que ocurrirá en el juego

private:
	void addMoney(int cant) { dinero_ += cant; }
	void reduceMoney(int cant) { dinero_ -= cant; }

	int dinero_;
	int finalID_; //Variable int que define en la última escena cuál final se va a reproducir
	int eventoID_; //Variable int que define cual evento especial de la historia deberá de ejecutarse
};

inline GeneralData& generalData() {
	return *GeneralData::instance();
}
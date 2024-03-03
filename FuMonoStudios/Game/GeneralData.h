#pragma once
#include "src/utils/Singleton.h"
#include "src/GameConstants.h"
class GeneralData : public Singleton<GeneralData>
{
	friend Singleton<GeneralData>;
public:
	GeneralData():dinero_(INITIAL_MONEY), rightPacages(0), wrongPacages(0) { };
	~GeneralData(){};

	/// <summary>
	/// metodo que acutaliza cuanto dinero tienes en funcion de los fallos y aciertos que realices
	/// </summary>
	/// <param name="writePacages"></param>
	/// <param name="wrongPacages"></param>
	void updateMoney();
	void addRightPacage() { rightPacages++; }
	void addWrongPacage() { wrongPacages--; }
	void resetRightWrong() {
		rightPacages = 0;
		wrongPacages = 0;
	}

private:
	void addMoney(int cant) { dinero_ += cant; }
	void reduceMoney(int cant) { dinero_ -= cant; }

	int dinero_;

	int rightPacages;
	int wrongPacages;
};

inline GeneralData& generalData() {
	return *GeneralData::instance();
}
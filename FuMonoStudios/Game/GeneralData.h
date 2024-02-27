#pragma once
#include "src/utils/Singleton.h"
#include "src/GameConstants.h"
class GeneralData : public Singleton<GeneralData>
{
	friend Singleton<GeneralData>;
public:
	GeneralData():dinero_(INITIAL_MONEY) { };
	~GeneralData(){};

	/// <summary>
	/// metodo que acutaliza cuanto dinero tienes en funcion de los fallos y aciertos que realices
	/// </summary>
	/// <param name="writePacages"></param>
	/// <param name="wrongPacages"></param>
	void updateMoney(int writePacages, int wrongPacages);

private:
	void addMoney(int cant) { dinero += cant; }
	void reduceMoney(int cant) { dinero -= cant; }

	int dinero_
};

inline GeneralData& generalData() {
	return *GeneralData::instance();
}
#pragma once
#include "src/utils/Singleton.h"
class GeneralData : public Singleton<GeneralData>
{
	friend Singleton<GeneralData>;
public:
	GeneralData():dinero() { };
	~GeneralData(){};



private:
	int dinero;
};

inline GeneralData& generalData() {
	return *GeneralData::instance();
}
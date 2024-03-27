#ifdef QA_TOOLS
#include "DataCollector.h"
#include <architecture/Time.h>
#include <architecture/GeneralData.h>
#include <SDL.h>
//NECESARIO c++ 17
//#include <cpr/cpr.h>
/*
dejo parado esto hasta hablar con carlos, no estoy siendo capaz de encontrar como hacer la solicitud
al cliente de forma correcta
*/
//#include "restclient-cpp/connection.h"
//#include "restclient-cpp/restclient.h"


DataCollector::DataCollector() : currentRow_(0), dataArray_(),clicks_(0) {
	dataArray_.resize(NUMBER_OF_METRICS);
	rapidcsv::LabelParams(-1, 0);

	//puede dar error fatal si el fichero esta abierto
	doc_.Load("QAdata/myData.csv");
	doc_.Clear();
	std::vector<std::string> Labels = { 
		"Escena","Marca de Tiempo (ms)","Clicks","Dia de Juego","Distrito","Calle","Tipo","Peso","Envoltura","NPC"
	};

	for (int i = 0; i < Labels.size(); i++) {
		doc_.SetColumnName(i, Labels[i]);
	}
};

void DataCollector::recordPacage(Paquete* pacage) {
	dataArray_[doc_.GetColumnIdx("Distrito")] = pacage->getDistrito();
	dataArray_[doc_.GetColumnIdx("Calle")] = pacage->getCalle();
	dataArray_[doc_.GetColumnIdx("Tipo")] = pacage->getTipo();
	dataArray_[doc_.GetColumnIdx("Peso")] = pacage->getPeso();
	dataArray_[doc_.GetColumnIdx("Envoltura")] = pacage->getFragil();
	record();
}

DataCollector::~DataCollector()
{
	doc_.Save();
}

void DataCollector::record()
{
	dataArray_[1] = SDL_GetTicks();
	dataArray_[2] = clicks_;
	dataArray_[3] = generalData().getCurrentDay();
	doc_.SetRow(currentRow_, dataArray_);
	dataArray_.clear();
	dataArray_.resize(NUMBER_OF_METRICS);
	currentRow_++;
}
#endif // QA_TOOLS

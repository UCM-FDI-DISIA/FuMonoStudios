#include "DataCollector.h"
#include <architecture/Time.h>
#include <SDL.h>

DataCollector::DataCollector() : currentRow_(0) {
	dataArray_.resize(NUMBER_OF_METRICS);
	rapidcsv::LabelParams(-1, 0);

	//puede dar error fatal si el fichero esta abierto
	doc_.Load("QAdata/myData.csv");
	doc_.Clear();
	std::vector<std::string> Labels = { 
		"Escena","Marca de Tiempo","Clicks",
	};

	for (int i = 0; i < Labels.size(); i++) {
		doc_.SetColumnName(i, Labels[i]);
	}
};


void DataCollector::record()
{
	float currTime = SDL_GetTicks() / 1000.0f;
	//dataArray_[0] = currentScene_;
	dataArray_[1] = currTime;
	dataArray_[2] = clicks_;
	doc_.SetRow(currentRow_, dataArray_);
	dataArray_.clear();
	dataArray_.resize(NUMBER_OF_METRICS);
	currentRow_++;
}

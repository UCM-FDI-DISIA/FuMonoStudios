#pragma once
#include <iostream>
#include <fstream>
#include "../../rapidCSV/rapidcsv.h"
#include <utils/Singleton.h>
/// <summary>
/// Clase abstracta de la que heredar para generar distintos csv en funcion de los datos a recopilar
/// </summary>
class DataCollector : public Singleton<DataCollector>
{
	friend Singleton<DataCollector>;

public:
	~DataCollector() {

	}

	void record();

private:
	DataCollector() {
		doc.Load("QAdata/myData.csv");
	};
	virtual ~DataCollector() {
		doc.Save();
	};
	/// <summary>
	/// Documento sobre el que se escribe el csv
	/// </summary>
	rapidcsv::Document doc;
};

inline DataCollector& generalData() {
	return *DataCollector::instance();
}


#pragma once
#include <iostream>
#include <fstream>
/// <summary>
/// Clase abstracta de la que heredar para generar distintos csv en funcion de los datos a recopilar
/// </summary>
class DataCollector
{
protected:
	DataCollector();
	virtual ~DataCollector() {
		dataFile.close();
	};
	/// <summary>
	/// Caracter de separacion para el scv
	/// </summary>
	const char SEPARATOR = ';';
	/// <summary>
	/// Fichero en el que se cargará la informacion
	/// </summary>
	std::ofstream dataFile;
};


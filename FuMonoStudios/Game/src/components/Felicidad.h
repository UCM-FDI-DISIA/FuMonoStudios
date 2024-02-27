#pragma once
#include <unordered_map>

//enums globales
enum Personajes { SECRETARIO_REAL, VAGABUNDO, CONTABLE,ARTESANO, TAROTISTA, SOLDADO, CAMPESINO};
enum EstadosDeFelicidad{MÍNIMA, BAJA, INTERMEDIA, FELIZ, MAXIFELIZ};

using uint = unsigned int;
class Felicidad
{
private:
	std::unordered_map<Personajes, int> felicidades;
public:
	Felicidad();

	void aumentaFel(Personajes p, uint f);
	void decrementaFel(Personajes p, uint f);
	EstadosDeFelicidad interpretaFel(Personajes p) const;
};


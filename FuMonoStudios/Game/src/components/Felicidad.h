#pragma once
#include <unordered_map>

//enums globales
namespace pers{
	enum Personajes { SECRETARIO_REAL, VAGABUNDO, CONTABLE, ARTESANO, TAROTISTA, SOLDADO, CAMPESINO };
	enum EstadosDeFelicidad { MINIMA, BAJA, INTERMEDIA, FELIZ, MAXIFELIZ };
}

using uint = unsigned int;
class Felicidad
{
private:
	std::unordered_map<pers::Personajes, int> felicidades;
public:
	Felicidad();

	void aumentaFel(pers::Personajes p, uint f);
	void decrementaFel(pers::Personajes p, uint f);
	pers::EstadosDeFelicidad interpretaFel(pers::Personajes p) const;
};


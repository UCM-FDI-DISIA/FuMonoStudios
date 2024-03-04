#include "Felicidad.h"

Felicidad::Felicidad()
{
	for (int i = 0; i <= 6; i++) {
		felicidades[(pers::Personajes) i] = 0;
	}
}

void Felicidad::aumentaFel(pers::Personajes p, uint f) // cleon: no se�is salvajes de C++. Personajes por referencia (constante?)
{
	if (felicidades.at(p) + f <= 99)
		felicidades[p] += f;
	else
		felicidades[p] = 99; // Toma 99.
}

void Felicidad::decrementaFel(pers::Personajes p, uint f)
{
	felicidades[p] -= f;
}

pers::EstadosDeFelicidad Felicidad::interpretaFel(pers::Personajes p) const
{
	int s = felicidades.at(p);
	if (s <= 0){
		return pers::MINIMA;
	}
	else if(s > 0 && s <= 33){
		return pers::BAJA;
	}
	else if (s > 33 && s <= 66){
		return pers::INTERMEDIA;
	}
	else if (s > 33 && s <= 66) {
		return pers::FELIZ;
	}
	else{
		return pers::MAXIFELIZ;
	}
}
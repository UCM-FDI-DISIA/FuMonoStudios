#include "Felicidad.h"

Felicidad::Felicidad()
{
	for (int i = 0; i <= 6; i++) {
		felicidades[(Personajes) i] = 0;
	}
}

void Felicidad::aumentaFel(Personajes p, uint f) // cleon: no seáis salvajes de C++. Personajes por referencia (constante?)
{
	if (felicidades.at(p) + f <= 99)
		felicidades[p] += f;
	else
		felicidades[p] = 99; // Toma 99.
}

void Felicidad::decrementaFel(Personajes p, uint f)
{
	felicidades[p] -= f;
}

EstadosDeFelicidad Felicidad::interpretaFel(Personajes p) const
{
	int s = felicidades.at(p);
	if (s <= 0){
		return MÍNIMA; // cleon: OLÉ. Esa tilde.
	}
	else if(s > 0 && s <= 33){
		return BAJA;
	}
	else if (s > 33 && s <= 66){
		return INTERMEDIA;
	}
	else if (s > 33 && s <= 66) {
		return FELIZ;
	}
	else{
		return MAXIFELIZ;
	}
}
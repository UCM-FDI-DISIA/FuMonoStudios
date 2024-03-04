#include "PaqueteBuilder.h"


Paquete::Distrito PaqueteBuilder::DistritoRND() {	//Este método devuelve un Distrito aleatorio entre todas las posibilidades
	int rnd = rand() % 7;
	return (Paquete::Distrito)rnd;
}
Paquete::TipoPaquete PaqueteBuilder::TipoRND() {	//Este método devuelve un Tipo de paquete aleatorio entre todas las posibilidades
	int rnd = rand() % 5;
	return (Paquete::TipoPaquete)rnd;
}
Paquete::Calle PaqueteBuilder::CalleRND(int probError) {	//Este método devuelve una calle aleatoria de las posibilidades, con probabilidad de que salga un resultado erróneo
	int rnd = rand() % 100; // cleon: en C++ hay maneras mejores de hacer números aleatorios
	if (rnd > probError) {
		rnd = rand() % 3 + 1;
		return (Paquete::Calle)rnd;
	}
	else {
		return Paquete::Calle::Erronea;
	}
}
bool PaqueteBuilder::BoolRND(int probFalse) { //Este método devuelve una valor aleatorio entre treu y false para un bool según una probabilidad
	int rnd = rand() % 100;
	if (rnd > probFalse) {
		return true;
	}
	else {
		return false;
	}
}
Paquete::NivelPeso PaqueteBuilder::PesoRND(int probPeso, int probError, int& peso) {	//Este método elige aleatoriamente si colocar un sello de peso o no en el paquete y, en caso positivo,
	int rnd = rand() % 100;												//elige aleatoriamente si el resultado es correcto o incorrecto, devolviendo un peso para el paquete
	if (rnd > probPeso) {
		Paquete::NivelPeso pes;
		rnd = rand() % 3 + 1;
		pes = (Paquete::NivelPeso)rnd;

		rnd = rand() % 100;
		if (rnd > probError) {
			if (pes == Paquete::NivelPeso::Alto) {
				peso = rand() % (pesadoMax - medioMax) + medioMax;
			}
			else if (pes == Paquete::NivelPeso::Medio) {
				peso = rand() % (medioMax - ligeroMax) + ligeroMax;
			}
			else if (pes == Paquete::NivelPeso::Bajo) {
				peso = rand() % ligeroMax + 1;
			}
		}
		else {
			if (pes == Paquete::NivelPeso::Alto) {
				peso = rand() % medioMax + 1;
			}
			else if (pes == Paquete::NivelPeso::Medio) {
				rnd = rand() % 2;
				if (rnd == 0) {
					peso = rand() % ligeroMax + 1;
				}
				else {
					peso = rand() % (pesadoMax - medioMax) + medioMax;
				}
			}
			else if (pes == Paquete::NivelPeso::Bajo) {
				peso = rand() % (pesadoMax - ligeroMax) + ligeroMax;
			}
		}
		return pes;
	}
	else {
		peso = rand() % pesadoMax + 1;
		return Paquete::NivelPeso::Ninguno;
	}
}
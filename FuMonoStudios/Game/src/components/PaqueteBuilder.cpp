#include "PaqueteBuilder.h"


Paquete::Distrito DistritoRND() {
	int rnd = rand() % 7;
	return (Paquete::Distrito)rnd;
}
Paquete::TipoPaquete TipoRND() {
	int rnd = rand() % 5;
	return (Paquete::TipoPaquete)rnd;
}
Paquete::Calle CalleRND(int probError) {
	int rnd = rand() % 100;
	if (rnd > probError) {
		rnd = rand() % 3 + 1;
		return (Paquete::Calle)rnd;
	}
	else {
		return Paquete::Calle::Erronea;
	}
}
bool BoolRND(int probFalse) {
	int rnd = rand() % 100;
	if (rnd > probFalse) {
		return true;
	}
	else {
		return false;
	}
}
Paquete::NivelPeso PesoRND(int probPeso, int probError, int& peso) {
	int rnd = rand() % 100;
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
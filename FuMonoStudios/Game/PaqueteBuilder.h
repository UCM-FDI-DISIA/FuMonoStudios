#pragma once
#include "Paquete.h"
#include <stdlib.h>

const int pesadoMax = 75;
const int medioMax = 50;
const int ligeroMax = 25;

class PaqueteBuilder
{
private:
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
			rnd = rand() % 3 +1;
			return (Paquete::Calle)rnd;
		}
		else{
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
	Paquete::NivelPeso PesoRNG(int probPeso, int probError, int& peso) {
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
					}else{
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



	Paquete* Nivel0() {
		return new Paquete(DistritoRND(),CalleRND(35), TipoRND(), true, Paquete::NivelPeso::Ninguno, rand() % pesadoMax + 1, false);
	}
	Paquete* Nivel1() {
		return new Paquete(DistritoRND(), CalleRND(20), TipoRND(), BoolRND(35), Paquete::NivelPeso::Ninguno, rand() % pesadoMax + 1, false);
	}
	Paquete* Nivel2() {
		int peso;
		Paquete::NivelPeso Nv = PesoRNG(25, 30, peso);
		return new Paquete(DistritoRND(), CalleRND(15), TipoRND(), BoolRND(20), Nv, peso, false);
	}
	Paquete* Nivel3() {
		int peso;
		Paquete::NivelPeso Nv = PesoRNG(20, 25, peso);
		return new Paquete(DistritoRND(), CalleRND(15), TipoRND(), BoolRND(20), Nv, peso, BoolRND(80));
	}
public:
	Paquete* PaqueteRND(int level) {
		
		if (level == 0) {
			return Nivel0();
		}
		else if (level == 1) {
			return Nivel1();
		}
		else if (level == 2) {
			return Nivel2();
		}
		else if (level == 3) {
			return Nivel3();
		}
		else return nullptr;
	}
};
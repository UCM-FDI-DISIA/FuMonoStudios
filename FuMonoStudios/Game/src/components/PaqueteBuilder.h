#pragma once
#include "Paquete.h"
#include <stdlib.h>


const int pesadoMax = 75;	//Límite del peso máximo de paquetes pesados 
const int medioMax = 50;	//Límite del peso máximo de paquetes de peso medio 
const int ligeroMax = 25;	//Límite del peso máximo de paquetes ligeros
const int pesoCartaMax = 2;	//Límite del peso máximo de cartas

class PaqueteBuilder
{
private:
	Paquete* Nivel0() {
		return new Paquete(DistritoRND(),CalleRND(35), TipoRND(), true, Paquete::NivelPeso::Ninguno, rand() % pesadoMax + 1, false,false);
	}
	Paquete* Nivel1() {
		return new Paquete(DistritoRND(), CalleRND(20), TipoRND(), BoolRND(35), Paquete::NivelPeso::Ninguno, rand() % pesadoMax + 1, false, false);
	}
	Paquete* Nivel2() {
		int peso;
		Paquete::NivelPeso Nv = PesoRND(25, 30, peso);
		return new Paquete(DistritoRND(), CalleRND(15), TipoRND(), BoolRND(20), Nv, peso, false, false);
	}
	Paquete* Nivel3() {
		int peso;
		Paquete::NivelPeso Nv = PesoRND(20, 25, peso);
		return new Paquete(DistritoRND(), CalleRND(15), TipoRND(), BoolRND(20), Nv, peso, BoolRND(80), false);
	}
	Paquete* Carta() {		
		return new Paquete(DistritoRND(), CalleRND(35), TipoRND(), true, Paquete::NivelPeso::Ninguno, rand() % pesoCartaMax + 1, false, true);
	}

	Paquete::Distrito DistritoRND();
	Paquete::TipoPaquete TipoRND();
	Paquete::Calle CalleRND(int probError);
	bool BoolRND(int probFalse);
	Paquete::NivelPeso PesoRND(int probPeso, int probError, int& peso);

public:
	//Método al que se llama que devuelve un Paquete generado aleatoriamente 
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
	Paquete* CartaRND() {
		return Carta();
	}

};
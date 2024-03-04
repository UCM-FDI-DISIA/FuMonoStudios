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
	Paquete* Nivel0() {	//Un paquete que no tiene ni sellos normales, de peso o de fragil, y solo puede tener calles erróneas
		return new Paquete(DistritoRND(),CalleRND(35), TipoRND(), true, Paquete::NivelPeso::Ninguno, rand() % pesadoMax + 1, false,false);
	}
	Paquete* Nivel1() {	//Un paquete que no tiene ni sellos de peso ni sello de fragil, y puede tener tanto calles como sellos de tipo erróneos
		return new Paquete(DistritoRND(), CalleRND(20), TipoRND(), BoolRND(35), Paquete::NivelPeso::Ninguno, rand() % pesadoMax + 1, false, false);
	}
	Paquete* Nivel2() { //Un paquete que no tiene sello de fragil, pero puede tener sellos de peso, así como calles erróneas y sellos de tipo erróneos
		int peso;
		Paquete::NivelPeso Nv = PesoRND(25, 30, peso);
		return new Paquete(DistritoRND(), CalleRND(15), TipoRND(), BoolRND(20), Nv, peso, false, false);
	}
	Paquete* Nivel3() { //Un paquete que puede tener peso, sellos de frágil, calles erróneas y sellos de tipo erróneos
		int peso;
		Paquete::NivelPeso Nv = PesoRND(20, 25, peso);
		return new Paquete(DistritoRND(), CalleRND(15), TipoRND(), BoolRND(20), Nv, peso, BoolRND(80), false);
	}
	Paquete* Carta() {	//Una carta, que en esencia funciona igual que un paquete de nivel 0
		return new Paquete(DistritoRND(), CalleRND(35), TipoRND(), true, Paquete::NivelPeso::Ninguno, rand() % pesoCartaMax + 1, false, true);
	}

	Paquete::Distrito DistritoRND();	//Método que elige un distrito aleatorio de los que hay
	Paquete::TipoPaquete TipoRND();		//Método que elige un tipo de paquete aleatorio entre los que hay
	Paquete::Calle CalleRND(int probError);	//Método que elige una calle aleatoria de las posibilidades. El valor probError es, sobre 100, la probabilidad de que sea una calle incorrecta
	bool BoolRND(int probFalse);		//Método que genera un bool con valor aleatorio entre true y false. El valor probFalse es, sobre 100, la probabilidad de que sea false
	Paquete::NivelPeso PesoRND(int probPeso, int probError, int& peso);	//Método que elige si un paquete tiene peso, y si es erróneo, devolviendo un peso para el paquete con la variable "peso"

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
	//Método al que se llama que devuelve una Carta generada aleatoriamente 
	Paquete* CartaRND() {
		return Carta();
	}

};
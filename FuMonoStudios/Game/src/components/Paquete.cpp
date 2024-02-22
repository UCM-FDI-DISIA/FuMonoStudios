#include "Paquete.h"

const int nivelFragil = 3;
const int nivelPeso = 2;
const int nivelSellos = 1;

const int desviacionPeso = 15;
const int ligeroMax = 25;
const int medioMax = 50;
const int pesadoMax = 75;

Paquete::Paquete(Distrito dis, Calle c, TipoPaquete Tp, bool corr, NivelPeso Np, int p, bool f, bool cart) : miDistrito(dis), miCalle(c), miTipo(Tp), 
	selloCorrecto(corr), miPeso(Np), peso(p), fragil(f), carta(cart),envuelto(false), calleMarcada(Erronea){}

Paquete::~Paquete() {

}

bool Paquete::Correcto() const{ 
	//Método que comprueba si el paquete había sido generado sin errores (AKA: Si da false, eso significa que se tendría que devolver al remitente)
	bool resul = true;
	if (miCalle == Erronea) {
		resul = false;
	}
	if (miDistrito == Erroneo) {
		resul = false;
	}
	else if (!selloCorrecto) {
		resul = false;
	}
	else if (miPeso != Ninguno){
		if (miPeso == Bajo) {
			if (peso > ligeroMax) resul = false;
		}
		else if (miPeso == Medio) {
			if (peso < ligeroMax || peso > medioMax) resul = false;
		}
		else if (miPeso == Alto) {
			if (peso < medioMax) resul = false;
		}		
	}
	return resul;
}

Paquete::Distrito Paquete::getDist() const
{
	return miDistrito;
}

void Paquete::sellarCalle(Calle sello) {
	if (sello != Erronea && calleMarcada == Erronea) // solo puedes sellar una vez
	{
		calleMarcada = sello;
	}
}

std::string Paquete::getDirecction()
{

	std::string dir = "Tu vieja\n";


	switch (miDistrito) {
	case Demeter:
		dir += "Demeter";
		break;
	case Hefesto:
		dir += "Hefesto";
		break;
	case Hestia:
		dir += "Hestia";
		break;
	case Artemisa:
		dir += "Artemisa";
		break;
	case Hermes:
		dir += "Hermes";
		break;
	case Apolo:
		dir += "Apolo";
		break;
	case Poseidon:
		dir += "Poseidon";
		break;
	}
	dir += "\n";

	//habria que comprobar si la direccion tiene que ser correcta
	dir += distrito_calle[miDistrito][miCalle];

	return dir;
}

#include "Paquete.h"
#include "../json/JSON.h"
#include <memory>
#include <iostream>

const int nivelFragil = 3;
const int nivelPeso = 2;
const int nivelSellos = 1;

const int desviacionPeso = 15;
const int ligeroMax = 25;
const int medioMax = 50;
const int pesadoMax = 75;

Paquete::Paquete(Distrito dis, Calle c, TipoPaquete Tp, bool corr, NivelPeso Np, int p, bool f, bool cart) : miDistrito(dis), miCalle(c), miTipo(Tp), 
	selloCorrecto(corr), miPeso(Np), peso(p), fragil(f), carta(cart),envuelto(false), calleMarcada(Erronea){
	
	//TODO: convertir esto a un método que reciba el enum y el string del distrito y el jsonObject

	std::string filename = "recursos/config/mail.direcctions.json";
	
	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

	// check it was loaded correctly
	// the root must be a JSON object
	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing '" + filename + "'";
	}

	// we know the root is JSONObject
	JSONObject root = jValueRoot->AsObject();
	JSONValue* jValue = nullptr;

	jValue = root["Demeter"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			distrito_calle[Demeter].reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto v : jValue->AsArray()) {
				if (v->IsString()) {
					std::string aux = v->AsString();
#ifdef _DEBUG
					std::cout << "Loading distrito with id: " << aux << std::endl;
#endif
					distrito_calle[Demeter].emplace_back(aux);
				}
				else {
					throw "'Calles' array in '" + filename
						+ "' includes and invalid value";
				}
			}
		}
		else {
			throw "'Demeter' is not an array in '" + filename + "'";
		}
	}

}

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

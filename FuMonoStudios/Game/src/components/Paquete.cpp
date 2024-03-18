#include "Paquete.h"
#include "../json/JSON.h"
#include <memory>
#include <iostream>
#include "../architecture/Entity.h"
#include "Render.h"
#include "../architecture/Scene.h"
#include <bitset>
#include "../sistemas/PaqueteBuilder.h"
#include "MoverTransform.h"


// cleon: 962 gatitos acaban de morir. con dolor.
const int nivelFragil = 3;
const int nivelPeso = 2;
const int nivelSellos = 1;

const int desviacionPeso = 15;
const int ligeroMax = 25;
const int medioMax = 50;
const int pesadoMax = 75;

Paquete::Paquete(Distrito dis, Calle c, std::string remitente, TipoPaquete Tp, bool corr, NivelPeso Np, int p, bool f, bool cart) : 
	miDistrito_(dis), miCalle_(c), miRemitente_(remitente),miTipo_(Tp),selloCorrecto_(corr), 
	miPeso_(Np), peso_(p), fragil_(f), carta_(cart),envuelto_(false), pesado_(false), calleMarcada_(Erronea){
	
	std::string filename = "recursos/config/mail.direcctions.json";
	getStreetsFromJSON(filename, Demeter, "Demeter");
	getStreetsFromJSON(filename, Hefesto, "Hefesto");
	getStreetsFromJSON(filename, Hestia, "Hestia");
	getStreetsFromJSON(filename, Artemisa, "Artemisa");
	getStreetsFromJSON(filename, Hermes, "Hermes");
	getStreetsFromJSON(filename, Apolo, "Apolo");
	getStreetsFromJSON(filename, Poseidon, "Poseidon");

}

Paquete::~Paquete() {

}

void Paquete::initComponent() {

}

bool Paquete::bienSellado() const{
	return calleMarcada_ == miCalle_;
}
bool Paquete::pesoCorrecto() const {
	bool result = true;
	if (miPeso_ != Ninguno) {	//Si tiene un sello de pesado y su peso no est� entre los valores indicados, el paquete no es correcto
		if (miPeso_ == Bajo) {
			if (peso_ > ligeroMax) result = false;
		}
		else if (miPeso_ == Medio) {
			if (peso_ < ligeroMax || peso_ > medioMax) result = false;
		}
		else if (miPeso_ == Alto) {
			if (peso_ < medioMax) result = false;
		}
	}
	return result;
}
bool Paquete::correcto() const{ 
	//M�todo que comprueba si el paquete habia sido generado sin errores (AKA: Si da false, eso significa que se tendr�a que devolver al remitente)
	bool resul = true;
	if (miCalle_ == Erronea) { //Si la calle es err0nea, el paquete no es correcto
		resul = false;
	}
	if (miDistrito_ == Erroneo) { //Si el distrito es err�neo, el paquete no es correcto
		resul = false;
	}
	else if (!selloCorrecto_) {	//Si el sello de tipo no es correcto, el paquete no es correcto
		resul = false;
	}
	else if (!pesoCorrecto()){	//Si tiene un sello de pesado y su peso no est� entre los valores indicados, el paquete no es correcto
		resul = false;				
	}
	return resul;	//Si ha superdado todas las pruebas exitosamente, el paquete ser� correcto y devolver� true. Si en alg�n momento ha fallado, devolver� false
}

void Paquete::sellarCalle(Calle sello, Transform* trSellador) {

	Vector2D posPaquete = ent_->getComponent<Transform>()->getPos();

	// queremos que la pos sea relativa ya que el sello será hijo de paquete
	Vector2D posSellador = Vector2D(trSellador->getPos().getX() - posPaquete.getX() + trSellador->getWidth()/2,
									trSellador->getPos().getY() - posPaquete.getY() + trSellador->getHeigth()/2);

	// solo puedes sellar una vez  
	if (sello != Erronea && calleMarcada_ == Erronea)
	{
		calleMarcada_ = sello;
		PaqueteBuilder::getInstance()->crearSelloCalle(ent_, miCalle_, posSellador);
	}
}
	
void Paquete::sellarPeso(Transform* trBalanza) {

	if (!pesado_) {
		ent_->addComponent<MoverTransform>(Vector2D(trBalanza->getPos()), 0.5, Easing::EaseOutCubic);
		//ent_->addComponent<MoverTransform>(Vector2D(100, 520), 0.5, Easing::EaseOutCubic);

		NivelPeso test = NivelPeso::Alto;
		PaqueteBuilder::getInstance()->crearSelloPesado(ent_, test);
		//PaqueteBuilder::getInstance()->crearSelloPesado(ent_, miPeso_);
		pesado_ = true;
	}
}

std::string Paquete::getDirecction()
{
	// vamos a hacer que ponga exterior / interior y luego codigo postal
	std::string dir;
	if (miDistrito_ < 4)
		dir = "Exterior - ";
	else
		dir = "Interior - ";

	//creacion de codigo postal
	if (miDistrito_ == Erroneo)
		dir += "000\n";
	else
		dir += std::bitset<3>(miDistrito_ + 1).to_string() + "\n";

	//habria que comprobar si la direccion tiene que ser correcta
	if (miCalle_ == Erronea)
		dir += "(CALLE INVENTADA)";
	else if (miDistrito_ == Erroneo)
		dir += "(CALLE INVENTADA)";
	else
		dir += distritoCalle_[miDistrito_][miCalle_];

	return dir;
}

void Paquete::getStreetsFromJSON(std::string filename, Distrito dist, std::string distString)
{
	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

	// check it was loaded correctly
	// the root must be a JSON object
	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing '" + filename + "'";
	}

	// we know the root is JSONObject
	JSONObject root = jValueRoot->AsObject();
	JSONValue* jValue = nullptr;

	jValue = root[distString];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			distritoCalle_[dist].reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto v : jValue->AsArray()) {
				if (v->IsString()) {
					std::string aux = v->AsString();
#ifdef _DEBUG
					std::cout << "Loading distrito with id: " << aux << std::endl;
#endif
					distritoCalle_[dist].emplace_back(aux);
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

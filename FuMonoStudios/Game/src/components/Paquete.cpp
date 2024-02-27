#include "Paquete.h"
#include "../json/JSON.h"
#include <memory>
#include <iostream>
#include "../architecture/Entity.h"
#include "Transform.h"
#include "Render.h"
#include "../architecture/Scene.h"

const int nivelFragil = 3;
const int nivelPeso = 2;
const int nivelSellos = 1;

const int desviacionPeso = 15;
const int ligeroMax = 25;
const int medioMax = 50;
const int pesadoMax = 75;

Paquete::Paquete(Distrito dis, Calle c, TipoPaquete Tp, bool corr, NivelPeso Np, int p, bool f, bool cart) : miDistrito(dis), miCalle(c), miTipo(Tp), 
	selloCorrecto(corr), miPeso(Np), peso(p), fragil(f), carta(cart),envuelto(false), calleMarcada(Erronea){
	
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

bool Paquete::Correcto() const{ 
	//Método que comprueba si el paquete había sido generado sin errores (AKA: Si da false, eso significa que se tendría que devolver al remitente)
	bool resul = true;
	if (miCalle == Erronea) { //Si la calle es errónea, el paquete no es correcto
		resul = false;
	}
	if (miDistrito == Erroneo) { //Si el distrito es erróneo, el paquete no es correcto
		resul = false;
	}
	else if (!selloCorrecto) {	//Si el sello no es correcto, el paquete no es correcto
		resul = false;
	}
	else if (miPeso != Ninguno){	//Si tiene un sello de pesado y su peso no está entre los valores indicados, el paquete no es correcto
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
	return resul;	//Si ha superdado todas las pruebas exitosamente, el paquete será correcto y devolverá true. Si en algún momento ha fallado, devolverá false
}

Paquete::Distrito Paquete::getDist() const
{
	return miDistrito;
}

void Paquete::sellarCalle(Calle sello, Vector2D posSellador) {
	// solo puedes sellar una vez
	if (sello != Erronea && calleMarcada == Erronea) 
	{
		calleMarcada = sello;
		Transform* paqTr = ent_->getComponent<Transform>();

		//Creamos la entidad sello
		ecs::Entity* selloEnt = ent_->getMngr()->addEntity();
		//Textura en funcion de tipo calle
		Texture* selloEntTex = &sdlutils().images().at(
			(std::string)"sello" += 
			(std::string)(sello == C1 ? "A" : sello == C2 ? "B" : "C"));

		//creamos transform y colocamos el sello en el centro del sellador
		float scale = 0.2f;
		Transform* selloEntTr = selloEnt->addComponent<Transform>
			(posSellador.getX() - selloEntTex->width() / 2 * scale, 
			posSellador.getY() - selloEntTex->height() / 2 * scale,
			selloEntTex->width() * scale, selloEntTex->height() * scale);
		selloEnt->addComponent<RenderImage>(selloEntTex);
		selloEntTr->setParent(paqTr);
	}
}

std::string Paquete::getDirecction()
{

	std::string dir = "Tu vieja\n";


	switch (miDistrito) {
	case Demeter:
		dir += "001";
		break;
	case Hefesto:
		dir += "010";
		break;
	case Hestia:
		dir += "011";
		break;
	case Artemisa:
		dir += "100";
		break;
	case Hermes:
		dir += "101";
		break;
	case Apolo:
		dir += "110";
		break;
	case Poseidon:
		dir += "111";
		break;
	}
	dir += "\n";

	//habria que comprobar si la direccion tiene que ser correcta
	dir += distrito_calle[miDistrito][miCalle];

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
			distrito_calle[dist].reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto v : jValue->AsArray()) {
				if (v->IsString()) {
					std::string aux = v->AsString();
#ifdef _DEBUG
					std::cout << "Loading distrito with id: " << aux << std::endl;
#endif
					distrito_calle[dist].emplace_back(aux);
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

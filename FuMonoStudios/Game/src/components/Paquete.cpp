
#include "Paquete.h"
#include "../json/JSON.h"
#include <memory>
#include <iostream>
#include "../architecture/Entity.h"
#include "Render.h"
#include "../architecture/Scene.h"
#include <bitset>


// cleon: 962 gatitos acaban de morir. con dolor.
const int nivelFragil = 3;
const int nivelPeso = 2;
const int nivelSellos = 1;

const int desviacionPeso = 15;
const int ligeroMax = 25;
const int medioMax = 50;
const int pesadoMax = 75;

Paquete::Paquete(Paquete& otherPckg)
{
	miDistrito_ = otherPckg.miDistrito_;
	miCalle_ = otherPckg.miCalle_;
	miRemitente_ = otherPckg.miRemitente_;
	miTipo_ = otherPckg.miTipo_;
	selloCorrecto_ = otherPckg.selloCorrecto_;
	miPeso_ = otherPckg.miPeso_;
	peso_ = otherPckg.peso_;
	fragil_ = otherPckg.fragil_;
	carta_ = otherPckg.carta_;
	envuelto_ = otherPckg.envuelto_;
	calleMarcada_ = otherPckg.calleMarcada_;
	nombreCalle_ = otherPckg.nombreCalle_;
}

Paquete::Paquete(Distrito dis, Calle c, std::string remitente, TipoPaquete Tp, bool corr, NivelPeso Np, int p, 
	bool f, bool cart, std::string nombreCalle) :
	miDistrito_(dis), miCalle_(c), miRemitente_(remitente),miTipo_(Tp),selloCorrecto_(corr), 
	miPeso_(Np), peso_(p), fragil_(f), carta_(cart),envuelto_(false), calleMarcada_(Erronea), nombreCalle_(nombreCalle) {

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

	Vector2D posSellador = trSellador->getPos();
	// solo puedes sellar una vez 
	if (sello != Erronea && calleMarcada_ == Erronea)
	{
		calleMarcada_ = sello;
		Transform* paqTr = ent_->getComponent<Transform>();

		//Creamos la entidad sello
		ecs::Entity* selloEnt = ent_->getMngr()->addEntity(ecs::layer::STAMP);
		//Textura en funcion de tipo calle
		Texture* selloEntTex = &sdlutils().images().at(
			(std::string)"sello" += 
			(std::string)(sello == C1 ? "0" : sello == C2 ? "1" : "2"));

		//creamos transform y colocamos el sello en el centro del sellador
		float scale = 0.2f;
		Transform* selloEntTr = selloEnt->addComponent<Transform>
			(posSellador.getX() + selloEntTex->width() / 2 * scale - paqTr->getPos().getX(),
			posSellador.getY() + selloEntTex->height() / 2 * scale - paqTr->getPos().getY(),
			selloEntTex->width() * scale, selloEntTex->height() * scale);
		selloEnt->addComponent<RenderImage>(selloEntTex);
		selloEntTr->setParent(paqTr);
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

	dir += nombreCalle_;

	return dir;
}

void Paquete::giveData(std::ofstream& stream) const{
	stream << (int)miDistrito_ << "," << miRemitente_ << "," << (int)miCalle_<<"\n";
}


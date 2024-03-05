#include "PaqueteBuilder.h"
#include "../components/Transform.h"
#include "../architecture/Entity.h"
#include "../components/Render.h"
#include "../architecture/GameConstants.h"

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

std::string PaqueteBuilder::RemitenteRND() {
	
	// Falta crear un json/txt con todos los posibles nombres random
	// y asignar uno random

	return "Nombre Random";
}

void PaqueteBuilder::addVisualElements(ecs::Entity* paq) {
	Paquete* paqComp = paq->getComponent<Paquete>();

	//Creamos la entidad de dirección y remitente
	createVisualDirections(paq, paqComp);

	//Creamos la entidad Tipo sello 
	Paquete::TipoPaquete miTipo = paqComp->getTipo();
	std::string tipoString = (miTipo == Paquete::Alimento ? "selloAlimento" :
		miTipo == Paquete::Medicinas ? "selloMedicinas" :
		miTipo == Paquete::Joyas ? "selloJoyas" :
		miTipo == Paquete::Materiales ? "selloMateriales" :
		miTipo == Paquete::Armamento ? "selloArmamento" : "Desconocido");
	crearSello(paq, tipoString, tipoSelloPosX, tipoSelloPosY, tipoSelloSize, tipoSelloSize);

	//Creamos la entidad Peso sello 
	Paquete::NivelPeso miPeso = paqComp->getPeso();
	if (miPeso != Paquete::Ninguno) {
		tipoString = (miTipo == Paquete::Bajo ? "selloPesoBajo" :
			miTipo == Paquete::Medio ? "selloPesoMedio" :
			miTipo == Paquete::Alto ? "selloPesoAlto" : "selloPesoBajo");
		crearSello(paq, tipoString, pesoSelloPosX, pesoSelloPosY, pesoSelloSize, pesoSelloSize);
	}
	//Creamos la entidad Fragil sello 
	bool fragil = paqComp->getFragil();
	if (fragil) {
		crearSello(paq, "selloFragil", fragilSelloPosX, fragilSelloPosY, fragilSelloSize, fragilSelloSize);
	}
}

void PaqueteBuilder::createVisualDirections(ecs::Entity* paq, Paquete* paqComp) {
	// Texto distrito y calle
	ecs::Entity* distritoEnt = paq->getMngr()->addEntity(ecs::layer::STAMP);
	Texture* distritoTex = new Texture(sdlutils().renderer(), paqComp->getDirecction(), *directionsFont, build_sdlcolor(0x000000ff), 500);
	Transform* distritoTr = distritoEnt->addComponent<Transform>(10, 165, 200, 50);
	RenderImage* distritoRender = distritoEnt->addComponent<RenderImage>();
	distritoRender->setTexture(distritoTex);
	distritoTr->setParent(paq->getComponent<Transform>());

	// Texto remitente
	ecs::Entity* remitenteEnt = paq->getMngr()->addEntity(ecs::layer::STAMP);
	Texture* remitenteTex = new Texture(sdlutils().renderer(), "Rte: " + paqComp->getRemitente(), *directionsFont, build_sdlcolor(0x000000ff), 500);
	Transform* remitenteTr = remitenteEnt->addComponent<Transform>(10, 215, 150, 25);
	RenderImage* remitenteRender = remitenteEnt->addComponent<RenderImage>();
	remitenteRender->setTexture(remitenteTex);
	remitenteTr->setParent(paq->getComponent<Transform>());
}

void PaqueteBuilder::crearSello(ecs::Entity* paq, std::string texKey, int x, int y, int width, int height) {
	ecs::Entity* SelloEnt = paq->getMngr()->addEntity(ecs::layer::STAMP);
	Texture* SelloTex = &sdlutils().images().at(texKey);
	Transform* SelloTr = SelloEnt->addComponent<Transform>(x, y, width, height);
	SelloEnt->addComponent<RenderImage>(SelloTex);
	SelloTr->setParent(paq->getComponent<Transform>());
}

#include "PaqueteBuilder.h"
#include "../components/Transform.h"
#include "../architecture/Entity.h"
#include "../components/Render.h"
#include "../architecture/GameConstants.h"

Paquete::Distrito PaqueteBuilder::DistritoRND() {	//Este m�todo devuelve un Distrito aleatorio entre todas las posibilidades
	int rnd = sdlutils().rand().nextInt(0, 8);
	return (Paquete::Distrito)rnd;
}
Paquete::TipoPaquete PaqueteBuilder::TipoRND() {	//Este m�todo devuelve un Tipo de paquete aleatorio entre todas las posibilidades
	int rnd = sdlutils().rand().nextInt(0, 5);
	return (Paquete::TipoPaquete)rnd;
}
Paquete::Calle PaqueteBuilder::CalleRND(int probError) {	//Este m�todo devuelve una calle aleatoria de las posibilidades, con probabilidad de que salga un resultado err�neo
	int rnd = sdlutils().rand().nextInt(0, 101);
	if (rnd > probError) {
		rnd = sdlutils().rand().nextInt(0, 3);
		return (Paquete::Calle)rnd;
	}
	else {
		return Paquete::Calle::Erronea;
	}
}
bool PaqueteBuilder::BoolRND(int probFalse) { //Este m�todo devuelve una valor aleatorio entre treu y false para un bool seg�n una probabilidad
	int rnd = sdlutils().rand().nextInt(0, 101);
	if (rnd > probFalse) {
		return true;
	}
	else {
		return false;
	}
}
Paquete::NivelPeso PaqueteBuilder::PesoRND(int probPeso, int probError, int& peso) {	//Este m�todo elige aleatoriamente si colocar un sello de peso o no en el paquete y, en caso positivo,
	int rnd = sdlutils().rand().nextInt(0, 101);										//elige aleatoriamente si el resultado es correcto o incorrecto, devolviendo un peso para el paquete
	if (rnd > probPeso) {
		Paquete::NivelPeso pes;
		rnd = sdlutils().rand().nextInt(1, 4);
		pes = (Paquete::NivelPeso)rnd;

		rnd = sdlutils().rand().nextInt(0, 101);
		if (rnd > probError) {
			if (pes == Paquete::NivelPeso::Alto) {
				peso = sdlutils().rand().nextInt(medioMax, pesadoMax + 1);
			}
			else if (pes == Paquete::NivelPeso::Medio) {
				peso = sdlutils().rand().nextInt(ligeroMax, medioMax);
			}
			else if (pes == Paquete::NivelPeso::Bajo) {
				peso = sdlutils().rand().nextInt(paqueteMin, ligeroMax);
			}
		}
		else {
			if (pes == Paquete::NivelPeso::Alto) {
				peso = sdlutils().rand().nextInt(paqueteMin, medioMax); // o bajo o medio
			}
			else if (pes == Paquete::NivelPeso::Medio) {
				rnd = sdlutils().rand().nextInt(0, 2);
				if (rnd == 0) {
					peso = sdlutils().rand().nextInt(paqueteMin, ligeroMax); // bajo
				}
				else {
					peso = sdlutils().rand().nextInt(medioMax, pesadoMax + 1); // alto
				}
			}
			else if (pes == Paquete::NivelPeso::Bajo) {
				peso = sdlutils().rand().nextInt(ligeroMax, pesadoMax + 1); // o medio o alto
			}
		}
		return pes;
	}
	else {
		peso = sdlutils().rand().nextInt(paqueteMin, pesadoMax + 1);
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

	//Creamos la entidad de direcci�n y remitente
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
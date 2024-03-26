#include "PaqueteBuilder.h"
#include "../components/Transform.h"
#include "../architecture/Entity.h"
#include "../components/Render.h"
#include "../architecture/GameConstants.h"

PaqueteBuilder::PaqueteBuilder() {
	srand(sdlutils().currRealTime());
	directionsFont = new Font("recursos/fonts/ARIAL.ttf", 40);
}

PaqueteBuilder::~PaqueteBuilder() {
	delete directionsFont;
}


ecs::Entity* PaqueteBuilder::paqueteRND(int level, ecs::Scene* mScene) {
	ecs::Entity* ent = mScene->addEntity();
	
	bool continuar = true;
	if (generalData().areTherePaquetesNPC()) {
		int rnd = sdlutils().rand().nextInt(0, 4);
		if (rnd == 0) continuar = false;
	}

	int streetErrorChance, stampErrorChance = 0, notFragileChance = 100;
	int peso;
	Paquete::NivelPeso Nv;
	if (continuar) {
		if (level < 2) {
			Nv = Paquete::NivelPeso::Ninguno;
			peso = rand() % PESADO_MAX + 1;
			if (level == 0) {
				streetErrorChance = 10;
			}
			else if (level == 1) {
				streetErrorChance = 20;
				stampErrorChance = 35;
			}
		}
		else {
			stampErrorChance = 20;
			if (level == 2) {
				streetErrorChance = 15;
				Nv = pesoRND(25, 30, peso);
			}
			else if (level == 3) {
				streetErrorChance = 20;
				notFragileChance = 80;
				Nv = pesoRND(20, 25, peso);
			}
		}
		Paquete* pq = ent->addComponent<Paquete>(distritoRND(), calleRND(streetErrorChance), remitenteRND(), tipoRND(), boolRND(stampErrorChance), Nv, peso, 
			boolRND(notFragileChance), false);
		addVisualElements(ent);
	}
	else {
		paqueteNPC(ent);
	}
	return ent;
}

ecs::Entity* PaqueteBuilder::cartaRND(ecs::Scene* mScene) {
	ecs::Entity* ent = mScene->addEntity();
	ent->addComponent<Paquete>(distritoRND(), calleRND(20), remitenteRND(), tipoRND(), true, Paquete::NivelPeso::Ninguno, PESO_CARTA, false, true);
	return ent;
}

void PaqueteBuilder::paqueteNPC(ecs::Entity* ent) {
	Paquete* pNPC = generalData().getPaqueteNPC();
	Paquete* pq = ent->addComponent<Paquete>(*pNPC);
	if (!pNPC->isCarta()) addVisualElements(ent);
	//else addVisualElementsCarta(ent);
}

Paquete::Distrito PaqueteBuilder::distritoRND() {	//Este método devuelve un Distrito aleatorio entre todas las posibilidades
	//TO DO: Cambiarlo para que solo salgan distritos desbloqueados
	int rnd = sdlutils().rand().nextInt(0, 8);
	return (Paquete::Distrito)rnd;
}

Paquete::TipoPaquete PaqueteBuilder::tipoRND() {	//Este método devuelve un Tipo de paquete aleatorio entre todas las posibilidades
	int rnd = sdlutils().rand().nextInt(0, 5);
	return (Paquete::TipoPaquete)rnd;
}

Paquete::Calle PaqueteBuilder::calleRND(int probError) {	//Este método devuelve una calle aleatoria de las posibilidades, con probabilidad de que salga un resultado erróneo
	int rnd = sdlutils().rand().nextInt(0, 101);
	if (rnd > probError) {
		rnd = sdlutils().rand().nextInt(0, 3);
		return (Paquete::Calle)rnd;
	}
	else {
		return Paquete::Calle::Erronea;
	}
}

bool PaqueteBuilder::boolRND(int probFalse) { //Este método devuelve una valor aleatorio entre treu y false para un bool según una probabilidad
	int rnd = sdlutils().rand().nextInt(0, 101);
	if (rnd > probFalse) {
		return true;
	}
	else {
		return false;
	}
}

Paquete::NivelPeso PaqueteBuilder::pesoRND(int probPeso, int probError, int& peso) {	//Este método elige aleatoriamente si colocar un sello de peso o no en el paquete y, en caso positivo,
	int rnd = sdlutils().rand().nextInt(0, 101);										//elige aleatoriamente si el resultado es correcto o incorrecto, devolviendo un peso para el paquete
	if (rnd > probPeso) {
		Paquete::NivelPeso pes;
		rnd = sdlutils().rand().nextInt(1, 4);
		pes = (Paquete::NivelPeso)rnd;

		rnd = sdlutils().rand().nextInt(0, 101);
		if (rnd > probError) {
			if (pes == Paquete::NivelPeso::Alto) {
				peso = sdlutils().rand().nextInt(MEDIO_MAX, PESADO_MAX + 1);
			}
			else if (pes == Paquete::NivelPeso::Medio) {
				peso = sdlutils().rand().nextInt(LIGERO_MAX, MEDIO_MAX);
			}
			else if (pes == Paquete::NivelPeso::Bajo) {
				peso = sdlutils().rand().nextInt(PAQUETE_MIN, LIGERO_MAX);
			}
		}
		else {
			if (pes == Paquete::NivelPeso::Alto) {
				peso = sdlutils().rand().nextInt(PAQUETE_MIN, MEDIO_MAX); // o bajo o medio
			}
			else if (pes == Paquete::NivelPeso::Medio) {
				rnd = sdlutils().rand().nextInt(0, 2);
				if (rnd == 0) {
					peso = sdlutils().rand().nextInt(PAQUETE_MIN, LIGERO_MAX); // bajo
				}
				else {
					peso = sdlutils().rand().nextInt(MEDIO_MAX, PESADO_MAX + 1); // alto
				}
			}
			else if (pes == Paquete::NivelPeso::Bajo) {
				peso = sdlutils().rand().nextInt(LIGERO_MAX, PESADO_MAX + 1); // o medio o alto
			}
		}
		return pes;
	}
	else {
		peso = sdlutils().rand().nextInt(PAQUETE_MIN, PESADO_MAX + 1);
		return Paquete::NivelPeso::Ninguno;
	}
}

std::string PaqueteBuilder::remitenteRND() {
	
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
	crearSello(paq, tipoString, TIPO_SELLO_POS_X, TIPO_SELLO_POS_Y, TIPO_SELLO_SIZE, TIPO_SELLO_SIZE);

	//Creamos la entidad Peso sello 
	Paquete::NivelPeso miPeso = paqComp->getPeso();
	if (miPeso != Paquete::Ninguno) {
		tipoString = (miTipo == Paquete::Bajo ? "selloPesoBajo" :
			miTipo == Paquete::Medio ? "selloPesoMedio" :
			miTipo == Paquete::Alto ? "selloPesoAlto" : "selloPesoBajo");
		crearSello(paq, tipoString, PESO_SELLO_POS_X, PESO_SELLO_POS_Y, PESO_SELLO_SIZE, PESO_SELLO_SIZE);
	}
	//Creamos la entidad Fragil sello 
	bool fragil = paqComp->getFragil();
	if (fragil) {
		crearSello(paq, "selloFragil", FRAGIL_SELLO_POS_X, FRAGIL_SELLO_POS_Y, FRAGIL_SELLO_SIZE, FRAGIL_SELLO_SIZE);
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

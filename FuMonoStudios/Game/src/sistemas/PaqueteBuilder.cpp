#include "PaqueteBuilder.h"
#include "../components/Transform.h"
#include "../architecture/Entity.h"
#include "../components/Render.h"
#include "../architecture/GameConstants.h"
#include <sistemas/ComonObjectsFactory.h>
#include "../json/JSON.h"


PaqueteBuilder::PaqueteBuilder(ecs::Scene* sc):createdTextures(),mScene_(sc) {
	srand(sdlutils().currRealTime());
	directionsFont = &sdlutils().fonts().at("arial40");

	std::string filename = "recursos/config/mail.direcctions.json";
	getStreetsFromJSON(filename, Demeter, "Demeter");
	getStreetsFromJSON(filename, Hefesto, "Hefesto");
	getStreetsFromJSON(filename, Hestia, "Hestia");
	getStreetsFromJSON(filename, Artemisa, "Artemisa");
	getStreetsFromJSON(filename, Hermes, "Hermes");
	getStreetsFromJSON(filename, Apolo, "Apolo");
	getStreetsFromJSON(filename, Poseidon, "Poseidon");
}

PaqueteBuilder::~PaqueteBuilder() {
	for (Texture* t : createdTextures) {
		delete t;
	}
}


ecs::Entity* PaqueteBuilder::paqueteRND(int level, ecs::Scene* mScene) {
	
	auto packageBase = buildBasePackage(mScene);


	packageBase->getComponent<Trigger>()->addCallback([packageBase](ecs::Entity* entRec) {
		Herramientas* herrEnt = entRec->getComponent<Herramientas>();
		if (herrEnt != nullptr)
		{
			herrEnt->interact(packageBase);
		}
	});

	bool continuar = true;
	if (generalData().areTherePaquetesNPC()) {
		int rnd = sdlutils().rand().nextInt(0, 4);
		if (rnd == 0) continuar = false;
	}
	//se puede quedar como atributo de la clase si vemos que hace falta mayor velocidad en el juego
	DifficultySettings lvl1 = getLevelSetings(level);
	int peso;

	pq::NivelPeso Nv;
	if (continuar) {
		Nv = pesoRND(lvl1.weithChance,lvl1.weightErrorChance, peso);

		pq::Distrito toDist = distritoRND();
		pq::Calle toDir = calleRND(lvl1.streetErrorChance);
		std::string dir;
		if (toDir == Erronea)
			//Cambiarlo por el sistema de calles erróneas una vez esté
			//Simplemente sería meterlas en el mismo json, en el distrito erroneo y modificar el getStreetsFromJson
			//Y meterle un randomizador para que de esas pille la que más le guste
			//Tipo, haces distritoCalle_[Erroneo][rand]
			dir = "(CALLE INVENTADA)";
		else
			dir = distritoCalle_[toDist][(int)toDir];

		/*
		TODO hacer que la creacion del paquete vaya en funcion de la necsidad de los dias
		*/

		Paquete* pq = packageBase->addComponent<Paquete>(toDist, toDir,dir, remitenteRND(), tipoRND(), boolRND(lvl1.stampErrorChance), Nv, peso,
			boolRND(lvl1.notFragileChance), false);
		addVisualElements(packageBase);
		if (pq->getFragil()) {
			//Wrap debe ir despues del Transform, Trigger y Multitextures
			std::list<int> route{ pointRoute::LeftUp, pointRoute::MiddleUp, pointRoute::MiddleMid, pointRoute::MiddleDown, pointRoute::RightDown };
			packageBase->addComponent<Wrap>(20, 0, route);
		}
	}
	else {
		paqueteNPC(packageBase);
	}

	return packageBase;
}

ecs::Entity* PaqueteBuilder::cartaRND(ecs::Scene* mScene) {
	ecs::Entity* ent = mScene->addEntity();

	pq::Distrito toDist = distritoRND();
	pq::Calle toDir = calleRND(10);
	std::string dir;
	if (toDir == Erronea)
		//Cambiarlo por el sistema de calles erróneas una vez esté
		//Simplemente sería meterlas en el mismo json, en el distrito erroneo y modificar el getStreetsFromJson
		//Y meterle un randomizador para que de esas pille la que más le guste
		//Tipo, haces distritoCalle_[Erroneo][rand]
		dir = "(CALLE INVENTADA)";
	else
		dir = distritoCalle_[toDist][toDir];
	ent->addComponent<Paquete>(distritoRND(), calleRND(20),dir, remitenteRND(), tipoRND(), true, pq::NivelPeso::Ninguno, PESO_CARTA, false, true);
	return ent;
}

void PaqueteBuilder::paqueteNPC(ecs::Entity* ent) {
	Paquete* pNPC = generalData().getPaqueteNPC();
	Paquete* pq = ent->addComponent<Paquete>(*pNPC);
	if (!pNPC->isCarta()) addVisualElements(ent);
	//else addVisualElementsCarta(ent);
}

ecs::Entity* PaqueteBuilder::customPackage(pq::Distrito distrito, pq::Calle calle, const std::string& remitente, pq::TipoPaquete tipo, bool correcto, pq::NivelPeso nivPeso, int peso, bool fragil, bool carta)
{
	auto base = buildBasePackage(mScene_);
	base->addComponent<Paquete>(distrito,calle,"Tu vieja", remitente, tipo, correcto, nivPeso, peso, fragil, carta);
	addVisualElements(base);
	return base;
}

ecs::Entity* PaqueteBuilder::buildBasePackage(ecs::Scene* mScene)
{
	ComonObjectsFactory* factory = mScene->getFactory();

	Texture* texturaPaquet = &sdlutils().images().at("boxTest");
	//ENVOLTURA
	//se puede rellenar con un for
	std::vector<Texture*> textures = {
		texturaPaquet,
		&sdlutils().images().at("caja25"),
		&sdlutils().images().at("caja50"),
		&sdlutils().images().at("caja75"),
		&sdlutils().images().at("caja100")
	};
	auto packageBase = factory->createMultiTextureImage(Vector2D(1600.0f, 600.0f), Vector2D(320.5f, 245.5), textures);

	packageBase->addComponent<Depth>();
	packageBase->addComponent<Gravity>();
	DragAndDrop* drgPq = packageBase->addComponent<DragAndDrop>(true);
	return packageBase;
}

pq::Distrito PaqueteBuilder::distritoRND() {	//Este método devuelve un Distrito aleatorio entre todas las posibilidades
	//TO DO: Cambiarlo para que solo salgan distritos desbloqueados
	int rnd = sdlutils().rand().nextInt(0, 8);
	return (pq::Distrito)rnd;
}

pq::TipoPaquete PaqueteBuilder::tipoRND() {	//Este método devuelve un Tipo de paquete aleatorio entre todas las posibilidades
	int rnd = sdlutils().rand().nextInt(0, 5);
	return (pq::TipoPaquete)rnd;
}

pq::Calle PaqueteBuilder::calleRND(int probError) {	//Este método devuelve una calle aleatoria de las posibilidades, con probabilidad de que salga un resultado erróneo
	int rnd = sdlutils().rand().nextInt(0, 101);
	if (rnd > probError) {
		rnd = sdlutils().rand().nextInt(0, 3);
		return (pq::Calle)rnd;
	}
	else {
		return pq::Calle::Erronea;
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

pq::NivelPeso PaqueteBuilder::pesoRND(int probPeso, int probError, int& peso) {	//Este método elige aleatoriamente si colocar un sello de peso o no en el paquete y, en caso positivo,
	int rnd = sdlutils().rand().nextInt(0, 101);										//elige aleatoriamente si el resultado es correcto o incorrecto, devolviendo un peso para el paquete
	if (rnd > probPeso) {
		pq::NivelPeso pes;
		rnd = sdlutils().rand().nextInt(1, 4);
		pes = (pq::NivelPeso)rnd;

		rnd = sdlutils().rand().nextInt(0, 101);
		if (rnd > probError) {
			if (pes == pq::NivelPeso::Alto) {
				peso = sdlutils().rand().nextInt(MEDIO_MAX, PESADO_MAX + 1);
			}
			else if (pes == pq::NivelPeso::Medio) {
				peso = sdlutils().rand().nextInt(LIGERO_MAX, MEDIO_MAX);
			}
			else if (pes == pq::NivelPeso::Bajo) {
				peso = sdlutils().rand().nextInt(PAQUETE_MIN, LIGERO_MAX);
			}
		}
		else {
			if (pes == pq::NivelPeso::Alto) {
				peso = sdlutils().rand().nextInt(PAQUETE_MIN, MEDIO_MAX); // o bajo o medio
			}
			else if (pes == pq::NivelPeso::Medio) {
				rnd = sdlutils().rand().nextInt(0, 2);
				if (rnd == 0) {
					peso = sdlutils().rand().nextInt(PAQUETE_MIN, LIGERO_MAX); // bajo
				}
				else {
					peso = sdlutils().rand().nextInt(MEDIO_MAX, PESADO_MAX + 1); // alto
				}
			}
			else if (pes == pq::NivelPeso::Bajo) {
				peso = sdlutils().rand().nextInt(LIGERO_MAX, PESADO_MAX + 1); // o medio o alto
			}
		}
		return pes;
	}
	else {
		peso = sdlutils().rand().nextInt(PAQUETE_MIN, PESADO_MAX + 1);
		return pq::NivelPeso::Ninguno;
	}
}

std::string PaqueteBuilder::remitenteRND() {
	
	// Falta crear un json/txt con todos los posibles nombres random
	// y asignar uno random

	return "Nombre Random";
}

void PaqueteBuilder::getStreetsFromJSON(const std::string& filename, Distrito dist, const std::string& distString)
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

PaqueteBuilder::DifficultySettings PaqueteBuilder::getLevelSetings(int lvl)
{
	DifficultySettings diff;
	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(DIFF_SETTINGS_PATH));

	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing '" + DIFF_SETTINGS_PATH + "'";
	}

	JSONObject root = jValueRoot->AsObject();
	JSONObject lvlObj = root["lvl"+std::to_string(lvl)]->AsObject();

	diff.streetErrorChance = lvlObj["streetErrorChance"]->AsNumber();
	diff.stampErrorChance = lvlObj["stampErrorChance"]->AsNumber();
	diff.weithChance = lvlObj["weightChance"]->AsNumber();
	diff.weightErrorChance = lvlObj["weightErrorChance"]->AsNumber();
	diff.notFragileChance = lvlObj["notFragileChance"]->AsNumber();

	return diff;
}


void PaqueteBuilder::addVisualElements(ecs::Entity* paq) {
	Paquete* paqComp = paq->getComponent<Paquete>();

	//Creamos la entidad de dirección y remitente
	createVisualDirections(paq, paqComp);

	//Creamos la entidad Tipo sello 
	pq::TipoPaquete miTipo = paqComp->getTipo();
	std::string tipoString = (miTipo == pq::Alimento ? "selloAlimento" :
		miTipo == pq::Medicinas ? "selloMedicinas" :
		miTipo == pq::Joyas ? "selloJoyas" :
		miTipo == pq::Materiales ? "selloMateriales" :
		miTipo == pq::Armamento ? "selloArmamento" : "Desconocido");
	crearSello(paq, tipoString, TIPO_SELLO_POS_X, TIPO_SELLO_POS_Y, TIPO_SELLO_SIZE, TIPO_SELLO_SIZE);

	//Creamos la entidad Peso sello 
	pq::NivelPeso miPeso = paqComp->getPeso();
	if (miPeso != pq::Ninguno) {
		tipoString = (miTipo == pq::Bajo ? "selloPesoBajo" :
			miTipo == pq::Medio ? "selloPesoMedio" :
			miTipo == pq::Alto ? "selloPesoAlto" : "selloPesoBajo");
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
	createdTextures.push_back(distritoTex);
	Transform* distritoTr = distritoEnt->addComponent<Transform>(10, 165, 200, 50);
	RenderImage* distritoRender = distritoEnt->addComponent<RenderImage>();
	distritoRender->setTexture(distritoTex);
	distritoTr->setParent(paq->getComponent<Transform>());

	// Texto remitente
	ecs::Entity* remitenteEnt = paq->getMngr()->addEntity(ecs::layer::STAMP);
	Texture* remitenteTex = new Texture(sdlutils().renderer(), "Rte: " + paqComp->getRemitente(), *directionsFont, build_sdlcolor(0x000000ff), 500);
	createdTextures.push_back(remitenteTex);
	Transform* remitenteTr = remitenteEnt->addComponent<Transform>(10, 215, 150, 25);
	RenderImage* remitenteRender = remitenteEnt->addComponent<RenderImage>();
	remitenteRender->setTexture(remitenteTex);
	remitenteTr->setParent(paq->getComponent<Transform>());
}

void PaqueteBuilder::crearSello(ecs::Entity* paq,const std::string& texKey, int x, int y, int width, int height) {
	ecs::Entity* SelloEnt = paq->getMngr()->addEntity(ecs::layer::STAMP);
	Texture* SelloTex = &sdlutils().images().at(texKey);
	Transform* SelloTr = SelloEnt->addComponent<Transform>(x, y, width, height);
	SelloEnt->addComponent<RenderImage>(SelloTex);
	SelloTr->setParent(paq->getComponent<Transform>());
}

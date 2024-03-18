#pragma once
#include "../components/Paquete.h"
#include "../architecture/Entity.h"
#include <stdlib.h>
#include "../sdlutils/VirtualTimer.h"
#include "../architecture/GeneralData.h"
#include "../components/MoverTransform.h"



const int PESADO_MAX = 75;	//Límite del peso máximo de paquetes pesados 
const int MEDIO_MAX = 50;	//Límite del peso máximo de paquetes de peso medio 
const int LIGERO_MAX = 25;	//Límite del peso máximo de paquetes ligeros
const int PAQUETE_MIN = 10;	//Límite del peso mínimo de paquetes ligeros
const int PESO_CARTA = 2;	//Peso carta

// Miguel: En el futuro haremos que salgan un poco desviados de su
// posición original para que parezcan más orgánicos los paquetes
// posicion y tama�o Tipo sellos
const Vector2D TIPO_SELLO_POS = Vector2D(10, 60);
const double TIPO_SELLO_SIZE = 0.2;
// posicion y tama�o Fragil sellos
const Vector2D FRAGIL_SELLO_POS = Vector2D(150, 150);
const double FRAGIL_SELLO_SIZE = 0.2;
// posicion y tama�o Peso sellos
const Vector2D PESO_SELLO_POS = Vector2D(100, 20);
const double PESO_SELLO_SIZE = 0.2;

class PaqueteBuilder
{
public:
	//Método al que se llama que devuelve un Paquete generado aleatoriamente 
	void paqueteRND(int level, ecs::Entity* ent) {
		bool continuar = true;
		if (generalData().areTherePaquetesNPC()) {
			int rnd = sdlutils().rand().nextInt(0, 4);
			if (rnd == 0) continuar = false;
		}

		if (continuar) {
			if (level == 0) {
				nivel0(ent);
			}
			else if (level == 1) {
				nivel1(ent);
			}
			else if (level == 2) {
				nivel2(ent);
			}
			else if (level == 3) {
				nivel3(ent);
			}
		}
		else {
			paqueteNPC(ent);
		}
	}
	//Método al que se llama que devuelve una Carta generada aleatoriamente 
	Paquete* cartaRND(ecs::Entity* ent) {
		carta(ent);
	}
	//Añade sello de calle, comprueba si es paquete
	void crearSelloCalle(ecs::Entity* ent, enum Paquete::Calle nuestraCalle, Vector2D pos) {
		if (ent->getComponent<Paquete>() != nullptr) {

			//Textura en funcion de tipo calle
			Texture* selloTex = &sdlutils().images().at(
				(std::string)"sello" +=
				(std::string)(nuestraCalle == Paquete::C1 ? "A" : nuestraCalle == Paquete::C2 ? "B" : "C"));

			//Ajustamos la posicion con respecto a la textura del sello
			pos = Vector2D(pos.getX() - selloTex->width() / 2 * PESO_SELLO_SIZE, pos.getY() - selloTex->height() / 2 * PESO_SELLO_SIZE);

			//Creamos sello
			crearSello(ent, selloTex, pos, PESO_SELLO_SIZE);
		}
	}
	//Añade sello de peso
	void crearSelloPesado(ecs::Entity* ent, enum Paquete::NivelPeso nuestroPeso) {
		if (ent->getComponent<Paquete>() != nullptr) {
			//Creamos la entidad Peso sello 
			if (nuestroPeso != Paquete::Ninguno) {
				Texture* selloTex = &sdlutils().images().at(nuestroPeso == Paquete::Bajo ? "selloPesoBajo" :
					nuestroPeso == Paquete::Medio ? "selloPesoMedio" :
					nuestroPeso == Paquete::Alto ? "selloPesoAlto" : "selloPesoBajo");
				crearSello(ent, selloTex, PESO_SELLO_POS, PESO_SELLO_SIZE);
			}
		}
	}

	static PaqueteBuilder* getInstance() {
		if (!instance) {
			instance = new PaqueteBuilder();
		}
		return instance;
	}

private:
	static PaqueteBuilder* instance;

	PaqueteBuilder() {
		srand(sdlutils().currRealTime());
		directionsFont = new Font("recursos/fonts/ARIAL.ttf", 40);
	};
	void nivel0(ecs::Entity* ent) {	//Un paquete que no tiene ni sellos normales, de peso o de fragil, y solo puede tener calles err�neas
		Paquete* pq = ent->addComponent<Paquete>(distritoRND(), calleRND(20), remitenteRND(), tipoRND(), true, Paquete::NivelPeso::Ninguno, rand() % PESADO_MAX + 1, false, false);
		addVisualElements(ent);
	}
	void nivel1(ecs::Entity* ent) {	//Un paquete que no tiene ni sellos de peso ni sello de fragil, y puede tener tanto calles como sellos de tipo erróneos
		Paquete* pq = ent->addComponent<Paquete>(distritoRND(), calleRND(20), remitenteRND(), tipoRND(), boolRND(35), Paquete::NivelPeso::Ninguno, rand() % PESADO_MAX + 1, false, false);
		addVisualElements(ent);
	}
	void nivel2(ecs::Entity* ent) { //Un paquete que no tiene sello de fragil, pero puede tener sellos de peso, así como calles erróneas y sellos de tipo erróneos
		int peso;
		Paquete::NivelPeso Nv = pesoRND(25, 30, peso);
		Paquete* pq = ent->addComponent<Paquete>(distritoRND(), calleRND(15), remitenteRND(), tipoRND(), boolRND(20), Nv, peso, false, false);
		addVisualElements(ent);
	}
	void nivel3(ecs::Entity* ent) { //Un paquete que puede tener peso, sellos de frágil, calles erróneas y sellos de tipo erróneos
		int peso;
		Paquete::NivelPeso Nv = pesoRND(20, 25, peso);
		Paquete* pq = ent->addComponent<Paquete>(distritoRND(), calleRND(15), remitenteRND(), tipoRND(), boolRND(20), Nv, peso, boolRND(80), false);
		addVisualElements(ent);
	}
	void carta(ecs::Entity* ent) {	//Una carta, que en esencia funciona igual que un paquete de nivel 0
		Paquete* pq = ent->addComponent<Paquete>(distritoRND(), calleRND(20), remitenteRND(), tipoRND(), true, Paquete::NivelPeso::Ninguno, PESO_CARTA, false, true);
		//addVisualElementsCarta(ent);
	}
	void paqueteNPC(ecs::Entity* ent) {	//Una carta, que en esencia funciona igual que un paquete de nivel 0
		Paquete pNPC = generalData().getPaqueteNPC();
		Paquete* pq = ent->addComponent<Paquete>(pNPC.getDistrito(), pNPC.getCalle(), pNPC.getRemitente(), pNPC.getTipo(), pNPC.getSelloCorrecto(), pNPC.getPeso(), pNPC.getCantidadPeso(), pNPC.getFragil(), pNPC.isCarta());
		if(!pNPC.isCarta()) addVisualElements(ent);
		//else addVisualElementsCarta(ent);
	}


	Paquete::Distrito distritoRND();	//Método que elige un distrito aleatorio de los que hay
	Paquete::TipoPaquete tipoRND();		//Método que elige un tipo de paquete aleatorio entre los que hay
	Paquete::Calle calleRND(int probError);	//Método que elige una calle aleatoria de las posibilidades. El valor probError es, sobre 100, la probabilidad de que sea una calle incorrecta
	bool boolRND(int probFalse);		//Método que genera un bool con valor aleatorio entre true y false. El valor probFalse es, sobre 100, la probabilidad de que sea false
	Paquete::NivelPeso pesoRND(int probPeso, int probError, int& peso);	//Método que elige si un paquete tiene peso, y si es erróneo, devolviendo un peso para el paquete con la variable "peso"
	std::string remitenteRND();			//Método que elige un nombre random de Remitente

	// Se llama a este después de crear el paquete
	void addVisualElements(ecs::Entity* paq);
	// coge el paquete recien creado y le añade el componente visual de dirección
	void createVisualDirections(ecs::Entity* paq, Paquete* paqComp);
	// coge el paquete recien creado y le añade el componente visual de sello
	void crearSello(ecs::Entity* paq, Texture* tex, Vector2D pos, double scaleFactor);

	// esto hay que cambiarlo de sitio, al scene o algo
	Font* directionsFont;

};

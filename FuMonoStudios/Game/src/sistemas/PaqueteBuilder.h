#pragma once
#include "../components/Paquete.h"
#include "../architecture/Entity.h"
#include <stdlib.h>
#include "../sdlutils/VirtualTimer.h"


const int pesadoMax = 75;	//Límite del peso máximo de paquetes pesados 
const int medioMax = 50;	//Límite del peso máximo de paquetes de peso medio 
const int ligeroMax = 25;	//Límite del peso máximo de paquetes ligeros
const int paqueteMin = 10;	//Límite del peso mínimo de paquetes ligeros
const int pesoCarta = 2;	//Peso carta

// Miguel: En el futuro haremos que salgan un poco desviados de su
// posición original para que parezcan más orgánicos los paquetes
// posicion y tama�o Tipo sellos
const int tipoSelloPosX = 20;
const int tipoSelloPosY = 80;
const int tipoSelloSize = 80;
// posicion y tama�o Fragil sellos
const int fragilSelloPosX = 150;
const int fragilSelloPosY = 150;
const int fragilSelloSize = 80;
// posicion y tama�o Peso sellos
const int pesoSelloPosX = 200;
const int pesoSelloPosY = 200;
const int pesoSelloSize = 80;

class PaqueteBuilder
{
private:
	void Nivel0(ecs::Entity* ent) {	//Un paquete que no tiene ni sellos normales, de peso o de fragil, y solo puede tener calles err�neas
		Paquete* pq = ent->addComponent<Paquete>(DistritoRND(), CalleRND(20), RemitenteRND(), TipoRND(), true, Paquete::NivelPeso::Ninguno, rand() % pesadoMax + 1, false, false);
		addVisualElements(ent);
	}
	void Nivel1(ecs::Entity* ent) {	//Un paquete que no tiene ni sellos de peso ni sello de fragil, y puede tener tanto calles como sellos de tipo erróneos
		Paquete* pq = ent->addComponent<Paquete>(DistritoRND(), CalleRND(20), RemitenteRND(), TipoRND(), BoolRND(35), Paquete::NivelPeso::Ninguno, rand() % pesadoMax + 1, false, false);
		addVisualElements(ent);
	}
	void Nivel2(ecs::Entity* ent) { //Un paquete que no tiene sello de fragil, pero puede tener sellos de peso, así como calles erróneas y sellos de tipo erróneos
		int peso;
		Paquete::NivelPeso Nv = PesoRND(25, 30, peso);
		Paquete* pq = ent->addComponent<Paquete>(DistritoRND(), CalleRND(15), RemitenteRND(), TipoRND(), BoolRND(20), Nv, peso, false, false);
		addVisualElements(ent);
	}
	void Nivel3(ecs::Entity* ent) { //Un paquete que puede tener peso, sellos de frágil, calles erróneas y sellos de tipo erróneos
		int peso;
		Paquete::NivelPeso Nv = PesoRND(20, 25, peso);
		Paquete* pq = ent->addComponent<Paquete>(DistritoRND(), CalleRND(15), RemitenteRND(), TipoRND(), BoolRND(20), Nv, peso, BoolRND(80), false);
		addVisualElements(ent);
	}
	void Carta(ecs::Entity* ent) {	//Una carta, que en esencia funciona igual que un paquete de nivel 0
		Paquete* pq = ent->addComponent<Paquete>(DistritoRND(), CalleRND(20), RemitenteRND(), TipoRND(), true, Paquete::NivelPeso::Ninguno, pesoCarta, false, true);
		//addVisualElementsCarta(ent);
	}

	Paquete::Distrito DistritoRND();	//Método que elige un distrito aleatorio de los que hay
	Paquete::TipoPaquete TipoRND();		//Método que elige un tipo de paquete aleatorio entre los que hay
	Paquete::Calle CalleRND(int probError);	//Método que elige una calle aleatoria de las posibilidades. El valor probError es, sobre 100, la probabilidad de que sea una calle incorrecta
	bool BoolRND(int probFalse);		//Método que genera un bool con valor aleatorio entre true y false. El valor probFalse es, sobre 100, la probabilidad de que sea false
	Paquete::NivelPeso PesoRND(int probPeso, int probError, int& peso);	//Método que elige si un paquete tiene peso, y si es erróneo, devolviendo un peso para el paquete con la variable "peso"
	std::string RemitenteRND();			//Método que elige un nombre random de Remitente

	// Se llama a este después de crear el paquete
	void addVisualElements(ecs::Entity* paq);
	// coge el paquete recien creado y le añade el componente visual de dirección
	void createVisualDirections(ecs::Entity* paq, Paquete* paqComp);
	// coge el paquete recien creado y le añade el componente visual de sello
	void crearSello(ecs::Entity* paq, std::string texKey, int x, int y, int width, int height);

	// esto hay que cambiarlo de sitio, al scene o algo
	Font* directionsFont;
public:
	//Método al que se llama que devuelve un Paquete generado aleatoriamente 
	void PaqueteRND(int level, ecs::Entity* ent) {

		if (level == 0) {
			Nivel0(ent);
		}
		else if (level == 1) {
			Nivel1(ent);
		}
		else if (level == 2) {
			Nivel2(ent);
		}
		else if (level == 3) {
			Nivel3(ent);
		}
	}
	//Método al que se llama que devuelve una Carta generada aleatoriamente 
	Paquete* CartaRND(ecs::Entity* ent) {
		Carta(ent);
	}
	PaqueteBuilder() { 
		srand(sdlutils().currRealTime()); 
		directionsFont = new Font("recursos/fonts/ARIAL.ttf", 40);
	};
};

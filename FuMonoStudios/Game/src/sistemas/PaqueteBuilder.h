#pragma once
#include "../components/Paquete.h"
#include "../architecture/Entity.h"
#include <stdlib.h>
#include "../sdlutils/VirtualTimer.h"
#include "../architecture/GeneralData.h"
#include "../components/MultipleTextures.h"
#include "../components/Wrap.h"
#include "../components/Gravity.h"
#include "../components/Depth.h"
#include "../components/Trigger.h"
#include "../components/Herramientas.h"
#include "../components/MoverTransform.h"


const int PESADO_MAX = 75;	//Límite del peso máximo de paquetes pesados 
const int MEDIO_MAX = 50;	//Límite del peso máximo de paquetes de peso medio 
const int LIGERO_MAX = 25;	//Límite del peso máximo de paquetes ligeros
const int PAQUETE_MIN = 10;	//Límite del peso mínimo de paquetes ligeros
const int PESO_CARTA = 2;	//Peso carta

// Miguel: En el futuro haremos que salgan un poco desviados de su
// posición original para que parezcan más orgánicos los paquetes
// posicion y tama�o Tipo sellos
const int TIPO_SELLO_POS_X = 20;
const int TIPO_SELLO_POS_Y = 80;
const int TIPO_SELLO_SIZE = 80;
// posicion y tama�o Fragil sellos
const int FRAGIL_SELLO_POS_X = 150;
const int FRAGIL_SELLO_POS_Y = 150;
const int FRAGIL_SELLO_SIZE = 80;
// posicion y tama�o Peso sellos
const int PESO_SELLO_POS_X = 200;
const int PESO_SELLO_POS_Y = 200;
const int PESO_SELLO_SIZE = 80;

//Escala del paquete 
const float PAQUETE_SIZE = 0.25f;

class PaqueteBuilder
{
public:
	//Método al que se llama que devuelve un Paquete generado aleatoriamente 
	ecs::Entity* paqueteRND(int level, ecs::Scene*);
	//Método al que se llama que devuelve una Carta generada aleatoriamente 
	ecs::Entity* cartaRND(ecs::Scene*);

	void paqueteNPC(ecs::Entity*);

	PaqueteBuilder();

	~PaqueteBuilder();

private:
	ecs::Entity* buildBasePackage(ecs::Scene* mScene);
	pq::Distrito distritoRND();	//Método que elige un distrito aleatorio de los que hay
	pq::TipoPaquete tipoRND();		//Método que elige un tipo de paquete aleatorio entre los que hay
	pq::Calle calleRND(int probError);	//Método que elige una calle aleatoria de las posibilidades. El valor probError es, sobre 100, la probabilidad de que sea una calle incorrecta
	bool boolRND(int probFalse);		//Método que genera un bool con valor aleatorio entre true y false. El valor probFalse es, sobre 100, la probabilidad de que sea false
	pq::NivelPeso pesoRND(int probPeso, int probError, int& peso);	//Método que elige si un paquete tiene peso, y si es erróneo, devolviendo un peso para el paquete con la variable "peso"
	std::string remitenteRND();			//Método que elige un nombre random de Remitente

	// Se llama a este después de crear el paquete
	void addVisualElements(ecs::Entity* paq);
	// coge el paquete recien creado y le añade el componente visual de dirección
	void createVisualDirections(ecs::Entity* paq, Paquete* paqComp);
	// coge el paquete recien creado y le añade el componente visual de sello
	void crearSello(ecs::Entity* paq, std::string texKey, int x, int y, int width, int height);

	// esto hay que cambiarlo de sitio, al scene o algo
	Font* directionsFont;

	std::vector<Texture*> createdTextures;
};

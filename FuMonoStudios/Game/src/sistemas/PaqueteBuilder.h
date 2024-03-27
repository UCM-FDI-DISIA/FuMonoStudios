#pragma once
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
#include <components/Paquete.h>


constexpr int PESADO_MAX = 75;	//Límite del peso máximo de paquetes pesados 
constexpr int MEDIO_MAX = 50;	//Límite del peso máximo de paquetes de peso medio 
constexpr int LIGERO_MAX = 25;	//Límite del peso máximo de paquetes ligeros
constexpr int PAQUETE_MIN = 10;	//Límite del peso mínimo de paquetes ligeros
constexpr int PESO_CARTA = 2;	//Peso carta

// Miguel: En el futuro haremos que salgan un poco desviados de su
// posición original para que parezcan más orgánicos los paquetes
// posicion y tama�o Tipo sellos
constexpr int TIPO_SELLO_POS_X = 20;
constexpr int TIPO_SELLO_POS_Y = 80;
constexpr int TIPO_SELLO_SIZE = 80;
// posicion y tama�o Fragil sellos
constexpr int FRAGIL_SELLO_POS_X = 150;
constexpr int FRAGIL_SELLO_POS_Y = 150;
constexpr int FRAGIL_SELLO_SIZE = 80;
// posicion y tama�o Peso sellos
constexpr int PESO_SELLO_POS_X = 200;
constexpr int PESO_SELLO_POS_Y = 200;
constexpr int PESO_SELLO_SIZE = 80;

//Escala del paquete 
constexpr float PAQUETE_SIZE = 0.25f;

const std::string DIFF_SETTINGS_PATH = "recursos/config/mail.dificulty.json";

class PaqueteBuilder
{
public:
	//Método al que se llama que devuelve un Paquete generado aleatoriamente 
	ecs::Entity* buildPackage(int level, ecs::Scene*);
	//Método al que se llama que devuelve una Carta generada aleatoriamente 
	ecs::Entity* cartaRND(ecs::Scene*);



	ecs::Entity* customPackage(pq::Distrito, pq::Calle, const std::string& remitente, pq::TipoPaquete, bool correcto = true, 
		pq::NivelPeso nivPeso = pq::Ninguno, int peso = 0,
		bool fragil = false, bool carta = false);

	PaqueteBuilder(ecs::Scene*);

	~PaqueteBuilder();

private:
	typedef struct {
		int streetErrorChance;
		int stampErrorChance;
		int weithChance;
		int weightErrorChance;
		int notFragileChance;
	}DifficultySettings;



	ecs::Entity* buildBasePackage(ecs::Scene* mScene);
	void stdRandPackage(ecs::Entity*, int);
	void paqueteNPC(ecs::Entity*);
	/// <summary>
	/// determina si se debe crear un paquete de nPC
	/// </summary>
	/// <returns></returns>
	bool shouldBuildNPCPackage();

	pq::Distrito distritoRND();	//Método que elige un distrito aleatorio de los que hay
	pq::TipoPaquete tipoRND();		//Método que elige un tipo de paquete aleatorio entre los que hay
	pq::Calle calleRND(int probError);	//Método que elige una calle aleatoria de las posibilidades. El valor probError es, sobre 100, la probabilidad de que sea una calle incorrecta
	bool boolRND(int probFalse);		//Método que genera un bool con valor aleatorio entre true y false. El valor probFalse es, sobre 100, la probabilidad de que sea false
	pq::NivelPeso pesoRND(int probPeso, int probError, int& peso);	//Método que elige si un paquete tiene peso, y si es erróneo, devolviendo un peso para el paquete con la variable "peso"
	std::string remitenteRND();			//Método que elige un nombre random de Remitente

	/// <summary>
	/// Funcion auxiliar para cargar en el mapa las direcciones
	/// </summary>
	/// <param name="filename">direccion del fichero json</param>
	/// <param name="dist">valor enum del distritio al que pertenece</param>
	/// <param name="distString">valor string del distrito al que pertenece</param>
	void getStreetsFromJSON(const std::string& filename, Distrito dist,const std::string& distString);

	DifficultySettings getLevelSetings(int lvl);

	// Se llama a este después de crear el paquete
	void addVisualElements(ecs::Entity* paq);
	// coge el paquete recien creado y le añade el componente visual de dirección
	void createVisualDirections(ecs::Entity* paq, Paquete* paqComp);
	// coge el paquete recien creado y le añade el componente visual de sello
	void crearSello(ecs::Entity* paq, const std::string& texKey, int x, int y, int width, int height);

	// esto hay que cambiarlo de sitio, al scene o algo
	Font* directionsFont;

	std::vector<Texture*> createdTextures;

	ecs::Scene* mScene_;

	/*
	*TODO: Meter estos datos en el paquete builder
	*/
	/// <summary>
	/// mapa que relaciona cada distrito con su calle
	/// usado para la generacion del string de la direccion
	/// </summary>
	std::unordered_map<Distrito, std::vector<std::string>> distritoCalle_;
};

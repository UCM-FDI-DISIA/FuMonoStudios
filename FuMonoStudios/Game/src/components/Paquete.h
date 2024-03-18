#pragma once

#include "../architecture/Component.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "../utils/Vector2D.h"
#include "Transform.h"

class Scene;

class Paquete : public ecs::Component
{
public:
	__CMP_DECL__(ecs::cmp::PAQUETE)
		

	/*
	De locos pero y si lo metemos en un espacio de nombres
	*/
	/// <summary>
	/// enum con todos los distritos posibles que pueden tener los paquetes
	/// </summary>
	enum Distrito {Hestia, Hefesto, Demeter, Artemisa, Hermes, Apolo, Poseidon, Erroneo };
	/// <summary>
	/// enum con todas las calles posibles que pueden tener los paquetes
	/// </summary>
	enum Calle { C1, C2, C3, Erronea };
	/// <summary>
	/// enum con todoos los tipos de cargamento que pueden tener los paquetes
	/// </summary>
	enum TipoPaquete { Alimento,Medicinas,Joyas,Materiales,Armamento };
	/// <summary>
	/// enum con todas los tipos de medici�n de peso que pueden tener los paquetes
	/// </summary>
	enum NivelPeso { Ninguno, Bajo, Medio, Alto };



	Paquete(Distrito, Calle, std::string remitente, TipoPaquete, bool correcto = true, NivelPeso nivPeso = Ninguno, int peso = 0, bool fragil = false, bool carta = false);
	~Paquete();

	void initComponent() override;
	bool correcto() const;		//Bool que comprueba si el paquete tiene errores (falsificaciones, calles incorrectas...)
	bool bienSellado() const;

	// Sella la calle una única vez con el sellador
	void sellarCalle(Calle sello, Transform* trSellador);
	// Sella el peso
	void sellarPeso(Transform* trBalanza);
	/// <summary>
	/// metodo que devuelve el string a implimir en la etiqueta de direccion
	/// </summary>
	/// <returns></returns>
	std::string getDirecction();
	TipoPaquete getTipo() const { return miTipo_; }
	Distrito getDistrito() const { return miDistrito_; }
	Calle getCalle() const { return miCalle_; }
	std::string getRemitente() const { return miRemitente_; }
	NivelPeso getPeso() const { return miPeso_; }
	int getCantidadPeso() const { return peso_; }
	bool getFragil() const { return fragil_; }
	bool getSelloCorrecto() const { return selloCorrecto_; }
	bool isCarta() const { return carta_; }

private:
	/// <summary>
	/// Funcion auxiliar para cargar en el mapa las direcciones
	/// </summary>
	/// <param name="filename">direccion del fichero json</param>
	/// <param name="dist">valor enum del distritio al que pertenece</param>
	/// <param name="distString">valor string del distrito al que pertenece</param>
	void getStreetsFromJSON(std::string filename, Distrito dist, std::string distString);
	//void createSello(std::string texKey, int x, int y, int width, int height); (movido al paqueteBuilder)

	/*
	*TODO: Meter estos datos en el paquete builder
	*/
	/// <summary>
	/// mapa que relaciona cada distrito con su calle
	/// usado para la generacion del string de la direccion
	/// </summary>
	std::unordered_map<Distrito, std::vector<std::string>> distritoCalle_;
	//Variables que se generan automaticamente con informaci�n de los paquetes
	Distrito miDistrito_;	//Variable con el distrito al que es enviado el paquete	
	std::string miRemitente_;  //Variable con el nombre del remitente
	Calle miCalle_;			//Variable con la calle a la que es enviada el paquete	
	TipoPaquete miTipo_;		//Variable con el tipo de cargamente que lleva el paquete
	bool selloCorrecto_;		//Variable que indica si el sello que contiene el paquete es correcto o no
	NivelPeso miPeso_;		//Variable que indica qu� peso esta marcado en el paquete, o si este peso ni siquera est� marcado
	int peso_;				//Variable que indica cuanto pesa el paquete para mostrar en la balanza
	bool fragil_;			//Variable que indica si tiene un sello de fr�gil puesto

	//Bool que indica si el paquete es en realidad una carta, y si debe ser representado como tal en el renderizado
	bool carta_;

	//Variables que debe modificar el jugador
	Calle calleMarcada_;		//Variable que indica para qu� distrito ha sido etiquetado el paquete
	bool envuelto_;			//Variable que indica si est� envuelto o no el paquete
	bool pesado_;			// indica si ya fue pesado
};


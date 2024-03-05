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
	bool Correcto() const;		//Bool que comprueba si el paquete tiene errores (falsificaciones, calles incorrectas...)

	// Sella la calle una única vez con el sellador
	void sellarCalle(Calle sello, Transform* trSellador);
	/// <summary>
	/// metodo que devuelve el string a implimir en la etiqueta de direccion
	/// </summary>
	/// <returns></returns>
	std::string getDirecction();
	TipoPaquete getTipo() const { return miTipo; }
	Distrito getDistrito() const { return miDistrito; }
	Calle getCalle() const { return miCalle; }
	std::string getRemitente() const { return miRemitente; }
	NivelPeso getPeso() const { return miPeso; }
	bool getFragil() const { return fragil; }

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
	std::unordered_map<Distrito, std::vector<std::string>> distrito_calle;
	//Variables que se generan automaticamente con informaci�n de los paquetes
	Distrito miDistrito;	//Variable con el distrito al que es enviado el paquete	
	std::string miRemitente;  //Variable con el nombre del remitente
	Calle miCalle;			//Variable con la calle a la que es enviada el paquete	
	TipoPaquete miTipo;		//Variable con el tipo de cargamente que lleva el paquete
	bool selloCorrecto;		//Variable que indica si el sello que contiene el paquete es correcto o no
	NivelPeso miPeso;		//Variable que indica qu� peso esta marcado en el paquete, o si este peso ni siquera est� marcado
	int peso;				//Variable que indica cuanto pesa el paquete para mostrar en la balanza
	bool fragil;			//Variable que indica si tiene un sello de fr�gil puesto

	//Bool que indica si el paquete es en realidad una carta, y si debe ser representado como tal en el renderizado
	bool carta;

	//Variables que debe modificar el jugador
	Calle calleMarcada;		//Variable que indica para qu� distrito ha sido etiquetado el paquete
	bool envuelto;			//Variable que indica si est� envuelto o no el paquete
};


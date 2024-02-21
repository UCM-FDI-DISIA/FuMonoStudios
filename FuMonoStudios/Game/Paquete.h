#pragma once
class Paquete
{
public:
	enum Distrito {Demeter,Hefesto,Hestia,Artemisa,Hermes,Apolo,Poseidon};	//enum con todos los distritos posibles que pueden tener los paquetes
	enum Calle {Erronea, C1,C2,C3};											//enum con todas las calles posibles que pueden tener los paquetes
	enum TipoPaquete { Alimento,Medicinas,Joyas,Materiales,Armamento };		//enum con todoos los tipos de cargamente que pueden tener los paquetes
	enum NivelPeso { Ninguno, Bajo, Medio,Alto };							//enum con todas los tipos de medición de peso que pueden tener los paquetes

	Paquete(Distrito, Calle, TipoPaquete, bool, NivelPeso, int, bool, bool);
	~Paquete();
	bool Correcto() const;		//Bool que comprueba si el paquete tiene errores (falsificaciones, calles incorrectas...)

	void sellarCalle(Calle sello);

private:
	//Variables que se generan automaticamente
	Distrito miDistrito;	//Variable con el distrito al que es enviado el paquete	
	Calle miCalle;			//Variable con la calle a la que es enviada el paquete	
	TipoPaquete miTipo;		//Variable con el tipo de cargamente que lleva el paquete
	bool selloCorrecto;		//Variable que indica si el sello que contiene el paquete es correcto o no
	NivelPeso miPeso;		//Variable que indica qué peso esta marcado en el paquete, o si este peso ni siquera está marcado
	int peso;				//Variable que indica cuanto pesa el paquete para mostrar en la balanza
	bool fragil;			//Variable que indica si tiene un sello de frágil puesto

	//Bool que indica si el paquete es en realidad una carta, y si debe ser representado como tal en el renderizado
	bool carta;

	//Variables que debe modificar el jugador
	Calle calleMarcada;		//Variable que indica para qué distrito ha sido etiquetado el paquete
	bool envuelto;			//Variable que indica si está envuelto o no el paquete
};


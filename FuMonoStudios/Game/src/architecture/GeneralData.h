#pragma once
#include "../utils/Singleton.h"
#include "../components/Paquete.h"
#include "GameConstants.h"
#include <vector>

class DialogManager;

class GeneralData : public Singleton<GeneralData>
{
public:
	friend Singleton<GeneralData>;

	// enum con tipos de felicidad
	enum Felicidad { Minima, Mala, Normal, Buena, Maxima, NoHabladoAun };
	
	Felicidad stringToFelicidad(const std::string& str);

	// enum con el nombre de todas las cosas interactuables
	enum Personaje {
		Vagabundo, Secretario, Campesino, Artesano, Tarotisa, Soldado, Contable,
		JefeOficina
	};

	#pragma region NPCdata

	// Los datos de los NPC deben actualizarse al acabar cada día.
	// Recogen datos sobre su felicidad, así como que dialogo deben enseñar.
	// Al iniciarse, su felicidad estará en NoHabladoAun, y al sacar su
	// primer diálogo cambiará a Normal.
	// NPC MENORES: El bool giveEvent dicta si debe dar evento (true) o dar
	// un dialogo generico (false). El int iteration itera sobre los 3 posibles
	// dialogos genericos que tiene el personaje.
	// NPC GRANDES: El bool postConversation si es true, significa que ya se 
	// ha hablado con el una vez, y sacara el dialogo mas corto que sale despues
	// del dialogo original de ese dia.
	// 
	// Al acabar el día se debe llamar a setupDayData() para reiniciar las 
	// variables y ajustar datos segun el dia
	// 
	// NOTA IMPORTANTE: POSBILEMENTE SE PONDRA AQUI EL TEMA DE LAS CONDICIONES
	// Y LOS EVENTOS DE CADA NPC, AUN NO ESTA IMPLEMENTADO, SOLO ESTA PUESTO
	// LO DE LOS DIALOGOS
	struct NPCdata {
		Felicidad felicidad;
		virtual std::pair<const std::string, int> getDialogueInfo() = 0;

		// esto solo lo usa el NPCmenor
		virtual void iterateDialogues() = 0;
		virtual void setupDayData() = 0;
	};

	struct NPCMenorData : public NPCdata {
		NPCMenorData(Felicidad Felicidad, std::vector<bool> DiasDanEvento);

		std::pair<const std::string, int> getDialogueInfo() override;
		void iterateDialogues() override;
		void setupDayData() override;
	private:
		void activateEvent();
		void deactivateEvent();

		std::vector<bool> diasDanEvento;

		bool giveEvent;
		int iteration;
	};

	struct NPCMayorData : public NPCdata {
		NPCMayorData(Felicidad Felicidad);

		std::pair<const std::string, int> getDialogueInfo() override;
		void iterateDialogues() override {};
		void setupDayData() override;
	private:
		bool postConversation;
	};
#pragma endregion

	GeneralData();
	~GeneralData();

	/// <summary>
	/// Metodo que acutaliza cuanto dinero tienes en funcion de los fallos y aciertos que realices
	/// </summary>
	/// <param name="writePacages"></param>
	/// <param name="wrongPacages"></param>
	void updateMoney(int correct, int wrong);
	int getMoney() { return dinero_; }

	void setFinalID(int final); //Cambia el ID del final
	int getFinalID(); //Devuelve el id del final del juego

	void setEventoID(int evento); //Cambia el ID del evento a ocurrir
	int getEventoID(); //Devuelve el id del evento que ocurrir� en el juego

	int getDia() { return dia_; }
	void setDia(int dia) { dia_ = dia; }

	void setTubesAmount(int tubos) { numTubos_ = tubos; } // Aumenta el numero de tubos en el minijuego cuando se requiera (podría llamarse automáticamente
														  // desde setDia modificado). Que jose lo haga cuando se sepan los días en los que un distrito y su tubo se desbloquean
	int getTubesAmount() { return numTubos_; }

	void correctPackage() { corrects_++; }
	void wrongPackage() { fails_++; }

	int getFails() { return fails_; }
	int getCorrects() { return corrects_; }

	void resetFailsCorrects() { fails_ = 0; corrects_ = 0; }

	void addPaqueteNPC(Paquete p) { paquetesNPCs.push_back(p); }
	bool areTherePaquetesNPC() { return paquetesNPCs.size() != 0; }
	void resetPaquetesNPC() { while (areTherePaquetesNPC()) paquetesNPCs.pop_back(); }

	Paquete getPaqueteNPC() { Paquete p = paquetesNPCs.back(); paquetesNPCs.pop_back(); return p; }
	int getPaqueteLevel(); // Devuelve el lvl del paquete correspondiente al d�a
	void setPaqueteLevel(int lvl);

	// convierte Personaje a string
	const std::string personajeToString(Personaje pers);
	// convierte string a Personaje
	Personaje stringToPersonaje(const std::string& pers);

	// lee los datos de NPCs desde su JSON
	void readNPCData();
	// escribe los datos de NPCs a su JSON
	void writeNPCData();

	NPCdata* getNPCData(Personaje personaje);
private:
	void addMoney(int cant) { dinero_ += cant; }
	void reduceMoney(int cant) { dinero_ -= cant; }

	// vector que contiene los datos de todos los 7 npc
	std::vector<NPCdata*> npcData;

	int fails_;
	int corrects_;
	int dinero_;
	int failsMargin_;
	int finalID_; //Variable int que define en la �ltima escena cu�l final se va a reproducir
	int eventoID_; //Variable int que define cual evento especial de la historia deber� de ejecutarse
	int dia_;
	int paqueteLvl_ = 0; // de momento es 0
	int numTubos_; // Numero de tubos que habrán en el minijuego de paquetes
	std::vector<Paquete> paquetesNPCs;
};

inline GeneralData& generalData() {
	return *GeneralData::instance();
}
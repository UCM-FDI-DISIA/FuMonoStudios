#pragma once
#ifndef DEV_TOOLS
#include <utils/checkML.h>
#endif // !DEV_TOOLS
#include <scenes/MainScene.h>
#include <sistemas/TutorialSystem.h>




// Esta escena tiene los mismos objetos que la escena principal a excepcion
// del tutorialSystem, que va poniendo textos y permitiendo acciones en funcion
// del punto del tutorial en el que estamos
namespace ecs {
	class TutorialScene : public MainScene
	{
		__SC_DECL__(ecs::sc::TUTORIAL_SCENE)
		friend TutorialSystem;
	public:
		TutorialScene();
		virtual ~TutorialScene();

		virtual void update() override;
		virtual void render() override;
		void close() override;
		void init() override;
		/// <summary>
		/// notifica al sistema de tutorial que un paquete ha sido enviado
		/// </summary>
		void packageSent();

		enum PackageTutorial { Primero, Segundo, Tercero, FallarAposta, Fragil, BalanzaTut, Carta, Random};
		ecs::Entity* createPackage(PackageTutorial pt);

		//void createErrorMessage(Paquete* paqComp, bool basura, bool tuboIncorrecto);

		// getters
		ecs::Entity* getManual() { return manualEnt_; }

	private:

		//Sobreescritura de varios metodos de creacion para incluir la recepcion de la accion
		ecs::Entity* createMiniManual() override;
		std::unordered_map<std::string, ecs::Entity*> createManual(int NumPages) override;
		std::unordered_map<std::string, ecs::Entity*> createBalanza() override;
		std::unordered_map<std::string, ecs::Entity*> createTubes() override;
		ecs::Entity* createGarbage() override; // empieza desactivada

		//Desactiva todos los tubos para que no se envien por ellos paquetes
		void deactivateTubos();
		//Desactiva todos menos un tubo
		void deactivateAllButOneTube(int tube);
		//Desactiva un tubo
		void deactivateOneTube(int tube);
		//Activa todos los tubos
		void activateTubos();
		//Activa todos menos un tubo
		void activateAllButOneTube(int tube);
		//Activa solo un tubo
		void activateOneTube(int tube);

		void activateGarbage();
		void deactivateGarbage();

		void createPauseButton();


		ecs::Entity* garbage_;

		TutorialSystem* tutorialSys_;

		bool balanzaUsed;
	};
}
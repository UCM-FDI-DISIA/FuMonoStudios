#include "Herramientas.h"


Herramientas::Herramientas() {

}

Herramientas::~Herramientas() {

}

void Herramientas::setFunctionality(TipoHerramienta tipo) {
	switch (tipo) 
	{
	case SelloCalleA:
		funcion = [](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C1);
			std::cout << "A";
			};
		break;
	case SelloCalleB:
		funcion = [](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C2);
			std::cout << "B";
			};
		break;
	case SelloCalleC:
		funcion = [](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C3);
			std::cout << "C";
			};
		break;
	}
}
void Herramientas::interact(ecs::Entity* paquete) {
	funcion(paquete);
}
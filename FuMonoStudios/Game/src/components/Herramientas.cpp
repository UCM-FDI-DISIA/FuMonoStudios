#include "Herramientas.h"


Herramientas::Herramientas() {

}

Herramientas::~Herramientas() {

}


void Herramientas::update() {

}

void Herramientas::setFunctionality(TipoHerramienta tipo) {
	switch (tipo) 
	{
	case SelloCalleA:
		funcion = [](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C1);
			};
		break;
	case selloCalleB:
		funcion = [](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C1);
			};
		break;
	case selloCalleC:
		funcion = [](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C1);
			};
		break;
	}
}
void Herramientas::interact(ecs::Entity* paquete) {
	funcion(paquete);
}
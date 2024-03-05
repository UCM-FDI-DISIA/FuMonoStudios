#include "Herramientas.h"
#include "Transform.h"
#include "MoverTransform.h"

Herramientas::Herramientas() {

}

Herramientas::~Herramientas() {

}

void Herramientas::setFunctionality(TipoHerramienta tipo) {

	switch (tipo) 
	{
	case SelloCalleA:
		funcion = [this](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C1, ent_->getComponent<Transform>());
			};
		break;
	case SelloCalleB:
		funcion = [this](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C2, ent_->getComponent<Transform>());
			};
		break;
	case SelloCalleC:
		funcion = [this](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C3, ent_->getComponent<Transform>());
			};
		break;
	}
}
void Herramientas::interact(ecs::Entity* paquete) {
	funcion(paquete);
}
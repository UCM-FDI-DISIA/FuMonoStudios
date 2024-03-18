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
		funcion_ = [this](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C1, ent_->getComponent<Transform>());
			};
		break;
	case SelloCalleB:
		funcion_ = [this](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C2, ent_->getComponent<Transform>());
			};
		break;
	case SelloCalleC:
		funcion_ = [this](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C3, ent_->getComponent<Transform>());
			};
		break;
	case WeightMachine:
		funcion_ = [this](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->getPeso();

			Transform* entTr = ent_->getComponent<Transform>();
			paqComp->sellarPeso(entTr);
		};
		break;
	}
}
void Herramientas::interact(ecs::Entity* paquete) {
	funcion_(paquete);
}
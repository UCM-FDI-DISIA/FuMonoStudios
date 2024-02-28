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
			ent_->addComponent<MoverTransform>(
				Vector2D(1200,200),1,Easing::EaseOutBack);
			};
		break;
	case SelloCalleB:
		funcion = [this](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C2, ent_->getComponent<Transform>());
			ent_->addComponent<MoverTransform>(
				Vector2D(1200, 300), 1, Easing::EaseOutCubic);
			};
		break;
	case SelloCalleC:
		funcion = [this](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C3, ent_->getComponent<Transform>());
			ent_->addComponent<MoverTransform>(
				Vector2D(1200, 400), 1, Easing::Linear);
			};
		break;
	}
}
void Herramientas::interact(ecs::Entity* paquete) {
	funcion(paquete);
}
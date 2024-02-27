#include "Herramientas.h"
#include "Transform.h"
#include "MoverTransform.h"

Herramientas::Herramientas() {

}

Herramientas::~Herramientas() {

}

void Herramientas::setFunctionality(TipoHerramienta tipo) {

	Transform* selladorTr = ent_->getComponent<Transform>();

	switch (tipo) 
	{
	case SelloCalleA:
		funcion = [this,selladorTr](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C1, selladorTr->getCenter());
			ent_->addComponent<MoverTransform>(
				Vector2D(0,0),1,Easing::EaseOutCubic);
			};
		break;
	case SelloCalleB:
		funcion = [selladorTr](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C2, selladorTr->getCenter());
			};
		break;
	case SelloCalleC:
		funcion = [selladorTr](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C3, selladorTr->getCenter());
			};
		break;
	}
}
void Herramientas::interact(ecs::Entity* paquete) {
	funcion(paquete);
}
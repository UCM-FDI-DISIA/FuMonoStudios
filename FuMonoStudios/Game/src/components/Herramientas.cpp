#include "Herramientas.h"
#include "Transform.h"

Herramientas::Herramientas() {

}

Herramientas::~Herramientas() {

}

void Herramientas::setFunctionality(TipoHerramienta tipo) {

	Transform* selladorTr = ent_->getComponent<Transform>();

	switch (tipo) 
	{
	case SelloCalleA:
		funcion = [selladorTr](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C1, selladorTr->getCenter());
			};
		break;
	case SelloCalleB:
		funcion = [selladorTr](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C2, selladorTr->getPos());
			};
		break;
	case SelloCalleC:
		funcion = [selladorTr](ecs::Entity* paq) {
			Paquete* paqComp = paq->getComponent<Paquete>();
			paqComp->sellarCalle(Paquete::C3, selladorTr->getPos());
			};
		break;
	}
}
void Herramientas::interact(ecs::Entity* paquete) {
	funcion(paquete);
}
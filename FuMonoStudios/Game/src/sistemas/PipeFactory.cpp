#include "PipeFactory.h"
#include "../components/Paquete.h"
#include "../architecture/Entity.h"
#include <stdlib.h>
#include "../sdlutils/VirtualTimer.h"
#include "../architecture/GeneralData.h"

void PipeFactory::createPipes(Scene* mScene) {
	int numTubos = generalData().getTubesAmount(); // coge el numero de tubos que están desbloqueados
	int j = 0;
	for (int i = 0; i < numTubos; i++) {
		createPipe(mScene, (Paquete::Distrito)i, true);
		j++;
	}
	//Creación de paquetes bloqueados
	for (int z = j; z < 7; z++) {
		createPipe(mScene, (Paquete::Distrito)z, false);
	}
}

void PipeFactory::createPipe(Scene* mScene, Paquete::Distrito toDis, bool disponible) {
	
}
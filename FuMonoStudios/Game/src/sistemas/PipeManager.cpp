#include "PipeManager.h"

PipeManager::PipeManager() : returnPipe_(Erroneo)
{
	
}

PipeManager::~PipeManager()
{

}

void PipeManager::init()
{
	returnPipe_ = pq::Erroneo;
	for (int i = 0; i < 8; i++) {
#ifdef _DEBUG
		std::cout << "Pipe" << i << "Config" << std::endl;
#endif // _DEBUG
		blockedPipes_.push_back(false);
		swappedPipes_.push_back({ false, false, Erroneo });
		bannedTypePipes_.push_back({false, Alimento});
		weightRestrictionTypes_.push_back({false, false, 4, Ninguno, Alimento});
	}
}

void PipeManager::setReturnPipe(pq::Distrito trash)
{
	returnPipe_ = trash;
}

bool PipeManager::checkPackage(Paquete* pqt, pq::Distrito toDis)
{
	//Comprueba si el paquete es correcto de base
		//Si lo es, se comprueba que se haya procesado bien (sellar calle, evolver, etc)
			//Si es correcto comprueba que no se halla mandado a la papelera
				//Si no se ha mandado a la de retorno, comprueba que no incumpla otra infracción de la tubería destino:
				//Primero si está bloqueada
				//Luego si está intercambiado (si está cambiado se checkeará ese distrito a partir de ahora)
				//Luego, si hay algún tipo baneado
				//Por último, comprueba restricciones de peso
					//Si todo eso es correcto devuelve True :D
					//Else, devuelve false
				//Si se ha mandado a la papelera, comprueba (de manera similar a la de arriba) si las condiciones 
				//impedirían que se mandase el paquete.
					//Si lo impiden, es correcto devolverlo al remitente y devuelve True
					//Si no, es un fallo y devuelve false
		//Si el paquete es incorrecto comprueba que esté en la papelera
			//Si lo está, devuelve true
			//Si no, es un buen paquete en la basura y devuelve false D:

	/*
	if (correct) {
		if (pqt->bienSellado() && pqt->correctFragile()) {
			if (toDis == returnPipe_) {
				correct = checkReturningConditions(pqt);
			}
			else {
				correct = checkPipeConditions(pqt, toDis);
			}
		}
		else {
			correct = false;
		}
	}
	else {
		if (toDis == returnPipe_) {
			correct = true;
		}
		else {
			correct = false;
		}
	} */

	return ((!pqt->correcto() && toDis == returnPipe_) || //Si el paquete es incorrecto que se envie a la tubería que actua de papelera
		pqt->correcto() && (pqt->bienSellado() && pqt->correctFragile() &&	//Si es correcto si comprueba si está sellado y protegido si fragil
		((toDis == returnPipe_ && checkReturningConditions(pqt)) ||		//Si es correcto pero se ha devuelto, comprueba si estaba bloqueado
		(toDis != returnPipe_ && checkPipeConditions(pqt, toDis)))));	//Si es correcto, comprueba que se haya mandado correctamente
}

void PipeManager::blockPipe(pq::Distrito target)
{
	blockedPipes_[target] = true;
}

void PipeManager::swapPipe(pq::Distrito target, SwappedPipe toNew)
{
	swappedPipes_[target] = toNew;
}

void PipeManager::banTypeInPipe(pq::Distrito target, pq::TipoPaquete ban)
{
	bannedTypePipes_[target].first = true;
	bannedTypePipes_[target].second = ban;
}

void PipeManager::weightRestrictPipe(pq::Distrito target, WeightRestriction restrictions)
{
	weightRestrictionTypes_[target] = restrictions;
}

void PipeManager::activateEvent(WorkEvent evento)
{
    switch (evento.id)
    {
	case SWAP_PIPE:
		swapPipe(evento.swap_pipe_data.targetPipe, evento.swap_pipe_data.dest);
		blockPipe(evento.swap_pipe_data.blockedPipe);
		break;
	case BAN_TYPE_IN_PIPE:
		banTypeInPipe(evento.ban_type_pipe_data.targetPipe, evento.ban_type_pipe_data.ban);
		break;
	case WEIGHT_RESTRICT_PIPE:
		weightRestrictPipe(evento.weight_res_pipe_data.targetPipe, evento.weight_res_pipe_data.restrictions);
		break;
    default:
		break;
    }
}

bool PipeManager::checkPipeConditions(Paquete* pqt, pq::Distrito toDis)
{
	bool correct;
	SwappedPipe it = swappedPipes_[toDis];

	/*
	if (!blockedPipes_[toDis]) {
		if (it.swapActive) {
			if (it.changedDis == pqt->getDistrito()) {
				correct = checkPipeRestrictions(pqt, it.changedDis);
			}
			else if (it.originalDis && toDis == pqt->getDistrito()) {
				correct = checkPipeRestrictions(pqt, toDis);
			}
			else {
				correct = false;
			}
		}
		else {
			if (toDis == pqt->getDistrito()) {
				correct = checkPipeRestrictions(pqt, toDis);
			}
			else {
				correct = false;
			}
		}
	}
	else {
		correct = false;
	}*/

	return (!blockedPipes_[toDis] && //Comprueba si la tubería está bloqueada
			((it.swapActive &&		 //"" "" "" "" está cambiada 	
			((it.changedDis == pqt->getDistrito() && checkPipeRestrictions(pqt, it.changedDis)) ||		//Comprueba si la tubería cambiada es correcta
			(it.originalDis && toDis == pqt->getDistrito() && checkPipeRestrictions(pqt, toDis)))) ||	//Comprueba si el destino original es correcto
			(!it.swapActive && toDis == pqt->getDistrito() && checkPipeRestrictions(pqt, toDis))));		//Comprueba si no está cambiada si es correcto
}

bool PipeManager::checkPipeRestrictions(Paquete* pqt, pq::Distrito toDis)
{
	/*
	if (bannedTypePipes_[toDis].first && pqt->getTipo() == bannedTypePipes_[toDis].second) {
		correct = false;
	}
	else {
		correct = checkWeightRestrictions(pqt, toDis);
	}*/

	return (!(bannedTypePipes_[toDis].first && pqt->getTipo() == bannedTypePipes_[toDis].second) && checkWeightRestrictions(pqt, toDis));
}

bool PipeManager::checkWeightRestrictions(Paquete* pqt, pq::Distrito toDis)
{
	bool correct;
	WeightRestriction it = weightRestrictionTypes_[toDis];
	pq::NivelPeso peso = pqt->getPeso();
	
	/*
	if (it.weightRestricted && peso != pq::Ninguno) {
		if (it.singleType) {
			if (pqt->getTipo() != it.typeToWeight) {
				correct = true;
			}
			else {
				if (it.minOrMax == 0 && it.x < peso) {
					correct = true;
				}
				else if (it.minOrMax == 1 && it.x == peso) {
					correct = true;
				}
				else if (it.minOrMax == 2 && it.x > peso) {
					correct = true;
				}
				else if (it.minOrMax == 3 && it.x != peso) {
					correct = true;
				}
				else {
					correct = false;
				}
			}
		}
		else {
			if (it.minOrMax == 0 && it.x < peso) {
				correct = true;
			}
			else if (it.minOrMax == 1 && it.x == peso) {
				correct = true;
			}
			else if (it.minOrMax == 2 && it.x > peso) {
				correct = true;
			}
			else if (it.minOrMax == 3 && it.x != peso) {
				correct = true;
			}
			else {
				correct = false;
			}
		}
	}
	else {
		correct = true;
	}*/

	return (!it.weightRestricted || peso == pq::Ninguno || 
		((it.singleType && pqt->getTipo() != it.typeToWeight) ||
		((it.minOrMax == 0 && it.x < peso) || (it.minOrMax == 1 && it.x == peso) ||
		(it.minOrMax == 2 && it.x > peso) || (it.minOrMax == 3 && it.x != peso))));
}

bool PipeManager::checkReturningConditions(Paquete* pqt)
{
	bool blocked;
	pq::Distrito objDis = pqt->getDistrito();
	SwappedPipe it = swappedPipes_[objDis];

	if (blockedPipes_[objDis] || (it.swapActive && !it.originalDis)) {
		if (checkSwappedPipes(pqt)) {
			blocked = !checkPipeRestrictions(pqt, objDis);
		}
		else {
			blocked = true;
		}
	}
	else {
		blocked = !checkPipeRestrictions(pqt, objDis);
	}

	return blocked;
}

bool PipeManager::checkSwappedPipes(Paquete* pqt)
{
	int i = 0;
	pq::Distrito objDis = pqt->getDistrito();

	while (i < 7 && (!swappedPipes_[i].swapActive || (swappedPipes_[i].swapActive && swappedPipes_[i].changedDis != objDis))) {
		i++;
	}
	return i == 7;
}

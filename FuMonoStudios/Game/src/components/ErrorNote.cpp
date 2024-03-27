#include "ErrorNote.h"


ErrorNote::ErrorNote(Paquete* p, bool basura, bool tuboIncorrecto) {
	if (basura) {
		text_ = "Ese paquete no deberia haber sido tirado a la basura \n";
	}
	else if (tuboIncorrecto) {
		text_ = "Ese paquete ha sido enviado al tubo incorrecto \n";
	}else
	{
		if (!p->getSelloCorrecto()) {
			text_ = "Ese paquete tiene un sello incorrecto \n";
		}
		else if (p->getCalle() == pq::Erronea) {
			std::cout << "Ese paquete no tenia una calle existente\n";
		}
		else if (!p->bienSellado()) {
			text_ = "Ese paquete no ha sido bien sellado \n";
		}
		else if (!p->pesoCorrecto()) {
			text_ = "Ese paquete no ha sido bien sellado segun el peso\n";
		}
	}	
}
ErrorNote::~ErrorNote() {

}
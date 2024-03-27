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
		if (p->getCalle() == pq::Erronea) {
			std::cout << "Ese paquete no tenia una calle existente\n";
		}
		if (!p->bienSellado()) {
			std::cout << "Ese paquete no ha sido bien sellado \n";
		}
		if (!p->pesoCorrecto()) {
			std::cout << "Ese paquete no ha sido bien sellado segun el peso\n";
		}
	}	
}
ErrorNote::~ErrorNote() {

}
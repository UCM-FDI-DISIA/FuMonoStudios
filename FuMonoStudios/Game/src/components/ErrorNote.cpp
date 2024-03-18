#include "ErrorNote.h"


ErrorNote::ErrorNote(Paquete* p, bool basura, bool tuboIncorrecto) {
	if (basura) {
		std::cout << "Ese paquete no deberia haber sido tirado a la basura \n";
	}
	else if (tuboIncorrecto) {
		std::cout << "Ese paquete ha sido enviado al tubo incorrecto \n";
	}else
	{
		if (!p->getSelloCorrecto()) {
			std::cout << "Ese paquete tiene un sello incorrecto \n";
		}
		else if (p->getCalle() == Paquete::Erronea) {
			std::cout << "Ese paquete no tenia una calle existente\n";
		}
		else if (!p->bienSellado()) {
			std::cout << "Ese paquete no ha sido bien sellado \n";
		}
		else if (!p->pesoCorrecto()) {
			std::cout << "Ese paquete no ha sido bien sellado segun el peso\n";
		}
	}	
}
ErrorNote::~ErrorNote() {

}
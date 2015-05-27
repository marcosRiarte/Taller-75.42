#include "stdafx.h"
#include "ControladorDeTomas.h"


ControladorDeTomas::ControladorDeTomas()
{
	tomas = std::vector<Toma*>();
}


void ControladorDeTomas::setToma(Toma* unaToma){
	tomas.push_back(unaToma);
}


void ControladorDeTomas::setMovimientos(std::vector<MOV_TIPO>* unosMovimientosActivos){
	movimientosActivos = unosMovimientosActivos;
}


bool ControladorDeTomas::hayToma(Toma* unaToma, bool estaInvertido){
	int error = 0;
	int aciertos = 0;
	int j = unaToma->getMovimientos()->size() - 1;
	MOV_TIPO otroMovimiento, unMovimiento;
	if (movimientosActivos->size() >= (unaToma->getMovimientos()->size())){
		for (int i = movimientosActivos->size() - 1; i >= 0; i--){
			if (aciertos == unaToma->getMovimientos()->size()){
				movimientosActivos->clear();
				return true;
			}
			if (error > unaToma->getError()) return false;

			otroMovimiento = movimientosActivos->at(i);
			unMovimiento = movimientosActivos->at(i);

			if (estaInvertido){
				if (otroMovimiento == DER) unMovimiento = IZQ;
				if (otroMovimiento == IZQ) unMovimiento = DER;
				if (otroMovimiento == SALTODER) unMovimiento = SALTOIZQ;
				if (otroMovimiento == SALTOIZQ) unMovimiento = SALTODER;
			}

			if (unMovimiento != unaToma->getMovimientos()->at(j)){
				if (i == (movimientosActivos->size() - 1)) return false;
				error++;
			}
			else{
				j--;
				aciertos++;
			}
		}
		movimientosActivos->clear();
		return true;
	}
	return false;
}


Toma* ControladorDeTomas::getTomaSegunOrientacion(bool estaInvertido){
	for (size_t i = 0; i < tomas.size(); i++){
		if (hayToma(tomas.at(i), estaInvertido)) return tomas.at(i);
	}
	return nullptr;
}


std::vector<Toma*>* ControladorDeTomas::getTomas(){
	return &tomas;
}


ControladorDeTomas::~ControladorDeTomas()
{
	for (size_t i = 0; i < tomas.size(); i++){
		delete tomas.at(i);
	}
	tomas.clear();
}

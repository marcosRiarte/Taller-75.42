#include "stdafx.h"
#include "ControladorDeTomas.h"


ControladorDeTomas::ControladorDeTomas()
{
	/*movimientosDeTomas = std::vector<std::vector<MOV_TIPO>>();
	movimientosDeTomas.push_back(std::vector<MOV_TIPO>());
	movimientosDeTomas.push_back(std::vector<MOV_TIPO>());
	movimientosDeTomas.push_back(std::vector<MOV_TIPO>());*/
}


/*void ControladorDeTomas::setMovimientoParaToma(MOV_TIPO unMovimiento, TOMA unaToma){
	movimientosDeTomas.at(unaToma).push_back(unMovimiento);
}


void ControladorDeTomas::setMovimientos(std::vector<MOV_TIPO>* unosMovimientosActivos){
	movimientosActivos = unosMovimientosActivos;
}
*/

bool ControladorDeTomas::hayToma(TOMA unaToma, bool estaInvertido){
	/*int error = 0;
	int aciertos = 0;
	int j = movimientosDeTomas.at(unaToma).size() - 1;
	MOV_TIPO otroMovimiento, unMovimiento;
	if (movimientosActivos->size() == (movimientosDeTomas.at(unaToma).size() + 1)){
		for (int i = movimientosActivos->size() - 1; i >= 0; i--){
			if (aciertos == 5) return true;
			if (error > 1) return false;

			otroMovimiento = movimientosActivos->at(i);
			unMovimiento = movimientosActivos->at(i);

			if (estaInvertido){
				if (otroMovimiento == DER) unMovimiento = IZQ;
				if (otroMovimiento == IZQ) unMovimiento = DER;
				if (otroMovimiento == SALTODER) unMovimiento = SALTOIZQ;
				if (otroMovimiento == SALTOIZQ) unMovimiento = SALTODER;
			}

			if (unMovimiento != movimientosDeTomas.at(unaToma).at(j)){
				if (i == (movimientosActivos->size() - 1)) return false;
				error++;
			}
			else{
				j--;
				aciertos++;
			}
		}
		return true;
	}*/
	return false;
}


ControladorDeTomas::TOMA ControladorDeTomas::getTomaSegunOrientacion(bool estaInvertido){
	for (int unaToma = TOMA1; unaToma < (sizeof(TOMA) - 1); unaToma++){
		if (hayToma((TOMA)unaToma, estaInvertido)) return (TOMA)unaToma;
	}
	return NINGUNA;
}


ControladorDeTomas::~ControladorDeTomas()
{
	/*for (int i = 0; i < movimientosDeTomas.size(); i++){
		movimientosDeTomas.at(i).clear();
	}
	movimientosDeTomas.clear();*/
}

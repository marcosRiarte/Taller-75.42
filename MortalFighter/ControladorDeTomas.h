#pragma once
#include "Controlador.h"

class ControladorDeTomas
{
public:
	enum TOMA {TOMA1, TOMA2, FATALITY, NINGUNA};

	ControladorDeTomas();
	TOMA getTomaSegunOrientacion(bool estaInvertido);
	//void setMovimientoParaToma(MOV_TIPO unMovimiento, TOMA unaToma);
	//void setMovimientos(std::vector<MOV_TIPO>* unosMovimientosActivos);
	~ControladorDeTomas();

private:
	//std::vector< std::vector<MOV_TIPO> > movimientosDeTomas;
	//std::vector<MOV_TIPO>* movimientosActivos;

	bool hayToma(TOMA unaToma, bool estaInvertido);
};


#pragma once
#include "Toma.h"

class ControladorDeTomas
{
public:
	enum TOMA { TOMA1, TOMA2, FATALITY, NINGUNA };

	ControladorDeTomas();
	Toma* getTomaSegunOrientacion(bool estaInvertido);
	void setToma(Toma* unaToma);
	void setMovimientos(std::vector<MOV_TIPO>* unosMovimientosActivos);
	std::vector<Toma*>* getTomas();
	~ControladorDeTomas();

private:
	std::vector<Toma*> tomas;
	std::vector<MOV_TIPO>* movimientosActivos;

	bool hayToma(Toma* unaToma, bool estaInvertido);
};


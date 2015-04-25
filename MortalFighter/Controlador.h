#pragma once
#include "Constantes.h"

enum MOV_TIPO { QUIETO, DER, IZQ, ARRIBA, ABAJO, SALTOIZQ, SALTODER, CERRAR, RECARGAR };


class Controlador
{
public:
	Controlador();
	
	~Controlador();
	int cambiar();
	std::vector<MOV_TIPO> getMovimientos();

protected:
	std::vector<MOV_TIPO> movimientos;
};


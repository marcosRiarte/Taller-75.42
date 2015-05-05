/*
QUIETO, DER, IZQ, ARRIBA, ABAJO,
SALTOIZQ, SALTODER, 
DEFENSA, 
G_BAJO, G_ALTO, //piñas
G_ABAJO, G_GANCHO, 
G_SALTO, 
G_SALTOIZQ, 
G_SALTODER,  

P_BAJA, P_ALTA, 
P_BAJA_ABAJO, P_ALTA_ABAJO, 
P_SALTO, P_SALTOIZQ, P_SALTODER,  //patas
ARMA, CERRAR, RECARGAR

*/

#pragma once
#include "Constantes.h"
#include "ConversorDeEventos.h"

enum MOV_TIPO { QUIETO, DER, IZQ, ARRIBA, ABAJO, SALTOIZQ, SALTODER, DEFENSA, DEFENSA_AGACHADO, G_BAJO, G_ALTO, G_ABAJO, G_GANCHO, G_SALTO, G_SALTOIZQ, G_SALTODER, P_BAJA, P_ALTA, P_BAJA_ABAJO, P_ALTA_ABAJO, P_SALTO, P_SALTOIZQ, P_SALTODER, ARMA, CERRAR, RECARGAR };


class Controlador
{
public:
	Controlador();
	
	~Controlador();
	int cambiar();
	std::vector<MOV_TIPO> getMovimientos();
	void setConversorDeEventos(ConversorDeEventos* unConversorDeEventos);

protected:
	std::vector<MOV_TIPO> movimientos;
	ConversorDeEventos* conversorDeEventos;
};


/*
TECLAS DEL LOS PERSONAJES
Harcodee flechas 1,2,3,4,5,6 para el p1
[05:12:52 p.m.] Agustín: y w,a,s,d,j,k,l,u,i,o para el 2
[05:13:03 p.m.] Agustín: el 1 y j es guardia
[05:13:21 p.m.] Agustín: el 4 y u es arma arrojable
[05:13:38 p.m.] Agustín: el 2 y k golpe bajo
[05:13:42 p.m.] Agustín: 3 y l golpe alto
[05:13:51 p.m.] Agustín: 5 y i patada baja
[05:13:56 p.m.] Agustín: 6 y o patada alta

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

enum MOV_TIPO { QUIETO, DER, IZQ, ARRIBA, ABAJO, SALTOIZQ, SALTODER, DEFENSA, G_BAJO, G_ALTO, G_ABAJO, G_GANCHO, G_SALTO, G_SALTOIZQ, G_SALTODER, P_BAJA, P_ALTA, P_BAJA_ABAJO, P_ALTA_ABAJO, P_SALTO, P_SALTOIZQ, P_SALTODER, ARMA, CERRAR, RECARGAR };


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


#include "stdafx.h"
#include "Mundo.h"
#include "Cuerpo.h"

Mundo::Mundo()
{

}

void Mundo::Paso(float difTiempo)
{
	for (int i = 0; i < Cuerpos.size(); i++)
		Resolver(difTiempo, Cuerpos.at(i));

}

void Mundo::Resolver(float difTiempo, Cuerpo &unCuerpo)
{
	//integra velocidad, para salto, en el piso la fuerza normal anula la gravedad...
	vector2D unaFuerza = unCuerpo.getFuerzas();
	unaFuerza /= unCuerpo.getMasa();
	unaFuerza += gravedad * difTiempo;

	unCuerpo.sumarVelocidad(unaFuerza);

	//integra posicion
	vector2D unaVelocidad = unCuerpo.getVelocidad();
	unCuerpo.sumarPosicion(unaVelocidad * difTiempo);

}
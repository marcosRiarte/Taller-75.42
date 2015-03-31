#include "stdafx.h"
#include "Mundo.h"
#include "Cuerpo.h"

Mundo::Mundo()
{

}

void Mundo::Paso(float difTiempo)
{
	for (unsigned int i = 0; i < Cuerpos.size(); i++)
		Resolver(difTiempo, Cuerpos.at(i));

}

void Mundo::Resolver(float difTiempo, Cuerpo &unCuerpo)
{
	vector2D unaVelocidad = unCuerpo.getVelocidad();

	/// integra velocidad, para salto, 
	// si no está en el piso siente la gravedad
	if (!unCuerpo.estaEnPiso())
		unCuerpo.sumarVelocidad(gravedad * difTiempo);


	/// integra posicion	
	unCuerpo.sumarPosicion(unaVelocidad * difTiempo);
}
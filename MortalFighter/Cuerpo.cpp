#include "stdafx.h"
#include "Cuerpo.h"

Cuerpo::Cuerpo(const defCuerpo* unaDefCuerpo)
{
	nombre = unaDefCuerpo->nombre;
	posicion = unaDefCuerpo->posicion;
	velocidad = unaDefCuerpo->velocidad;	
	masa = unaDefCuerpo->masa;

}

bool Cuerpo::estaEnPiso()
{
	if (posicion.y > 0.0f )
		return false;

	return true;
}
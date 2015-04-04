#include "stdafx.h"
#include "Cuerpo.h"

Cuerpo::Cuerpo(const defCuerpo unaDefCuerpo)
{
	nombre = unaDefCuerpo.nombre;
	posicion = unaDefCuerpo.posicion;
	velocidad = unaDefCuerpo.velocidad;
	masa = unaDefCuerpo.masa;
	yPiso = Parser::getInstancia().getEscenario().getYPiso();
	posicion.y = yPiso;
}

bool Cuerpo::estaEnPiso()
{
	if (posicion.y > yPiso)
		return false;

	return true;
}

void Cuerpo::mover(float unaDistancia)
{
	posicion.x += unaDistancia;
}


void Cuerpo::recibeObservador(Personaje* unObservador)
{
	observador = unObservador;
}

void Cuerpo::notificarObservadores()
{
	observador->actualizar(posicion.x, posicion.y);
}
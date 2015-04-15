#include "stdafx.h"
#include "Cuerpo.h"

Cuerpo::Cuerpo(const defCuerpo unaDefCuerpo)
{
	nombre = unaDefCuerpo.nombre;
	posicion = unaDefCuerpo.posicion;
	velocidad = unaDefCuerpo.velocidad;
	masa = unaDefCuerpo.masa;
	posicion.x = Parser::getInstancia().getEscenario().getAncho() / 2;
	yPiso = Parser::getInstancia().getEscenario().getYPiso();
	posicion.y = yPiso;
}

bool Cuerpo::estaEnPiso()
{
	if (posicion.y > yPiso)
		return false;

	return true;
}

bool Cuerpo::estaEnBorde()
{
	if (posicion.x < Parser::getInstancia().getEscenario().getAncho())
		return false;

	return true;
}

void Cuerpo::sumarPosicion(const vector2D& unaPosicion)
{
	posicion += unaPosicion;
	// Que no se mueva debajo del piso
	if (estaEnPiso() && unaPosicion.y < yPiso) {
		posicion.y = yPiso;
		velocidad.x = 0.0f;
		velocidad.y = 0.0f;
	}

	// que no se mueva m�s all� del borde
	if (estaEnBorde())
		posicion.x = Parser::getInstancia().getEscenario().getAncho();
	// que no se mueva menos del cero
	if (posicion.x <= 0)
		posicion.x = 0;
}

void Cuerpo::mover(float unaDistancia)
{
	posicion.x += unaDistancia;
}


void Cuerpo::recibeObservador(Personaje* unObservador)
{
	observador = unObservador;
}

void Cuerpo::notificarObservadores(ESTADO nuevoEstado)
{
	observador->actualizar(posicion.x, posicion.y, nuevoEstado);
}
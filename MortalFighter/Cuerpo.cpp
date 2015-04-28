#include "stdafx.h"
#include "Cuerpo.h"

Cuerpo::Cuerpo(const defCuerpo unaDefCuerpo, Controlador* controladorNuevo)
{
	controlador = controladorNuevo;
	nombre = unaDefCuerpo.nombre;
	posicion = unaDefCuerpo.posicion;
	velocidad = unaDefCuerpo.velocidad;
	masa = unaDefCuerpo.masa;
	posicion.x = Parser::getInstancia().getEscenario().getAncho() / 2;
	yPiso = Parser::getInstancia().getEscenario().getYPiso();
	posicion.y = yPiso;
	estaFrenado = unaDefCuerpo.estaFrenado;
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

	// que no se mueva más allá del borde
	if (estaEnBorde())
		posicion.x = Parser::getInstancia().getEscenario().getAncho();
	// que no se mueva menos del cero
	if (posicion.x <= 0)
		posicion.x = 0;
	
}

void Cuerpo::mover(float unaDistancia)
{
	//if ((abs(Parser::getInstancia().getPersonajes().at(0)->getPosicionUn().first - Parser::getInstancia().getPersonajes().at(1)->getPosicionUn().first)) <= (Parser::getInstancia().getVentana().getAncho() - Parser::getInstancia().getPersonajes().at(0)->getAncho()))
		posicion.x += unaDistancia;
		//else
		//posicion.x -= unaDistancia;
}


void Cuerpo::recibeObservador(Personaje* unObservador)
{
	observador = unObservador;
}

void Cuerpo::notificarObservadores(ESTADO nuevoEstado)
{
	observador->actualizar(posicion.x, posicion.y, nuevoEstado);
}
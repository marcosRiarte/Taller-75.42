#include "stdafx.h"
#include "Cuerpo.h"

Cuerpo::Cuerpo(const defCuerpo unaDefCuerpo, Controlador* controladorNuevo, float posicionEnX, Personaje* unPersonaje)
{
	controlador = controladorNuevo;
	nombre = unaDefCuerpo.nombre;
	posicion = unaDefCuerpo.posicion;
	velocidad = unaDefCuerpo.velocidad;
	masa = unaDefCuerpo.masa;
	posicion.x = posicionEnX;
	yPiso = Parser::getInstancia().getEscenario().getYPiso();
	posicion.y = yPiso;
	estaFrenado = unaDefCuerpo.estaFrenado;
	demora = unaDefCuerpo.demora; //xjose
	sensorActivoStr = "";
	refPersonaje = unPersonaje;
	estadoAnterior.accion = SIN_ACCION;
	estadoAnterior.golpeado = NOGOLPEADO;
	estadoAnterior.movimiento = PARADO;
}

std::vector<Sensor*>* Cuerpo::getSensoresActivos() const
{
	for (size_t i = 0; i<sensores.size(); i++)
		if (sensores[i]->at(0)->getEstadoStr() == sensorActivoStr)
			return sensores[i];

	// si no se seteo un sensor activo pasa el primero
	return sensores[0];
}


bool Cuerpo::estaEnPiso()
{
	if (posicion.y > yPiso)
		return false;

	return true;
}

int Cuerpo::GetDemora()
{
	return demora;
}

ESTADO Cuerpo::getEstado()
{
	return observador->getEstado();
}

ESTADO Cuerpo::getEstadoAnterior()
{
	return estadoAnterior;
}

void Cuerpo::setDemora(int demoratiempo)
{
		demora = demoratiempo;
}

void Cuerpo::DisminuirDemora()
{
	demora--;
}

bool Cuerpo::estaEnBorde()
{
	if (posicion.x < Parser::getInstancia().getEscenario().getAncho())
		return false;

	return true;
}

Personaje* Cuerpo::getRefPersonaje(){
	return refPersonaje;
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

int Cuerpo::notificarObservadores(ESTADO nuevoEstado)
{
	if (nuevoEstado.golpeado == FALLECIDO)
		return REINICIAR;
	observador->actualizar(posicion.x, posicion.y, nuevoEstado);
		return CONTINUAR;
}
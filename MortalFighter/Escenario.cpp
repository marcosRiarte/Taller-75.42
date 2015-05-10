#include "stdafx.h"
#include "Escenario.h"


Escenario::Escenario(float anchoEscenario, float altoEscenario, float yPisoEscenario)
{
	ancho = anchoEscenario;
	alto = altoEscenario;
	yPiso = yPisoEscenario;
}

float Escenario::getAncho() const
{
	return ancho;
}

float Escenario::getAlto() const
{
	return alto;

}

float Escenario::getYPiso() const
{
	return yPiso;

}

void Escenario::setAncho(float unAncho){
	ancho = unAncho;
}


void Escenario::setAlto(float unAlto){
	alto = unAlto;
}


void Escenario::setYPiso(float unyPiso){
	yPiso = unyPiso;
}

Escenario::~Escenario()
{
}

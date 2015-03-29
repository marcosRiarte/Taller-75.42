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

Escenario::~Escenario()
{
}

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

Escenario::~Escenario()
{
}

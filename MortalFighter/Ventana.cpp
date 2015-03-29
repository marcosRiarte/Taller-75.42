#include "stdafx.h"
#include "Ventana.h"


Ventana::Ventana(int unAnchoPx, int unAltoPx, float unAncho)
{
	anchoPx = unAnchoPx;
	altoPx = unAltoPx;
	ancho = unAncho;
}

int Ventana::getAnchoPx() const
{
	return anchoPx;
}

int Ventana::getAltoPx() const
{
	return altoPx;
}

float Ventana::getAncho() const
{
	return ancho;
}

Ventana::~Ventana()
{
}

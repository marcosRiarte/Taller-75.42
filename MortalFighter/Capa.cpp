#include "stdafx.h"
#include "Capa.h"


Capa::Capa(std::string unaImagenFondo, float unAncho)
{
	imagenFondo = unaImagenFondo;
	ancho = unAncho;

}

std::string Capa::getImagenFondo(){
	return imagenFondo;
}


float Capa::getAncho(){
	return ancho;
}

Capa::~Capa()
{
}

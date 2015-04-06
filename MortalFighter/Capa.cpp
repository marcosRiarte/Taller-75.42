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

void Capa::setTexturaSDL(SDL_Texture* unaTexturaSDL)
{
	texturaSDL = unaTexturaSDL;
}

SDL_Texture* Capa::getTexturaSDL()
{
	return texturaSDL;
}

Capa::~Capa()
{
}

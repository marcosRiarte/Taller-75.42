#include "stdafx.h"
#include "Capa.h"


Capa::Capa(std::string unaImagenFondo, float unAncho, int zIndexCapa)
{
	imagenFondo = unaImagenFondo;
	ancho = unAncho;
	zIndex = zIndexCapa;
}

std::string Capa::getImagenFondo(){
	return imagenFondo;
}


float Capa::getAncho(){
	return ancho;
}

int Capa::getZIndex(){
	return zIndex;
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
	SDL_DestroyTexture(texturaSDL);
}

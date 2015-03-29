#include "stdafx.h"
#include "Personaje.h"


Personaje::Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string spritesPersonaje)
{
	ancho = anchoPersonaje;
	alto = altoPersonaje;
	zIndex = zIndexPersonaje;
	sprites = spritesPersonaje;
}

float Personaje::getAncho() const
{
	return ancho;
}

float Personaje::getAlto() const
{
	return alto;
}

int Personaje::getZIndex() const
{
	return zIndex;
}

std::string Personaje::getSprites() const
{
	return sprites;
}

Personaje::~Personaje()
{
}

#include "stdafx.h"
#include "Personaje.h"


Personaje::Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string spritesPersonaje)
{
	ancho = anchoPersonaje;
	alto = altoPersonaje;
	zIndex = zIndexPersonaje;
	sprites = spritesPersonaje;
}


Personaje::~Personaje()
{
}

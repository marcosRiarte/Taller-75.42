#include "stdafx.h"
#include "Personaje.h"
#include "Parser.h"
#include "ManejadorULogicas.h"

Personaje::Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string spritesPersonaje)
{
	ancho = anchoPersonaje;
	alto = altoPersonaje;
	zIndex = zIndexPersonaje;
	sprites = spritesPersonaje;
	posicionUn = std::make_pair(0.0f,0.0f);
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

std::pair<int, int> Personaje::getPosicionPx() const
{	
	ManejadorULogicas manejador;
	float yPiso = Parser::getInstancia().getEscenario().getYPiso();

	return manejador.obtenerPosicionPx(posicionUn.first, posicionUn.second + yPiso);
}

void Personaje::setPosicionUn(float x, float y)
{
	posicionUn.first = x;
	posicionUn.second = y;
}

void Personaje::actualizar(float xNuevo, float yNuevo)
{
	setPosicionUn(xNuevo, yNuevo);
}


Personaje::~Personaje()
{
}

#include "stdafx.h"
#include "Personaje.h"
#include "Parser.h"
#include "ManejadorULogicas.h"

Personaje::Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string spritesPersonaje)
{
	ancho = anchoPersonaje;
	alto = altoPersonaje;
	zIndex = zIndexPersonaje;
	energy = 100;
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

int Personaje::getZIndex() 
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
	float yPiso = Parser::getInstancia().getEscenario().getYPiso() + alto/2;
	

	return manejador.obtenerPosicionPx(posicionUn.first, posicionUn.second + yPiso);
}

void Personaje::setPosicionUn(float x, float y)
{
	posicionUn = std::make_pair(x, y);
}

void Personaje::actualizar(float xNuevo, float yNuevo)
{
	setPosicionUn(xNuevo, yNuevo);
}


Personaje::~Personaje()
{
}

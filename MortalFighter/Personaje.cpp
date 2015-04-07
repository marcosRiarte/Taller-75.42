#include "stdafx.h"
#include "Personaje.h"
#include "Parser.h"
#include "ManejadorULogicas.h"
#include "Sprites.h"


Personaje::Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string spritesPersonaje)
{
	ancho = anchoPersonaje;
	alto = altoPersonaje;
	zIndex = zIndexPersonaje;
	energy = 100;
	sprites = new Sprites(spritesPersonaje); //Creo la clase sprites con el path del personaje
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

 Sprites& Personaje::getSprites() const
{
	return *sprites;
}

std::pair<int, int> Personaje::getPosicionPx() const
{	
	ManejadorULogicas manejador;
	float yPiso = Parser::getInstancia().getEscenario().getYPiso() + alto/2;

	return manejador.obtenerPosicionPx(posicionUn.first, posicionUn.second + yPiso); 
}


std::pair<float, float> Personaje::getPosicionUn()const
{
	return posicionUn;
}

void Personaje::setPosicionUn(float x, float y)
{
	posicionUn = std::make_pair(x, y);
}

ESTADO Personaje::getEstado() const
{
	return estadoActual;
}

void Personaje::setEstado(ESTADO nuevoEstado)
{
	estadoActual = nuevoEstado;
}

void Personaje::actualizar(float xNuevo, float yNuevo, ESTADO nuevoEstado)
{
	setPosicionUn(xNuevo, yNuevo);
	setEstado(nuevoEstado);
}


Personaje::~Personaje()
{
}

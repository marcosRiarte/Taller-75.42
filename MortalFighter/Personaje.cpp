#include "stdafx.h"
#include "Personaje.h"
#include "Parser.h"
#include "ManejadorULogicas.h"
#include "Sprites.h"

//xjose 9 modifico la clase .... hay unas cosas raras.... QuietoPersonaje???.....

Personaje::Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string unaorientacion, std::string spritesPersonaje, std::string CaminarParaAdelante, std::string CaminarParaAtras, std::string QuietoPersonaje, std::string SaltoPersonaje, std::string SaltoDiagonalPersonaje, std::string CaidaPersonaje)
{
	ancho = anchoPersonaje;
	alto = altoPersonaje;
	zIndex = zIndexPersonaje;
	orientacion = unaorientacion;
	energy = 100;
	sprites = spritesPersonaje;
	caminaradelante = CaminarParaAdelante;
	caminaratras = CaminarParaAtras;
	quieto = QuietoPersonaje;
	salto = SaltoPersonaje;
	saltodiagonal = SaltoDiagonalPersonaje;
	caida = CaidaPersonaje;
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

std::string Personaje::getSprite() const
{
	return sprites;
}

//xjose agrego los famosos metodos......

std::string Personaje::getCaminarParaAdelante() const
{
	return caminaradelante;
}

std::string Personaje:: getCaminarParaAtras() const
{
	return caminaratras;
}

std::string Personaje::getQuieto() const
{
	return quieto;
}

std::string Personaje::getSalto() const
{
	return salto;
}

std::string Personaje::getSaltoDiagonal() const
{
	return saltodiagonal;
}

std::string Personaje::getCaida() const
{
	return caida;
}


//***************************************
std::string Personaje::getOrientacion() const
{
	return orientacion;
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

float Personaje::getDeltaX() const
{
	return deltaX;
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
	deltaX = posicionUn.first - xNuevo;
	setPosicionUn(xNuevo, yNuevo);
	setEstado(nuevoEstado);
}


Personaje::~Personaje()
{
}

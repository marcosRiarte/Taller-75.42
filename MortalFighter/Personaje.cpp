#include "stdafx.h"
#include "Personaje.h"
#include "Parser.h"
#include "ManejadorULogicas.h"
#include "Sprites.h"



Personaje::Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string unaorientacion, std::string spritesPersonaje, std::string CaminarParaAdelante, std::string CaminarParaAtras, std::string QuietoPersonaje, std::string SaltoPersonaje, std::string SaltoDiagonalPersonaje, std::string CaidaPersonaje, std::string nombrePersonaje)
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
	nombreP = nombrePersonaje;
	sensores.push_back(new Sensor(posicionUn, ancho, alto, false));
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

std::vector<Sensor*> Personaje::getSensores()
{
	return sensores;
}


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

std::string Personaje::getNombre() const
{
	return nombreP;
}


//***************************************
std::string Personaje::getOrientacion() const
{
	return orientacion;
}

std::pair<int, int> Personaje::getPosicionPx() const
{
	ManejadorULogicas manejador;	
	float yCorrido = Parser::getInstancia().getEscenario().getAlto() - alto;
	float yRel = yCorrido - posicionUn.second;

	int yRelPx = manejador.darLongPixels(yRel, Parser::getInstancia().getVentana().getAltoPx(), Parser::getInstancia().getEscenario().getAlto());
	int xRelPx = manejador.darLongPixels(posicionUn.first);

	return std::make_pair(xRelPx, yRelPx);
}


std::pair<float, float> Personaje::getPosicionUn()const
{
	return posicionUn;
}

void Personaje::setPosicionUn(float x, float y)
{
	posicionUn = std::make_pair(x, y);
	sensores.at(0)->setPosicion(posicionUn);
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
	for (size_t j = 0; j < sensores.size(); j++) {
		delete sensores.at(j);
	}
}

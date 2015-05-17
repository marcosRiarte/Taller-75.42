#include "stdafx.h"
#include "Personaje.h"
#include "Parser.h"
#include "ManejadorULogicas.h"
#include "Sprites.h"

Personaje::Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string unaorientacion, std::string spritesDirPersonaje, std::string nombrePersonaje)
{
	ancho = anchoPersonaje;
	alto = altoPersonaje;
	zIndex = zIndexPersonaje;
	orientacion = unaorientacion;
	vida = 100;
	spritesDir = spritesDirPersonaje;
	sprites = new Sprite(spritesDir);	
	nombreP = nombrePersonaje;
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

std::string Personaje::getSpriteDir() const
{
	return spritesDir;
}

Sprite* Personaje::getSprite() const
{
	return sprites;
}

int Personaje::getVida()
{
	return vida;
}



int Personaje::descontarVida(ESTADO estadoPj, ESTADO estadoPj2)
{
	if (estadoPj.accion==GUARDIA){
		switch (estadoPj2.accion){
		case PATADA_ALTA:
			vida = vida - 5;
			break;
		case PATADA_BAJA:
			vida = vida - 5;
			break;
		case GOLPE_BAJO:
			vida = vida - 3;
			break;
		case GOLPE_ALTO:
			vida = vida - 3;
			break;
		case GANCHO:
			vida = vida - 10;
			break;
		case ARMA_ARROJABLE:
			vida = vida - 10;
			break;
		default:
			vida = vida - 5;
			break;
		}
	}
	else{
		switch (estadoPj2.accion){
		case PATADA_ALTA:
			vida = vida - 10;
			break;
		case PATADA_BAJA:
			vida = vida - 10;
			break;
		case GOLPE_BAJO:
			vida = vida - 6;
			break;
		case GOLPE_ALTO:
			vida = vida - 6;
			break;
		case GANCHO:
			vida = vida - 20;
			break;
		case ARMA_ARROJABLE:
			vida = vida - 20;
			break;
		default:
			vida = vida - 10;
			break;
		}
	}
	if (vida <= 0)
		return REINICIAR;
	return CONTINUAR;
}

std::string Personaje::getNombre() const
{
	return nombreP;
}
void Personaje::setNombre(std::string unNombre)
{
	nombreP = unNombre;
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

std::pair<int, int> Personaje::getPosicionPx(int altoSprite) const
{
	ManejadorULogicas manejador;
	float yCorrido = Parser::getInstancia().getEscenario().getAlto() - altoSprite + alto/4 ;
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

//SETTERS
void Personaje::setDeltaX(float unDeltaX){
	deltaX = unDeltaX;
}

void Personaje::setAncho(float unAncho){
	ancho = unAncho;
}

void Personaje::setAlto(float unAlto){
	alto = unAlto;
}

void Personaje::setZIndex(int unZindex){
	zIndex = unZindex;
}

void Personaje::setOrientacion(std::string unaOrientacion){
	orientacion = unaOrientacion;
}

void Personaje::setSprites(std::string unosSprites){
	delete sprites;
	spritesDir = unosSprites;
	sprites = new Sprite(spritesDir);
}


void Personaje::actualizar(float xNuevo, float yNuevo, ESTADO nuevoEstado)
{
	deltaX = posicionUn.first - xNuevo;	
	setPosicionUn(xNuevo, yNuevo);	
	setEstado(nuevoEstado);
}

Personaje::~Personaje()
{
	delete sprites;
}
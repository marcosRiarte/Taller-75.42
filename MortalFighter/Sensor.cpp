#include "stdafx.h"
#include "Sensor.h"


Sensor::Sensor(std::pair<float, float> unaposicion, int unancho, int unalto, bool valorHitBox, std::string unestadoStr)
{
	ancho = unancho;
	alto = unalto;
	posicion = unaposicion;
	esHitBox = valorHitBox;
	estadoStr = unestadoStr;
}

void Sensor::setPosicion(std::pair<float, float> unaposicion){
	posicion = unaposicion;
}

void Sensor::setAlto(int unalto){
	alto = unalto;
}

void Sensor::setHitbox(bool valorHitBox){
	esHitBox = valorHitBox;
}

bool Sensor::getHitbox(){
	return esHitBox;
}

void Sensor::setAncho(int unancho){
	ancho = unancho;
}

std::pair<float, float> Sensor::getPosicion(){
	return posicion;
}

int Sensor::getAlto(){
	return alto;
}

int Sensor::getAncho(){
	return ancho;
}

bool Sensor::hayInterseccion(std::pair<float, float> unaPosicion, int unAncho, int unAlto){
	if ((unaPosicion.first + unAncho < posicion.first) || (unaPosicion.first > ancho + posicion.first) || (unaPosicion.second + unAlto < posicion.second) || (unaPosicion.second > posicion.second+alto)){
		return false;
	}
	return true;
}


std::string Sensor::getEstadoStr() const
{
	return estadoStr;
}

Sensor::~Sensor()
{
}
#include "stdafx.h"
#include "Sensor.h"


Sensor::Sensor(std::pair<float, float> unaposicion, float unancho, float unalto, bool valorHitBox)
{
	ancho = unancho;
	alto = unalto;
	posicion = unaposicion;
	esHitBox = valorHitBox;
}

void Sensor::setPosicion(std::pair<float, float> unaposicion){
	posicion = unaposicion;
}

void Sensor::setAlto(float unalto){
	alto = unalto;
}

void Sensor::setHitbox(bool valorHitBox){
	esHitBox = valorHitBox;
}

bool Sensor::getHitbox(){
	return esHitBox;
}

void Sensor::setAncho(float unancho){
	ancho = unancho;
}

std::pair<float, float> Sensor::getPosicion(){
	return posicion;
}

float Sensor::getAlto(){
	return alto;
}

float Sensor::getAncho(){
	return ancho;
}

bool Sensor::hayInterseccion(std::pair<float, float> unaPosicion, float unAncho, float unAlto){
	if ((unaPosicion.first + unAncho < posicion.first) || (unaPosicion.first > ancho + posicion.first) || (unaPosicion.second + unAlto < posicion.second) || (unaPosicion.second > posicion.second+alto)){
		return false;
	}
	return true;
}


Sensor::~Sensor()
{
}

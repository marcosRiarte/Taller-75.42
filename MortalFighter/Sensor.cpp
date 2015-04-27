#include "stdafx.h"
#include "Sensor.h"


Sensor::Sensor(std::pair<float, float> unaposicion, float unalto, float unancho)
{
	ancho = unancho;
	alto = unalto;
	posicion = unaposicion;
}

void Sensor::setPosicion(std::pair<float, float> unaposicion){
	posicion = unaposicion;
}

void Sensor::setAlto(float unalto){
	alto = unalto;
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


Sensor::~Sensor()
{
}

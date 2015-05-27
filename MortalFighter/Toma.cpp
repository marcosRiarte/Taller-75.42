#include "stdafx.h"
#include "Toma.h"


Toma::Toma()
{
	movimientos = std::vector<MOV_TIPO>();
	error = 0;
	nombre = "";
}


void Toma::setNombre(std::string unNombre){
	nombre = unNombre;
}


void Toma::setMovimiento(MOV_TIPO unMovimiento){
	movimientos.push_back(unMovimiento);
}


void Toma::setError(int unError){
	error = unError;
}


std::string Toma::getNombre(){
	return nombre;
}


int Toma::getError(){
	return error;
}


std::vector<MOV_TIPO>* Toma::getMovimientos(){
	return &movimientos;
}


Toma::~Toma()
{
	movimientos.clear();
	nombre.clear();
	error = 0;
}

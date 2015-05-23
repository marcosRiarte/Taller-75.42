#include "stdafx.h"
#include "Pelea.h"


Pelea::Pelea()
{
	personaje1 = nullptr;
	personaje2 = nullptr;
}


void Pelea::setPersonaje1(Personaje* unPersonaje){
	personaje1 = unPersonaje;
}


void Pelea::setPersonaje2(Personaje* unPersonaje){
	personaje2 = unPersonaje;
}


Personaje* Pelea::getPersonaje1(){
	return personaje1;
}


Personaje* Pelea::getPersonaje2(){
	return personaje2;
}


Pelea::~Pelea()
{
	personaje1 = nullptr;
	personaje2 = nullptr;
}

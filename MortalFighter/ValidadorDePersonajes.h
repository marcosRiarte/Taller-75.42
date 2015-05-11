#pragma once
#include "Validador.h"
class ValidadorDePersonajes :
	public Validador
{
private:
	std::vector<Personaje*>* personajes;

	void validarPersonaje();

public:
	ValidadorDePersonajes();
	bool validarPersonajesDesdeConEscenarioYventana(Json::Value personajesParseados, Escenario* unEscenario, Ventana* unaVentana);
	std::vector<Personaje*>* getPersonajes();
	~ValidadorDePersonajes();
};


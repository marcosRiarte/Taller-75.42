#pragma once
#include "Capa.h"
#include "Personaje.h"
#include "Ventana.h"
#include "Escenario.h"

class Parser
{
public:
	Parser(std::string nombreDelArchivo);
	~Parser();
private:
	std::vector<Capa*> Capas;
	Personaje* unPersonaje;
	Ventana* unaVentana;
	Escenario* unEscenario;

};


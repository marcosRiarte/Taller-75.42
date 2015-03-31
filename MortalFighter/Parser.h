#pragma once
#include "Capa.h"
#include "Personaje.h"
#include "Ventana.h"
#include "Escenario.h"

class Parser
{
public:	
	static Parser& getInstancia();
	bool parsear(std::string nombreDelArchivo);

	Escenario& getEscenario() const;
	Ventana& getVentana() const;
	Personaje& getPersonaje() const;

	static void FreeInstancia();

private:
	//Constructor privado
	explicit Parser();

	std::vector<Capa*> Capas;
	Personaje* unPersonaje;
	Ventana* unaVentana;
	Escenario* unEscenario;
	

	
	virtual ~Parser();


	Parser(Parser const&) = delete;
	void operator=(Parser const&) = delete;

};

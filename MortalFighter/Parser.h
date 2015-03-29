#pragma once
#include "Capa.h"
#include "Personaje.h"
#include "Ventana.h"
#include "Escenario.h"

class Parser
{
public:
	static Parser& getInstancia(std::string nombreDelArchivo);
	static Parser& getInstancia();
	bool parsear(std::string nombreDelArchivo);

	Escenario& getEscenario() const;

	static void FreeInstancia();

private:
	//Constructor privado
	Parser(std::string nombreDelArchivo);	

	std::vector<Capa*> Capas;
	Personaje* unPersonaje;
	Ventana* unaVentana;
	Escenario* unEscenario;
	
	explicit Parser();
	
	virtual ~Parser();


	Parser(Parser const&) = delete;
	void operator=(Parser const&) = delete;

};

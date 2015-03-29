#pragma once
#include "Capa.h"
#include "Personaje.h"
#include "Ventana.h"
#include "Escenario.h"

class Parser
{
public:
	static Parser& getInstancia()
	{
		static Parser instancia; // Se garantiza que será destruido.
		// Se instancia en el primer uso.
		return instancia;
	}

	static void FreeInstancia();

private:
	//Constructor privado
	Parser(std::string nombreDelArchivo){};

	std::vector<Capa*> Capas;
	Personaje* unPersonaje;
	Ventana* unaVentana;
	Escenario* unEscenario;
	static Parser* instancia;
	explicit Parser();
	
	virtual ~Parser();


	Parser(Parser const&) = delete;
	void operator=(Parser const&) = delete;

};

Parser::~Parser() {
}
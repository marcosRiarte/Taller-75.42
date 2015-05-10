#pragma once
#include "Capa.h"
#include "Ventana.h"
#include "Escenario.h"
#include "Personaje.h"
#include "Controlador.h"
#include "Log.h"
#include "Validador.h"
#include "ValidadorDeVentana.h"

class Parser
{
public:	
	static Parser& getInstancia();
	bool parsear(std::string nombreDelArchivo);

	Escenario& getEscenario() const;
	Ventana& getVentana() const;
	Controlador* getControlador1();
	Controlador* getControlador2();
	std::vector<Personaje*> getPersonajes() const;
	std::vector<Capa*> getCapas() const;
	std::vector<int> getColorAlternativo();
	std::string Parser::getPelea() const;
	static void FreeInstancia();

private:	
	//Constructor privado
	explicit Parser();
	
	std::vector<Capa*> Capas;
	std::vector<Personaje*> Personajes;	
	ValidadorDeVentana* validadorDeVentana;
	Escenario* unEscenario;
	Controlador* controlador1;
	Controlador* controlador2;
	std::string pelea;
	std::vector<int> colorAlternativo;
	virtual ~Parser();

	Parser(Parser const&) = delete;
	void operator =(Parser const&) = delete;	
};

#pragma once
#include "Capa.h"
#include "Ventana.h"
#include "Escenario.h"
#include "Personaje.h"
#include "Controlador.h"
#include "Log.h"
#include "Validador.h"
#include "ValidadorDeVentana.h"
#include "ValidadorDeEscenario.h"
#include "ValidadorDeCapas.h"
#include "ValidadorDePersonajes.h"
#include "ValidadorDelControlador.h"
#include "ValidadorDePelea.h"

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
	
	ValidadorDeCapas* validadorDeCapas;
	ValidadorDePersonajes* validadorDePersonajes;
	ValidadorDeVentana* validadorDeVentana;
	ValidadorDeEscenario* validadorDeEscenario;
	ValidadorDelControlador* validadorDelControlador;
	ValidadorDePelea* validadorDePelea;
	std::vector<int> colorAlternativo;
	virtual ~Parser();

	Parser(Parser const&) = delete;
	void operator =(Parser const&) = delete;	
};

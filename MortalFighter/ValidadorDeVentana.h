#pragma once
#include "Validador.h"
#include "Parser.h"

class ValidadorDeVentana :
	public Validador
{
private:
	Ventana* ventana;

public:
	ValidadorDeVentana();
	void validarVentanaDesde(Json::Value unaVentana);
	Ventana* getVentana();
	~ValidadorDeVentana();
};


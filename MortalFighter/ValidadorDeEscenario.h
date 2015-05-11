#pragma once
#include "Validador.h"
class ValidadorDeEscenario :
	public Validador
{
private:
	Escenario* escenario;

public:
	ValidadorDeEscenario();
	void validarEscenarioDesde(Json::Value unEscenario);
	Escenario* getEscenario();
	void validaryPisoCon(float altoPersonaje);
	~ValidadorDeEscenario();
};


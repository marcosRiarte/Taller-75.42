#pragma once
#include "ControladorDeTomas.h"

class ValidadorDeTomas
{
public:
	ValidadorDeTomas();
	void validarTomasDeseParaControladorDeTomas(Json::Value tomas, ControladorDeTomas* controladorDeTomas);
	~ValidadorDeTomas();

private:
	std::vector<MOV_TIPO> vecMovimientos;
};


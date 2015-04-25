#include "stdafx.h"
#include "Controlador.h"

Controlador::Controlador()
{
	movimientos = std::vector<MOV_TIPO>();
}


std::vector<MOV_TIPO> Controlador::getMovimientos(){
	return movimientos;
}


Controlador::~Controlador()
{
}
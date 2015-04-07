#pragma once
#include "stdafx.h"

class Validador
{
public:
	static void ValidarVentana(int* anchoPxVentana, int* altoPxVentana, float* anchoVentana);
	static void ValidarCapas(float* anchoCapas);
	static void ValidarEscenario(float *anchoEscenario, float *altoEscenario, float* yPisoEscenario);
	static void ValidarPersonaje(float *ancho, float* alto, int* zindex, std::string* orientacion, std::string* sprites);
};

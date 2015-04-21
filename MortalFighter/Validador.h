#pragma once
#include "stdafx.h"
#include "Parser.h"

class Validador
{
public:
	static void ValidarVentana(int* anchoPxVentana, int* altoPxVentana, float* anchoVentana);
	
	static void ValidarCapas(float* anchoCapas, std::string* fondo, size_t numerocapa);
	static void ValidarEscenario(float *anchoEscenario, float *altoEscenario, float* yPisoEscenario);
	
	static void ValidarPersonaje(float *ancho, float* alto, int* zindex, std::string* orientacion, std::string* sprites, std::string* CaminarParaAdelante, std::string* CaminarParaAtras, std::string* Quieto, std::string* Salto, std::string* SaltoDiagonal, std::string* Caida);
};

#pragma once
#include "stdafx.h"
#include "Parser.h"

class Validador
{
public:
	static void ValidarVentana(int* anchoPxVentana, int* altoPxVentana, float* anchoVentana);
	//xjose 1000 agrego el fondo para validar por que si no existe..... explota!
	static void ValidarCapas(float* anchoCapas, std::string* fondo);
	static void ValidarEscenario(float *anchoEscenario, float *altoEscenario, float* yPisoEscenario);
	//xjose 6 modifico la firma del validador
	static void ValidarPersonaje(float *ancho, float* alto, int* zindex, std::string* orientacion, std::string* sprites, std::string* CaminarParaAdelante, std::string* CaminarParaAtras, std::string* Quieto, std::string* Salto, std::string* SaltoDiagonal, std::string* Caida);
};

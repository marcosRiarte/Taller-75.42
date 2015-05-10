#pragma once
#include "stdafx.h"

class Validador
{
public:
	
	static bool ValidarCapas(float* anchoCapas, std::string* fondo, size_t numerocapa);
	
	static bool ValidarPersonaje(float *ancho, float* alto, int* zindex, std::string* orientacion, std::string* sprites, std::string* CaminarParaAdelante, std::string* CaminarParaAtras, std::string* Quieto, std::string* Salto, std::string* SaltoDiagonal, std::string* Caida);
};

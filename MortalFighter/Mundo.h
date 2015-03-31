#pragma once
#include "Cuerpo.h"

class Mundo
{
public:
	Mundo();
private:
	float gravedad;
	std::vector<Cuerpo> Cuerpos;
};
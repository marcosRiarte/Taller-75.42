#pragma once
#include "Cuerpo.h"

class Mundo
{
public:
	Mundo();
	void Paso(float difTiempo);
	void Resolver(float difTiempo, Cuerpo &unCuerpo);

	
private:
	vector2D gravedad;	
	std::vector<Cuerpo> Cuerpos;
};
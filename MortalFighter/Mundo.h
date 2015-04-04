#pragma once
#include "Cuerpo.h"
#include "Controlador.h"
#include "Escenario.h"

#define GRAVEDAD_Y -10.0f

class Mundo
{
public:
	Mundo();
	Mundo(const vector2D& valorGravedad);
	void agregarCuerpo(Cuerpo *unCuerpo);
	void Paso(float difTiempo, MOV_TIPO movimiento);
	void Resolver(float difTiempo, Cuerpo *unCuerpo, MOV_TIPO movimiento);


private:
	vector2D gravedad;	
	std::vector<Cuerpo*> Cuerpos;
};
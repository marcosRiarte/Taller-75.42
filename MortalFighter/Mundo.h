#pragma once
#include "Cuerpo.h"
#include "Controlador.h"
#include "Escenario.h"

#define GRAVEDAD_Y -1.0f

class Mundo
{
public:
	Mundo();
	Mundo(const vector2D& valorGravedad);
	void agregarCuerpo(Cuerpo *unCuerpo);
	void Paso(float difTiempo, Controlador::MOV_TIPO movimiento);
	void Resolver(float difTiempo, Cuerpo *unCuerpo, Controlador::MOV_TIPO movimiento);


private:
	vector2D gravedad;	
	std::vector<Cuerpo*> Cuerpos;
};
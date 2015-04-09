#pragma once
#include "Controlador.h"
#include "Cuerpo.h"
#include "Escenario.h"
#define SALTO_Y 400.0f
#define SALTO_X 100.0f
#define GRAVEDAD_Y -10.0f
#define DISTANCIA 2.0f

class Cuerpo;

class Mundo
{
public:
	Mundo();
	Mundo(const vector2D& valorGravedad);
	void agregarCuerpo(Cuerpo *unCuerpo);
	void Paso(float difTiempo, MOV_TIPO movimiento);
	ESTADO Resolver(float difTiempo, Cuerpo *unCuerpo, MOV_TIPO movimiento);
	float getYPiso() const;

private:
	vector2D gravedad;
	float yPiso;
	std::vector<Cuerpo*> Cuerpos;
};
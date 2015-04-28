#pragma once
#include "Controlador.h"
#include "Cuerpo.h"
#include "Escenario.h"
#define SALTO_Y 480.0f
#define SALTO_X 160.0f
#define GRAVEDAD_Y -8.0f
#define DISTANCIA 2.0f
#define FACTOR_DIST_REVERSA 0.6f

class Cuerpo;

class Mundo
{
public:
	Mundo();
	Mundo(const vector2D& valorGravedad);
	void agregarCuerpo(Cuerpo *unCuerpo);
	void Paso(float difTiempo);
	ESTADO Resolver(float difTiempo, Cuerpo *unCuerpo);
	float getYPiso() const;
	void FrenarCuerpos();
	void LiberarCuerpos();
	Cuerpo* getCuerpo(size_t pos);

private:
	vector2D gravedad;
	float yPiso;
	std::vector<Cuerpo*> Cuerpos;
};
#pragma once
#include "Controlador.h"
#include "Cuerpo.h"
#include "Escenario.h"
#include "Sprites.h"

#define SALTO_Y 480.0f
#define SALTO_X 160.0f
#define GRAVEDAD_Y -8.0f
#define DISTANCIA 2.0f
#define FACTOR_DIST_REVERSA 0.6f
#define DEFAULT_ESTA_GOLPEADO false// sacarla, esta para testear rapido
class Cuerpo;

class Mundo
{
public:
	Mundo();
	Mundo(const vector2D& valorGravedad, Sprite* unSprite);
	void agregarCuerpo(Cuerpo *unCuerpo);
	int Paso(float difTiempo);
	ESTADO Resolver(float difTiempo, Cuerpo *unCuerpo);
	float getYPiso() const;
	void FrenarCuerpos();
	void LiberarCuerpos();
	Cuerpo* getCuerpo(size_t pos);

private:
	vector2D gravedad;
	Sprite* elSprite;
	ESTADO estadoAnteriorPj1;
	ESTADO estadoAnteriorPj2;
	float yPiso;
	std::vector<Cuerpo*> Cuerpos;
	bool hayInterseccion(std::pair<int, int> unaPosicion, int unAncho, int unAlto, std::pair<int, int> otraPos, int otroAncho, int otoAlto);
	bool Mundo::DeterminarSuperposicionDeCuerpos();
	void Mundo::ResolverColisiones(Cuerpo *unCuerpo);
	void Mundo::ResolverSaltos(Cuerpo *unCuerpo);

};
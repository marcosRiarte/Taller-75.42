#pragma once
#include "Controlador.h"
#include "Cuerpo.h"
#include "Escenario.h"
#include "Sprites.h"

#define SALTO_Y 510.0f
#define SALTO_X 130.0f
#define GRAVEDAD_Y -8.0f
#define DISTANCIA 2.0f
#define DISTANCIAPROYECTIL 6.0f
#define FACTOR_DIST_REVERSA 0.6f
#define DEFAULT_ESTA_GOLPEADO false// sacarla, esta para testear rapido
class Cuerpo;

class Mundo
{
public:
	Mundo();
	Mundo(const vector2D& valorGravedad);
	void agregarCuerpo(Cuerpo *unCuerpo);
	int Paso(float difTiempo);
	ESTADO Resolver(float difTiempo, Cuerpo *unCuerpo);
	float getYPiso() const;
	void FrenarCuerpos();
	void LiberarCuerpos();
	Cuerpo* getCuerpo(size_t pos);
	Sensor* getProyectil(size_t pos);

private:
	vector2D gravedad;	
	ESTADO estadoAnteriorPj1;
	ESTADO estadoAnteriorPj2;
	float yPiso;
	Sensor* proyectilAnterior;
	std::vector<Cuerpo*> Cuerpos;
	bool hayInterseccion(std::pair<float, float> unaPosicion, float unAncho, float unAlto, std::pair<float, float> otraPos, float otroAncho, float otroAlto);
	bool haySuperposicion(Cuerpo *unCuerpo, Cuerpo *elOtroCuerpo, bool invertido);

	void ResolverGolpiza(Cuerpo* unCuerpo, Cuerpo* elOtroCuerpo, bool invertido);
	void ResolverArma(Cuerpo* unCuerpo, Cuerpo* elOtroCuerpo, Sensor* proyectil, bool invertido);
	void resolverChoque(Sensor* proyectilUno, Sensor* proyectilDos);

	void moverCuerpos(Cuerpo *unCuerpo, Cuerpo *elOtroCuerpo, bool invertido);

	ESTADO ResolverColisiones(float difTiempo, Cuerpo *unCuerpo, ESTADO nuevoEstado);
	ESTADO ResolverSaltos(float difTiempo, Cuerpo *unCuerpo, Cuerpo *elOtroCuerpo, ESTADO nuevoEstado, bool invertido, std::vector<MOV_TIPO>* movimientos);
	ESTADO ResolverAcciones(float difTiempo, Cuerpo *unCuerpo, Cuerpo *otroCuerpo, ESTADO nuevoEstado, bool invertido, std::vector<MOV_TIPO>* movimientos);

};
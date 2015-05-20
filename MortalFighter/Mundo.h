#pragma once
#include "Controlador.h"
#include "Cuerpo.h"
#include "Escenario.h"
#include "Sprites.h"

#define SALTO_Y 500.0f
#define SALTO_X 130.0f
#define GRAVEDAD_Y -8.0f
#define DISTANCIA 2.0f
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
	Cuerpo* getProyectil(size_t pos);
private:
	vector2D gravedad;	
	ESTADO estadoAnteriorPj1;
	ESTADO estadoAnteriorPj2;
	float yPiso;
	std::vector<Cuerpo*> Cuerpos;
	std::vector<Cuerpo*> Proyectiles;
	bool hayInterseccion(std::pair<int, int> unaPosicion, int unAncho, int unAlto, std::pair<int, int> otraPos, int otroAncho, int otoAlto);
	bool haySuperposicion(Cuerpo *unCuerpo, Cuerpo *elOtroCuerpo, bool invertido);

	void ResolverGolpiza(Cuerpo* unCuerpo, Cuerpo* elOtroCuerpo, bool invertido);

	void moverCuerpos(Cuerpo *unCuerpo, Cuerpo *elOtroCuerpo, bool invertido);

	ESTADO ResolverColisiones(Cuerpo* unCuerpo, Cuerpo* elOtroCuerpo, bool invertido, ESTADO nuevoEstado);
	ESTADO ResolverGolpes(Cuerpo* unCuerpo, Cuerpo* elOtroCuerpo, bool invertido, ESTADO nuevoEstado);
	ESTADO ResolverSaltos(float difTiempo, Cuerpo *unCuerpo, Cuerpo *elOtroCuerpo, ESTADO nuevoEstado, bool invertido, std::vector<MOV_TIPO>* movimientos);
	ESTADO ResolverAcciones(float difTiempo, Cuerpo *unCuerpo, Cuerpo *otroCuerpo, ESTADO nuevoEstado, bool invertido, std::vector<MOV_TIPO>* movimientos);

};
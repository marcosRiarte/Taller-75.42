#pragma once
#include "Sprites.h"

enum Movimientos
{
	PARADO, CAMINARDER, CAMINARIZQ, AGACHADO, SALTO, SALTODIAGIZQ, SALTODIAGDER
};

enum Acciones
{
	SIN_ACCION, GUARDIA, GANCHO, PATADA_ALTA, PATADA_BAJA, GOLPE_ALTO, GOLPE_BAJO, ARMA_ARROJABLE
};
enum Golpeado
{
	NOGOLPEADO, GOLPEADO,FALLECIDO
};

struct ESTADO {
	Movimientos movimiento;
	Acciones accion;
	Golpeado golpeado;
};

class Personaje
{
public:
	std::string nombre;
	Personaje::Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string unaorientacion, std::string spritesDirPersonaje, std::string nombrePersonaje);
	float getAncho() const;
	float getAlto() const;
	int getZIndex() ;
	int descontarVida(ESTADO estadoPj, ESTADO estadoPj2);
	int getVida();
	std::string getOrientacion() const;
	std::string getSpriteDir() const;	
	Sprite* getSprite() const;
	std::string getNombre() const;

	std::pair<int, int> getPosicionPx() const;
	std::pair<int, int> Personaje::getPosicionPx(int altoSprite) const;
	void setPosicionUn(float x, float y);
	ESTADO getEstado() const;
	void setEstado(ESTADO nuevoEstado);
	float getDeltaX() const;	
	virtual void actualizar(float xNuevo, float yNuevo, ESTADO estadoJugador);	
	std::pair<float, float> Personaje::getPosicionUn()const;	

	//SETTERS
	void setDeltaX(float unDeltaX);
	void setAncho(float unAncho);
	void setAlto(float unAlto);
	void setZIndex(int unZindex);
	void setOrientacion(std::string unaOrientacion);
	void setSprites(std::string unosSprites);
	
	void setNombre(std::string unNombre);
	


	~Personaje();

private:
	float ancho;
	float alto;
	int zIndex;
	int vida;	
	std::string orientacion;
	std::string spritesDir;	
	std::string nombreP;
	
	Sprite* sprites;
	std::pair<float, float> posicionUn;
	float deltaX;	
	ESTADO estadoActual;
};


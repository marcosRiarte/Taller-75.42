#pragma once
#include "Sprites.h"

class Personaje
{
public:
	Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string spritesPersonaje);
	float getAncho() const;
	float getAlto() const;
	int getZIndex() ;
	Sprites getSprites();
	std::pair<int, int> getPosicionPx() const;
	void setPosicionUn(float x, float y);
	enum ESTADO getEstado();
	void setEstado(enum ESTADO nuevoEstado);
	virtual void actualizar(float xNuevo, float yNuevo);
	enum ESTADO { QUIETODER, QUIETOIZQ, DER, IZQ, ARRIBA, ABAJO, SALTOIZQ, SALTODER};
	std::pair<float, float> Personaje::getPosicionUn()const;
	~Personaje();

private:
	float ancho;
	float alto;
	int zIndex;
	int energy;
	Sprites sprites;
	std::pair<float, float> posicionUn;
	ESTADO elEstado;
};


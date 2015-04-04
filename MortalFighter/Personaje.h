#pragma once


class Personaje
{
public:
	Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string spritesPersonaje);
	float getAncho() const;
	float getAlto() const;
	int getZIndex() const;
	std::string getSprites() const;
	std::pair<int, int> getPosicionPx() const;
	void setPosicionUn(float x, float y);

	virtual void actualizar(float xNuevo, float yNuevo);
	enum ESTADO { QUIETODER, QUIETOIZQ, DER, IZQ, ARRIBA, ABAJO, SALTOIZQ, SALTODER};

	~Personaje();

private:
	float ancho;
	float alto;
	int zIndex;
	int energy;
	std::string sprites;
	std::pair<float, float> posicionUn;
	ESTADO elEstado;
};


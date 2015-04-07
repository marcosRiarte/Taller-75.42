#pragma once

enum ESTADO {
	QUIETODER, QUIETOIZQ, DER_DER, DER_IZQ, IZQ_DER, IZQ_IZQ, ARRIBA_DER, ARRIBA_IZQ,
	ABAJO_DER, ABAJO_IZQ, SALTOIZQ_DER, SALTOIZQ_IZQ, SALTODER_DER, SALTODER_IZQ
};

class Personaje
{
public:
	
	Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string orientacion, std::string spritesPersonaje);
	float getAncho() const;
	float getAlto() const;
	int getZIndex() ;
	std::string getSprite() const;
	std::pair<int, int> getPosicionPx() const;
	void setPosicionUn(float x, float y);
	ESTADO getEstado() const;
	void setEstado(ESTADO nuevoEstado);
	float getDeltaX() const;
	virtual void actualizar(float xNuevo, float yNuevo, ESTADO);	
	std::pair<float, float> Personaje::getPosicionUn()const;
	~Personaje();

private:
	float ancho;
	float alto;
	int zIndex;
	int energy;
	std::string orientacion;
	std::string sprites;
	std::pair<float, float> posicionUn;
	float deltaX;
	ESTADO estadoActual;
};


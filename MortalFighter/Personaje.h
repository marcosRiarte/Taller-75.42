#pragma once
#include "Sensor.h"

enum ESTADO {
	QUIETODER, QUIETOIZQ, DER_DER, DER_IZQ, IZQ_DER, IZQ_IZQ, ARRIBA_DER, ARRIBA_IZQ,
	ABAJO_DER, ABAJO_IZQ, SALTOIZQ_DER, SALTOIZQ_IZQ, SALTODER_DER, SALTODER_IZQ
};

class Personaje
{
public:
	
	std::string nombre;
	Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string orientacion, std::string spritesPersonaje, std::string CaminarParaAdelante, std::string CaminarParaAtras, std::string Quieto, std::string Salto, std::string SaltoDiagonal, std::string Caida, std::string nombrePersonaje);
	float getAncho() const;
	float getAlto() const;
	int getZIndex() ;
	std::string getOrientacion() const;
	std::string getSprite() const;
	std::string getCaminarParaAdelante() const;
	std::string getCaminarParaAtras() const;
	std::string getQuieto() const;
	std::string getSalto() const;
	std::string getSaltoDiagonal() const;
	std::string getCaida() const;
	std::string getNombre() const;
	std::pair<int, int> getPosicionPx() const;
	void setPosicionUn(float x, float y);
	ESTADO getEstado() const;
	void setEstado(ESTADO nuevoEstado);
	float getDeltaX() const;	
	virtual void actualizar(float xNuevo, float yNuevo, ESTADO);	
	std::pair<float, float> Personaje::getPosicionUn()const;
	std::vector<Sensor*> getSensores();
	
	~Personaje();

private:
	float ancho;
	float alto;
	int zIndex;
	int energy;
	std::vector<Sensor*> sensores;
	std::string orientacion;
	std::string sprites;
	std::string caminaradelante;
	std::string caminaratras;
	std::string quieto;
	std::string salto;
	std::string saltodiagonal;
	std::string caida;
	std::string nombreP;
	std::pair<float, float> posicionUn;
	float deltaX;	
	ESTADO estadoActual;
};


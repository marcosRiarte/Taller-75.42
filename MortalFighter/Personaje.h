#pragma once
#include "Sensor.h"



enum Movimientos
{
	PARADO, CAMINARDER, CAMINARIZQ, AGACHADO, SALTO , SALTODIAGIZQ, SALTODIAGDER
};

enum Acciones
{
	GUARDIA, GANCHO, PATADA_ALTA, PATADA_BAJA, GOLPE_ALTO, GOLPE_BAJO, ARMA_ARROJABLE
};

enum Golpeado
{
	GOLPEADO
};

enum ESTADO {
	QUIETODER, QUIETOIZQ, DER_DER, DER_IZQ, IZQ_DER, IZQ_IZQ, ARRIBA_DER, ARRIBA_IZQ,
	ABAJO_DER, ABAJO_IZQ, SALTOIZQ_DER, SALTOIZQ_IZQ, SALTODER_DER, SALTODER_IZQ,
	P_ALTADER,P_ALTAIZQ,GOLPEADOIZQ,GOLPEADODER
};

class Personaje
{
public:
	std::string nombre;
	Personaje::Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string unaorientacion, std::string spritesPersonaje, std::string CaminarParaAdelante, std::string CaminarParaAtras, std::string QuietoPersonaje, std::string SaltoPersonaje, std::string SaltoDiagonalPersonaje, std::string CaidaPersonaje, std::string PatadaAltaPersonaje, std::string GolpeadoPersonaje, std::string AgachadoPersonaje, std::string nombrePersonaje);
	float getAncho() const;
	float getAlto() const;
	int getZIndex() ;
	int getEnergy();
	void setEnergy(int);
	std::string getOrientacion() const;
	std::string getSprite() const;
	std::string getCaminarParaAdelante() const;
	std::string getCaminarParaAtras() const;
	std::string getQuieto() const;
	std::string getSalto() const;
	std::string getSaltoDiagonal() const;
	std::string getCaida() const;
	std::string getNombre() const;
	
	std::string getPatadaAlta() const;
	std::string getAgacharse() const;
	std::string getGolpeado() const;
	std::pair<int, int> getPosicionPx() const;
	void setPosicionUn(float x, float y);
	ESTADO getEstado() const;
	void setEstado(ESTADO nuevoEstado);
	float getDeltaX() const;	
	virtual void actualizar(float xNuevo, float yNuevo, ESTADO);	
	std::pair<float, float> Personaje::getPosicionUn()const;	

	//SETTERS
	void setDeltaX(float unDeltaX);
	void setAncho(float unAncho);
	void setAlto(float unAlto);
	void setZIndex(int unZindex);
	void setOrientacion(std::string unaOrientacion);
	void setSprites(std::string unosSprites);
	void setCaminarParaAdelante(std::string unCaminarParaAdelante);
	void setCaminarParaAtras(std::string unCaminarParaAtras);
	void setQuieto(std::string unQuieto);
	void setSalto(std::string unSalto);
	void setSaltoDiagonal(std::string unSaltoDiagonal);
	void setCaida(std::string UnaCaida);
	void setNombre(std::string unNombre);
	void setPatadaAlta(std::string unaPatadaAlta);
	void setAgacharse(std::string unAgacharse);
	void setGolpeado(std::string unGolpeado);
	
	struct tipo {
		Movimientos movimiento;
		Acciones accion;
		Golpeado golpeado;
	};

	~Personaje();

private:
	float ancho;
	float alto;
	int zIndex;
	int energy;	
	std::string orientacion;
	std::string sprites;
	std::string caminaradelante;
	std::string caminaratras;
	std::string quieto;
	std::string salto;
	std::string saltodiagonal;
	std::string caida;
	std::string nombreP;
	std::string patadaalta;
	std::string agachado;
	std::string golpeado;
	std::pair<float, float> posicionUn;
	float deltaX;	
	ESTADO estadoActual;


};


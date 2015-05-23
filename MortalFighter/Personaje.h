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
	Personaje();
	void copiarAtributosDe(Personaje* unPersonaje);
	Personaje::Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string unaorientacion, std::string spritesDirPersonaje, std::string CaminarParaAdelante, std::string CaminarParaAtras, std::string QuietoPersonaje, std::string SaltoPersonaje, std::string SaltoDiagonalPersonaje, std::string CaidaPersonaje, std::string PatadaAltaPersonaje, std::string GolpeadoPersonaje, std::string AgachadoPersonaje, std::string nombrePersonaje);
	float getAncho() const;
	float getAlto() const;
	int getZIndex() ;
	int descontarVida(ESTADO estadoPj, ESTADO estadoPj2);
	int getVida();
	std::string getOrientacion() const;
	std::string getSpriteDir() const;	
	Sprite* getSprite() const;
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
	std::pair<int, int> Personaje::getPosicionPx(int altoSprite) const;
	void setPosicionUn(float x, float y);
	ESTADO getEstado() const;
	void setEstado(ESTADO nuevoEstado);
	float getDeltaX() const;	
	virtual void actualizar(float xNuevo, float yNuevo, ESTADO estadoJugador);	
	std::pair<float, float> getPosicionUn() const;	

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
	


	~Personaje();

private:
	float ancho;
	float alto;
	int zIndex;
	int vida;	
	std::string orientacion;
	std::string spritesDir;
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
	Sprite* sprites;
	std::pair<float, float> posicionUn;
	float deltaX;	
	ESTADO estadoActual;
};


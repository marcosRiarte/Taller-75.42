#pragma once
#include "Sensor.h"

//xjose1 hay que dividir los enumerados.
/*
yo los clasificaria en
movimientos, golpes, sufriendo
movimientos "quito, saltar, caminar...."
golpes "piña alta, patada, arma"
sufriendo "golpebajo,arrojado,congelado...."

hay que tener un atributo orientacion que determine si esta en orientacion izq o derecha y no duplicar aca estados!
http://stackoverflow.com/questions/18344646/combine-enums-c  ver respuesta de compiancion d enumerados

*/
//
//
//

// usando convencion de controlador .h
//enum MOV_TIPO { QUIETO, DER, IZQ, ARRIBA, ABAJO, SALTOIZQ, SALTODER, DEFENSA, G_BAJO, G_ALTO, G_ABAJO, G_GANCHO, G_SALTO, G_SALTOIZQ, G_SALTODER, P_BAJA, P_ALTA, P_BAJA_ABAJO, P_ALTA_ABAJO, P_SALTO, P_SALTOIZQ, P_SALTODER, ARMA, CERRAR, RECARGAR };

/*
enum tipo {
	Movimientos = 0x100,
	Acciones = 0x200,
	Golpeado = 0x300
};

enum Movimientos
{
	QUIETO = Movimientos, DER, IZQ, AGACHADO, SALTO , SALTOIZQ, SALTODER
};

enum Acciones
{
	DEFENSA = Golpes, GANCHO, PATADA_ALTA, PATADA_BAJA, GOLPE_ALTO, GOLPE_BAJO, ARMA_ARROJABLE
};

enum Golpeado
{
	GOLPEADO = Golpeado
};

constexpr tipo getOperationType(unsigned value) {
	return value & 0xFF00;
}
*/

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
	void getPatadaAlta(std::string unaPatadaAlta);
	void getAgacharse(std::string unAgacharse);
	void getGolpeado(std::string unGolpeado);
	
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


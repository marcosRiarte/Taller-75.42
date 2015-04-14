#pragma once

enum ESTADO {
	QUIETODER, QUIETOIZQ, DER_DER, DER_IZQ, IZQ_DER, IZQ_IZQ, ARRIBA_DER, ARRIBA_IZQ,
	ABAJO_DER, ABAJO_IZQ, SALTOIZQ_DER, SALTOIZQ_IZQ, SALTODER_DER, SALTODER_IZQ
};

class Personaje
{
public:
	//xjose 8 modifico la firma
	Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string orientacion, std::string spritesPersonaje, std::string CaminarParaAdelante, std::string CaminarParaAtras, std::string Quieto, std::string Salto, std::string SaltoDiagonal);
	float getAncho() const;
	float getAlto() const;
	int getZIndex() ;
	std::string getOrientacion() const;
	std::string getSprite() const;
	//xjose... la posta no se nada, invento gets???
	std::string getCaminarParaAdelante() const;
	std::string getCaminarParaAtras() const;
	std::string getQuieto() const;
	std::string getSalto() const;
	std::string getSaltoDiagonal() const;
	std::pair<int, int> getPosicionPx() const;
	void setPosicionUn(float x, float y);
	ESTADO getEstado() const;
	void setEstado(ESTADO nuevoEstado);
	float getDeltaX() const;
	virtual void actualizar(float xNuevo, float yNuevo, ESTADO);	
	std::pair<float, float> Personaje::getPosicionUn()const;
	//xjose que c... es ~ 
	~Personaje();

private:
	float ancho;
	float alto;
	int zIndex;
	int energy;
	std::string orientacion;
	std::string sprites;

	//xjose agrego atributos ?
	std::string caminaradelante;
	std::string caminaratras;
	std::string quieto;
	std::string salto;
	std::string saltodiagonal;

	std::pair<float, float> posicionUn;
	float deltaX;
	ESTADO estadoActual;
};


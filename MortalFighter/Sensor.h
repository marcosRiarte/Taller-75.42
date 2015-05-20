#pragma once
class Sensor
{
public:
	Sensor(std::pair<float, float> posicion, int alto, int ancho, bool esHitBox, std::string unestadoStr);
	
	void setPosicion(std::pair<float, float> posicion);
	void setAlto(int alto);
	void setAncho(int ancho);
	void setHitbox(bool valorHitBox);

	bool getHitbox();
	std::pair<float, float> getPosicion();
	int getAlto();
	int getAncho();
	std::string getEstadoStr() const;

	void moverProyectil(float unaDistancia);
	void resetearPosicionInicial();
	void activarSensor();
	void desactivarSensor();
	bool estaActivo();

	~Sensor();
private:
	std::pair<float, float> posicion;
	std::pair<float, float> posicionInicial;
	int ancho;
	int alto;
	bool esHitBox;
	bool activo;
	std::string estadoStr;
};


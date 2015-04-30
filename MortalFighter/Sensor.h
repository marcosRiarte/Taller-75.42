#pragma once
class Sensor
{
public:
	Sensor(std::pair<float, float> posicion, float alto, float ancho, bool esHitBox);
	
	void setPosicion(std::pair<float, float> posicion);
	void setAlto(float alto);
	void setAncho(float ancho);
	void setHitbox(bool valorHitBox);
	bool hayInterseccion(std::pair<float, float> unaPosicion, float unAncho, float unAlto);

	bool getHitbox();
	std::pair<float, float> getPosicion();
	float getAlto();
	float getAncho();
	
	~Sensor();
private:
	std::pair<float, float> posicion;
	float ancho;
	float alto;
	bool esHitBox;
};


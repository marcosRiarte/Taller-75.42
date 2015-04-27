#pragma once
class Sensor
{
public:
	Sensor(std::pair<float, float> posicion, float alto, float ancho);
	
	void setPosicion(std::pair<float, float> posicion);
	void setAlto(float alto);
	void setAncho(float ancho);

	std::pair<float, float> getPosicion();
	float getAlto();
	float getAncho();

	~Sensor();
private:
	std::pair<float, float> posicion;
	float ancho;
	float alto;
};


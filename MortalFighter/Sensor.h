#pragma once
class Sensor
{
public:
	Sensor(std::pair<float, float> posicion, int alto, int ancho, bool esHitBox, std::string unestadoStr);
	
	void setPosicion(std::pair<float, float> posicion);
	void setAlto(int alto);
	void setAncho(int ancho);
	void setHitbox(bool valorHitBox);
	bool hayInterseccion(std::pair<float, float> unaPosicion, int unAncho, int unAlto);

	bool getHitbox();
	std::pair<float, float> getPosicion();
	int getAlto();
	int getAncho();
	std::string getEstadoStr() const;
	
	~Sensor();
private:
	std::pair<float, float> posicion;
	int ancho;
	int alto;
	bool esHitBox;
	std::string estadoStr;
};


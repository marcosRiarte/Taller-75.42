#pragma once
class Capa
{
public:
	Capa(std::string unaImagenFondo, float unAncho);
	std::string getImagenFondo();
	float getAncho();
	virtual ~Capa();
private:
	std::string imagenFondo;
	float ancho;
};


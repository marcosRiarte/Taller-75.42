#pragma once
class Capa
{
public:
	Capa(std::string unaImagenFondo, float unAncho);
	virtual ~Capa();
private:
	std::string imagenFondo;
	float ancho;
};


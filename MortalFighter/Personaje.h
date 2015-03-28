#pragma once
class Personaje
{
public:
	Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string spritesPersonaje);
	~Personaje();
private:
	float ancho;
	float alto;
	int zIndex;
	std::string sprites;
};


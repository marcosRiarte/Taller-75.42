#pragma once
class Personaje
{
public:
	Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string spritesPersonaje);
	float getAncho() const;
	float getAlto() const;
	int getZIndex() const;
	std::string getSprites() const;
	~Personaje();
private:
	float ancho;
	float alto;
	int zIndex;
	std::string sprites;
};


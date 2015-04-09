#pragma once

class Capa
{
public:
	Capa(std::string unaImagenFondo, float unAncho);
	std::string getImagenFondo();
	void setTexturaSDL(SDL_Texture*);
	SDL_Texture* getTexturaSDL();
	float getAncho();
	virtual ~Capa();
private:
	std::string imagenFondo;
	SDL_Texture* texturaSDL;
	float ancho;
};


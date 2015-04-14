#pragma once

class Capa
{
public:
	Capa(std::string unaImagenFondo, float unAncho, int zIndexCapa);
	std::string getImagenFondo();
	void setTexturaSDL(SDL_Texture*);
	SDL_Texture* getTexturaSDL();
	float getAncho();
	int getZIndex();
	virtual ~Capa();
private:
	std::string imagenFondo;
	SDL_Texture* texturaSDL;
	float ancho;
	int zIndex;
};


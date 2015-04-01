#pragma once

#include "Parser.h"

class Vista
{
public:
	Vista();
	~Vista();
private:
	SDL_Window* ventana;
	SDL_Renderer* renderer;
	std::string rutaImagen;
	std::vector<SDL_Texture*> capasDeTextura;
};


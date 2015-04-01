#pragma once
#include "stdafx.h"
#include "ManejadorULogicas.h"

class Vista
{
public:
	Vista();
private:
	SDL_Window* ventana;
	SDL_Renderer* renderer;
	std::string rutaImagen;
	std::vector<SDL_Texture*> capasDeTextura;
	ManejadorULogicas manejadorULog;
};


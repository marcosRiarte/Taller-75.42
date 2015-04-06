#pragma once
#include "stdafx.h"
#include "Controlador.h"
#include <list>

class Vista
{
public:
	Vista();
	void actualizar(MOV_TIPO);
	~Vista();
private:
	SDL_Window* ventana;
	SDL_Renderer* renderer;
	std::string rutaImagen;
	std::vector<SDL_Texture*> capasDeTextura;
	ManejadorULogicas manejadorULog;
};


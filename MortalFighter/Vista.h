#pragma once
#include "stdafx.h"
#include "ManejadorULogicas.h"
#include "Controlador.h"
#include <list>

class Vista
{
public:
	Vista();
	void actualizar();
	~Vista();
private:
	SDL_Window* ventana;
	SDL_Renderer* renderer;
	std::string rutaImagen;
	std::list<SDL_Texture*> capasDeTextura;
	ManejadorULogicas manejadorULog;
};


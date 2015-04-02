#pragma once
#include "stdafx.h"
#include "ManejadorULogicas.h"
#include "Controlador.h"

class Vista
{
public:
	Vista();
	void actualizar(Controlador::MOV_TIPO movimiento);
private:
	SDL_Window* ventana;
	SDL_Renderer* renderer;
	std::string rutaImagen;
	std::vector<SDL_Texture*> capasDeTextura;
	ManejadorULogicas manejadorULog;
};


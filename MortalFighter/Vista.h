#pragma once
#include "stdafx.h"
#include "Controlador.h"
#include <list>

class Vista
{
public:
	Vista();
	void actualizar(MOV_TIPO movimiento);
	~Vista();
private:
	SDL_Window* ventana;
	SDL_Renderer* renderer;
	std::string rutaImagen;
	//std::vector<Capa*> capasDeTextura;	
	ManejadorULogicas manejadorULog;
};


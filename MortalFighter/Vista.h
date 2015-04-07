#pragma once
#include "stdafx.h"
#include "Controlador.h"
#include <list>
#include "Sprites.h"

class Vista
{
public:
	Vista();
	void actualizar(MOV_TIPO, ESTADO);
	~Vista();
private:
	Sprite* elSprite;
	SDL_Window* ventana;
	SDL_Renderer* renderer;
	std::string rutaImagen;
	int numeroDeCuadro;
	std::vector<SDL_Rect*>* listaDeCuadros;
	//std::vector<Capa*> capasDeTextura;
	float camaraXLog;
	ManejadorULogicas manejadorULog;
};


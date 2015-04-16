#pragma once
#include "stdafx.h"
#include "Controlador.h"
#include <list>
#include "Sprites.h"

#define TITULO_VENTANA "MortalFither"

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
	SDL_Surface* Superficie;
	SDL_Texture* texturaSprite;
	std::string dirImgPersonaje;

	std::vector<Capa*> capasVista;
	int numeroDeCuadro;
	std::vector<SDL_Rect*>* listaDeCuadros;
	//std::vector<Capa*> capasDeTextura;
	float camaraXLog;
	ManejadorULogicas manejadorULog;
};


#pragma once
#include "stdafx.h"
#include "Controlador.h"
#include <list>
#include "Sprites.h"

#define TITULO_VENTANA "Mortal Figther"
#define ICONO "ima/MF_icono.png"

class Vista
{
public:
	Vista();
	void actualizar(ESTADO);
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
	
	void OrdenarCapas();
	std::string GetEstadoDelPersonaje(ESTADO , Personaje* );
	void Dibujar(std::vector<Capa*> *, Personaje*, float, ESTADO);
	void DibujarCapasAnteriores(std::vector<Capa*> * capas, Personaje* personaje, float camaraXLog, float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario);
	void DibujarCapasPosteriores(std::vector<Capa*> *capas, Personaje* personaje, float camaraXLog, float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario);
	void DibujarPersonaje(std::vector<Capa*> *capas, Personaje* personaje, ESTADO, float camaraXLog);
};


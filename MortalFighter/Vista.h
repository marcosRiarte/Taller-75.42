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
	float xPjUn;
	ManejadorULogicas manejadorULog;
	
	void OrdenarCapas();
	std::string GetEstadoDelPersonaje(ESTADO , Personaje* );
	void Dibujar( Personaje*, ESTADO);
	void DibujarCapasAnteriores(Personaje* personaje, float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario);
	void DibujarCapasPosteriores(Personaje* personaje, float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario);
	void DibujarPersonaje(Personaje* personaje, ESTADO estadoPersonaje);
};


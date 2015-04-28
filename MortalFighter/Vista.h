#pragma once
#include "stdafx.h"
#include "Mundo.h"
#include "Controlador.h"
#include <list>
#include "Sprites.h"

#define TITULO_VENTANA "Mortal Figther"
#define ICONO "ima/MF_icono.png"

class Vista
{
public:	
	Vista(Mundo* unMundo);
	void actualizar();
	~Vista();
private:
	Sprite* elSprite;
	SDL_Window* ventana;
	SDL_Renderer* renderer;
	std::string rutaImagen;
	SDL_Surface* SuperficieUno;
	SDL_Surface* SuperficieDos;
	SDL_Texture* texturaSpriteUno;
	SDL_Texture* texturaSpriteDos;
	Mundo* refMundo;

	std::string dirImgPersonaje;

	std::vector<Capa*> capasVista;
	int numeroDeCuadroUno;
	std::vector<SDL_Rect*>* listaDeCuadrosUno;
	int numeroDeCuadroDos;
	std::vector<SDL_Rect*>* listaDeCuadrosDos;
	//std::vector<Capa*> capasDeTextura;
	float camaraXLog;
	float xPjUno;
	float xPjDos;
	ManejadorULogicas manejadorULog;
	
	void OrdenarCapas();
	std::string GetEstadoDelPersonaje(ESTADO , Personaje* );
	void Dibujar(std::vector<Personaje*>);
	void DibujarCapasAnteriores(std::vector<Personaje*> personajes, float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario);
	void DibujarCapasPosteriores(std::vector<Personaje*> personajes, float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario);
	void DibujarPersonajes(std::vector<Personaje*> personajes);
};


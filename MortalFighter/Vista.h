#pragma once
#include "stdafx.h"
#include "Mundo.h"
#include "Controlador.h"
#include <list>
#include "Sprites.h"

class Vista
{
public:	
	Vista(Mundo* unMundo, Sprite* unSprite, bool* error);
	void actualizar();
	void habilitarVibracion();
	void deshabilitarVibracion();
	SDL_Surface* cargarSuperficieOptimizada(std::string dirImagen);
	~Vista();

private:
	int vibraciones;
	bool vibracion;

	Sprite* elSprite;
	SDL_Window* ventana;
	SDL_Renderer* renderer;
	std::string rutaImagen;	
	SDL_Texture* texturaSpriteUno;
	SDL_Texture* texturaSpriteDos;
	Mundo* refMundo;
	int tiempoSecuenciaSpritesDos;
	int tiempoSecuenciaSpritesUno;
	SDL_Texture *texturaVerde;

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
	
	ESTADO estadoAnteriorPj1;
	ESTADO estadoAnteriorPj2;
	void OrdenarCapas();
	std::string GetEstadoDelPersonaje(ESTADO , Personaje* );
	void Dibujar(std::vector<Personaje*>);
	void DibujarCapasAnteriores(std::vector<Personaje*> personajes, float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario);
	void DibujarCapasPosteriores(std::vector<Personaje*> personajes, float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario);
	void DibujarPersonajes(std::vector<Personaje*> personajes);
};


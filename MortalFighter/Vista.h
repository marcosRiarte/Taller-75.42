#pragma once
#include "stdafx.h"
#include "Mundo.h"
#include "Controlador.h"
#include <list>
#include "Sprites.h"
#include "Timer.h"
#include "Sonidos.h"

class Vista
{
	enum modoJuego {ONEPLAYER,TWOPLAYER,PRACTICA};
public:	
	Vista(Mundo* unMundo, bool* error, bool habilitarAceleracionDeHardware);
	void actualizar();
	void habilitarVibracion();
	void deshabilitarVibracion();
	void alfa(Uint8 alfa);
	SDL_Surface* cargarSuperficieOptimizada(std::string dirImagen);
	~Vista();

private:
	int vibraciones;
	int retraso;
	bool vibracion;
	bool estaVibrando;
	
	SDL_Window* ventana;
	SDL_Renderer* renderer;
	std::string rutaImagen;	
	SDL_Texture* texturaSpriteUno;
	SDL_Texture* texturaSpriteDos;
	Mundo* refMundo;
	int tiempoSecuenciaSpritesDos;
	int tiempoSecuenciaSpritesUno;
	SDL_Texture *texturaVerde;
	SDL_Texture *texturaBarraDeVida;
	SDL_Texture *texturaBarraDeVidaRoja;
	SDL_Texture *texturaFight;
	SDL_Texture *texturaRound;
	SDL_Texture *texturaMenu;
	SDL_Texture *texturaLiuKang;
	SDL_Texture *texturaScorpion;
	SDL_Texture *texturaPlayMode;
	SDL_Texture *texturaUnjugador;
	SDL_Texture *texturaTrainig;
	SDL_Texture *texturaRecuadro;
	SDL_Texture *texturaSeleccionPersonajes;
	SDL_Texture *texturaGrillaPersonajes;
	SDL_Texture *texturaRecuadroPersonajes;
	SDL_Texture *texturaSeleccionPersonajes2;

	SDL_Texture *texturaToasty1;
	SDL_Texture *texturaToasty2;

	Uint8 AlfaVida;
	Uint8 AlfaAnterior;
	Uint8 AlfaInicial;

	SDL_Surface* superficieBarraDeVida;
	SDL_Surface* superficieBarraDeVidaRoja;

	SDL_Rect barraDeVida1;
	SDL_Rect barraDeVida2;
	SDL_Rect barraDeVidaImagen1;
	SDL_Rect barraDeVidaImagen2;

	SDL_Rect barraRojaDeVida1;
	SDL_Rect barraRojaDeVida2;
	SDL_Rect barraRojaDeVidaImagen1;
	SDL_Rect barraRojaDeVidaImagen2;

	//Modos de juego
	modoJuego modoActual;
	//Repreentara un click o un enter en la pantalla de menu
	int enterMenu;
	int enterSeleccionPersonaje;
	int y;//Alturaboton
	int yPersonaje;
	int x;//Columnas
	int yPersonaje2;
	int xPersonaje2;

	//Sonido ya reproducido
	bool roundYaReproducido;
	bool oneYaReproducido;
	bool fightYaReproducido;
	bool seleccionYaReproducida;
	
	//Seteados en el menu de eleccion
	Personaje* jugador1;
	Personaje* jugador2;

	Timer efectosTimer;
	Timer menuTimer;
	Timer timerToasty;
	TTF_Font * fuente;

	
	int posBarraDeVida1;
	int anchoImagenBarraDeVida;
	int anchoBarraDeVida1;
	int anchoBarraDeVida2;	

	//Anchos Auxiliares
	int anchoAnteriorBarra1;
	int anchoAnteriorBarra2;
	int anchoAnteriorBarraImagen1;
	int anchoAnteriorBarraImagen2;

	//Anchos finales
	int anchoRojoBarra1;
	int anchoRojoBarra2;
	int anchoRojoImagenBarra1;
	int anchoRojoImagenBarra2;
	
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
	void DibujarBarrasDeVida(std::vector<Personaje*>);
	void DibujarCapasAnteriores(std::vector<Personaje*> personajes, float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario);
	void DibujarCapasPosteriores(std::vector<Personaje*> personajes, float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario);
	void DibujarPersonajes(std::vector<Personaje*> personajes);
	void DibujarEfectos(float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario);
	void dibujarMenu(float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario);
	void dibujarSeleccionPersonaje(float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario);
	void actualizarMenu(int nuevaAltura);
	void setModoJuegoActual(modoJuego nuevoModo);
	modoJuego getModoJuegoActual();
	void controladorDeModoDeJuego();
	Personaje* controladorDePersonajes();
	void dibujarImagenesBarraVida(int anchoVentanaPx, int altoVentanaPx);
	void dibujarEfectoToasty();
};


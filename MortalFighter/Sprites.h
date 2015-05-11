#pragma once
#include <vector>
#include <string>
#include "Personaje.h"
#define JSON_SPRITES "ima/sprites/ScorpionMK3U.json"

class Sprite{
private:
	std::vector<SDL_Rect*>* Caida;
	std::vector<SDL_Rect*>* Salto;
	std::vector<SDL_Rect*>* CaminandoParaAdelante;
	std::vector<SDL_Rect*>* CaminandoParaAtras;
	std::vector<SDL_Rect*>* SaltoDiagonal;
	std::vector<SDL_Rect*>* SaltoDiagonalIzq;
	std::vector<SDL_Rect*>* Quieto;

	std::vector<SDL_Rect*>*Agacharse;
	std::vector<SDL_Rect*>*PatadaAlta;
	std::vector<SDL_Rect*>*Golpeado;
	
	std::vector<SDL_Rect*>*AgachadoGolpeado;
	std::vector<SDL_Rect*>*SaltoGolpeado;
	std::vector<SDL_Rect*>*AgachadoDefensa;


	std::vector<float>* cuadrosRep;

	std::vector<std::vector<Sensor*>*> Sensores;
	SDL_Rect* crearCuadro(int x, int y, int w, int h);
	SDL_Rect* crearCuadro(Json::Value cuadro);	
	void cargarSensores(std::string unEstadoStr, Json::Value spritesRaiz);
	void cargarSprites(std::vector<SDL_Rect*>* estadoCuadros, std::string unEstadoStr, Json::Value spritesRaiz);
	ManejadorULogicas manejadorULog;


public:
	Sprite(std::string);
	std::vector<SDL_Rect*>* listaDeCuadros(ESTADO unEstado);
	Json::Value	ParsearSprites(std::string);
	std::vector<std::vector<Sensor*>*> getSensores() const;
	int getConstantes(ESTADO estadoDelPersonaje);
	~Sprite();
};

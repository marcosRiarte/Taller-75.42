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
	SDL_Rect* crearCuadro(int x, int y, int w, int h);
	SDL_Rect* crearCuadro(Json::Value cuadro);	

public:
	Sprite();
	std::vector<SDL_Rect*>* listaDeCuadros(std::string unEstado);
	Json::Value	ParsearSprites();
	~Sprite();
};

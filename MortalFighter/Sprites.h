#pragma once
#include <vector>
#include <string>
#include "Personaje.h"

class Sprite{
private:
	std::vector<SDL_Rect*>* Caida;
	std::vector<SDL_Rect*>* Salto;
	std::vector<SDL_Rect*>* CaminandoParaAdelante;
	std::vector<SDL_Rect*>* CaminandoParaAtras;
	std::vector<SDL_Rect*>* SaltoDiagonal;
	std::vector<SDL_Rect*>* SaltoDiagonalIzq;
	std::vector<SDL_Rect*>* Quieto;

public:
	Sprite();
	std::vector<SDL_Rect*>* listaDeCuadros(std::string unEstado);
	~Sprite();
};

#pragma once
#include <vector>
#include <string>
#include "Personaje.h"

class Sprite{
private:
	std::vector<SDL_Rect*>* CayendoDer;
	std::vector<SDL_Rect*>* SaltandoDer;
	std::vector<SDL_Rect*>* CaminandoDer;
	std::vector<SDL_Rect*>* QuietoDer;

public:
	Sprite();
	std::vector<SDL_Rect*>* listaDeCuadros(ESTADO unEstado);
};

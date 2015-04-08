#include "stdafx.h"
#include "Sprites.h"
#include <list>

SDL_Rect* crearCuadro(int x, int y, int w, int h){
	SDL_Rect* unCuadro = new SDL_Rect;
	unCuadro->x = x;
	unCuadro->y = y;
	unCuadro->w = w;
	unCuadro->h = h;
	return unCuadro;
}

Sprite::Sprite(){
	this->CayendoDer = new std::vector<SDL_Rect*>();
	this->SaltandoDer = new std::vector<SDL_Rect*>();
	this->CaminandoDer = new std::vector<SDL_Rect*>();
	this->QuietoDer = new std::vector<SDL_Rect*>();

	//Quieto
	this->QuietoDer->push_back(crearCuadro(32, 28, 56, 81));

	//caminar
	this->CaminandoDer->push_back(crearCuadro(18, 336, 63, 81));
	this->CaminandoDer->push_back(crearCuadro(113, 333, 65, 83));
	this->CaminandoDer->push_back(crearCuadro(211, 331, 59, 82));
	this->CaminandoDer->push_back(crearCuadro(311, 330, 45, 83));
	this->CaminandoDer->push_back(crearCuadro(386, 329, 57, 85));
	this->CaminandoDer->push_back(crearCuadro(473, 327, 64, 85));
	this->CaminandoDer->push_back(crearCuadro(571, 329, 57, 83));
	this->CaminandoDer->push_back(crearCuadro(657, 333, 50, 81));

	//salto
	this->SaltandoDer->push_back(crearCuadro(21, 249, 64, 64));
	this->SaltandoDer->push_back(crearCuadro(109, 228, 58, 86));

	//caida del salto
	this->CayendoDer->push_back(crearCuadro(109, 228, 58, 86));
}

std::vector<SDL_Rect*>* Sprite::listaDeCuadros(ESTADO unEstado){
	if ((unEstado == ESTADO::IZQ_IZQ) || (unEstado == ESTADO::DER_DER) || (unEstado == ESTADO::DER_IZQ) || (unEstado == ESTADO::IZQ_DER)){ return CaminandoDer; }
	if ((unEstado == ESTADO::ARRIBA_IZQ) || (unEstado == ESTADO::ARRIBA_DER) || (unEstado == ESTADO::SALTODER_DER) || (unEstado == ESTADO::SALTODER_IZQ) || (unEstado == ESTADO::SALTOIZQ_DER) || (unEstado == ESTADO::SALTOIZQ_IZQ)){ return SaltandoDer; }
	if ((unEstado == ESTADO::ABAJO_IZQ) || (unEstado == ESTADO::ABAJO_DER)){ return CayendoDer; }
	if ((unEstado == ESTADO::QUIETODER) || (unEstado == ESTADO::QUIETOIZQ)) { return QuietoDer; }
	return QuietoDer;
}

Sprite::~Sprite()
{
	delete CayendoDer;
	delete SaltandoDer;
	delete CaminandoDer;
	delete QuietoDer;
	
}


	


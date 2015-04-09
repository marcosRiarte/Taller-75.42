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
	this->QuietoDer->push_back(crearCuadro(7, 20, 78, 117));
	this->QuietoDer->push_back(crearCuadro(7, 20, 78, 117));
	this->QuietoDer->push_back(crearCuadro(85, 20, 78, 117));
	this->QuietoDer->push_back(crearCuadro(85, 20, 78, 117));
	this->QuietoDer->push_back(crearCuadro(164, 20, 78, 117));
	this->QuietoDer->push_back(crearCuadro(164, 20, 78, 117));
	this->QuietoDer->push_back(crearCuadro(244, 20, 78, 117));
	this->QuietoDer->push_back(crearCuadro(244, 20, 78, 117));
	this->QuietoDer->push_back(crearCuadro(323, 20, 78, 117));
	this->QuietoDer->push_back(crearCuadro(323, 20, 78, 117));
	this->QuietoDer->push_back(crearCuadro(401, 20, 78, 117));
	this->QuietoDer->push_back(crearCuadro(401, 20, 78, 117));
	this->QuietoDer->push_back(crearCuadro(479, 20, 78, 117));
	this->QuietoDer->push_back(crearCuadro(479, 20, 78, 117));

	//caminar
	this->CaminandoDer->push_back(crearCuadro(20, 159, 59, 117));
	this->CaminandoDer->push_back(crearCuadro(90, 159, 57, 117));
	this->CaminandoDer->push_back(crearCuadro(158, 158, 54, 118));
	this->CaminandoDer->push_back(crearCuadro(224, 159, 62, 117));
	this->CaminandoDer->push_back(crearCuadro(298, 160, 64, 116));
	this->CaminandoDer->push_back(crearCuadro(375, 157, 58, 119));
	this->CaminandoDer->push_back(crearCuadro(446, 156, 58, 120));
	this->CaminandoDer->push_back(crearCuadro(515, 158, 61, 118));
	this->CaminandoDer->push_back(crearCuadro(587, 162, 65, 114));

	//salto
	this->SaltandoDer->push_back(crearCuadro(708, 161, 68, 115));

	//caida del salto
	this->CayendoDer->push_back(crearCuadro(708, 161, 68, 115));
	this->CayendoDer->push_back(crearCuadro(788, 150, 67, 126));
	this->CayendoDer->push_back(crearCuadro(866, 170, 64, 106));
	this->CayendoDer->push_back(crearCuadro(941, 179, 62, 97));
	this->CayendoDer->push_back(crearCuadro(1014, 188, 64, 88));
}

std::vector<SDL_Rect*>* Sprite::listaDeCuadros(ESTADO unEstado){
	if ((unEstado == ESTADO::IZQ_IZQ) || (unEstado == ESTADO::DER_DER) || (unEstado == ESTADO::DER_IZQ) || (unEstado == ESTADO::IZQ_DER)){ 
		return CaminandoDer; }
	if ((unEstado == ESTADO::ARRIBA_IZQ) || (unEstado == ESTADO::ARRIBA_DER) || (unEstado == ESTADO::SALTODER_DER) || (unEstado == ESTADO::SALTODER_IZQ) || (unEstado == ESTADO::SALTOIZQ_DER) || (unEstado == ESTADO::SALTOIZQ_IZQ)){
		return SaltandoDer; }
	if ((unEstado == ESTADO::ABAJO_IZQ) || (unEstado == ESTADO::ABAJO_DER)){
		return CayendoDer; }
	if ((unEstado == ESTADO::QUIETODER) || (unEstado == ESTADO::QUIETOIZQ)) { 
		return QuietoDer; }
	return QuietoDer;
}

Sprite::~Sprite()
{
	for (size_t i = 0; i < CayendoDer->size(); i++) 
		delete CayendoDer->at(i);
	CayendoDer->clear();
	delete CayendoDer;

	for (size_t i = 0; i < SaltandoDer->size(); i++)
		delete SaltandoDer->at(i);
	SaltandoDer->clear();
	delete SaltandoDer;

	for (size_t i = 0; i < CaminandoDer->size(); i++)
		delete CaminandoDer->at(i);
	CaminandoDer->clear();
	delete CaminandoDer;

	for (size_t i = 0; i < QuietoDer->size(); i++)
		delete QuietoDer->at(i);
	QuietoDer->clear();
	delete QuietoDer;
}


	


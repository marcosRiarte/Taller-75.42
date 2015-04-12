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
	//this->QuietoDer->push_back(crearCuadro(7, 7, 57, 118));
	//this->QuietoDer->push_back(crearCuadro(9, 7, 57, 118));
	//this->QuietoDer->push_back(crearCuadro(71, 7, 57, 118));
	//this->QuietoDer->push_back(crearCuadro(134, 7, 57, 118));
	//this->QuietoDer->push_back(crearCuadro(194, 7, 57, 118));
	//this->QuietoDer->push_back(crearCuadro(194, 7, 57, 118));
	//this->QuietoDer->push_back(crearCuadro(254, 7, 57, 118));
	//this->QuietoDer->push_back(crearCuadro(314, 7, 57, 118));
	//this->QuietoDer->push_back(crearCuadro(372, 7, 57, 118));
	//this->QuietoDer->push_back(crearCuadro(434, 7, 57, 118));
	//this->QuietoDer->push_back(crearCuadro(495, 7, 57, 118));
	//this->QuietoDer->push_back(crearCuadro(560, 7, 57, 118));
	//this->QuietoDer->push_back(crearCuadro(625, 7, 57, 118));
	//this->QuietoDer->push_back(crearCuadro(625, 7, 57, 118));
	this->QuietoDer->push_back(crearCuadro(0, 1, 202, 368));
	
	this->QuietoDer->push_back(crearCuadro(404, 1, 202, 368));

	this->QuietoDer->push_back(crearCuadro(808, 1, 202, 368));

	this->QuietoDer->push_back(crearCuadro(1212, 1, 202, 368));

	this->QuietoDer->push_back(crearCuadro(1616, 1, 202, 368));

	this->QuietoDer->push_back(crearCuadro(2020, 1, 202, 368));

	this->QuietoDer->push_back(crearCuadro(2424, 1, 202, 368));

	this->QuietoDer->push_back(crearCuadro(2828, 1, 202, 368));

	this->QuietoDer->push_back(crearCuadro(3232, 1, 202, 368));

	this->QuietoDer->push_back(crearCuadro(3636, 1, 202, 368));


	this->QuietoDer->push_back(crearCuadro(4040, 1, 202, 368));

	this->QuietoDer->push_back(crearCuadro(4444, 1, 202, 368));

	this->QuietoDer->push_back(crearCuadro(4848, 1, 202, 368));

	this->QuietoDer->push_back(crearCuadro(5252, 1, 202, 368));

	this->QuietoDer->push_back(crearCuadro(5656, 1, 202, 368));


	this->QuietoDer->push_back(crearCuadro(6060, 1, 202, 368));

	this->QuietoDer->push_back(crearCuadro(6464, 1, 202, 368));

	this->QuietoDer->push_back(crearCuadro(6868, 1, 202, 368));
	this->QuietoDer->push_back(crearCuadro(7070, 1, 202, 368));

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
	this->SaltandoDer->push_back(crearCuadro(6, 2, 42, 115));
	

	//caida del salto
	this->CayendoDer->push_back(crearCuadro(61, 2, 53, 115));
	this->CayendoDer->push_back(crearCuadro(125, 2, 88, 115));
	this->CayendoDer->push_back(crearCuadro(231, 2, 46, 115));
	this->CayendoDer->push_back(crearCuadro(293, 2, 70, 115));
	this->CayendoDer->push_back(crearCuadro(377, 2, 84, 115));
	this->CayendoDer->push_back(crearCuadro(474, 2, 53, 115));
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


	


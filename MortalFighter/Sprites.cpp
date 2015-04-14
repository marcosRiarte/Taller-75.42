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
	this->QuietoDer->push_back(crearCuadro(0, 0, 77, 132));
	this->QuietoDer->push_back(crearCuadro(77, 0, 77, 132));
	this->QuietoDer->push_back(crearCuadro(154, 0, 77, 132));
	this->QuietoDer->push_back(crearCuadro(231, 0, 77, 132));
	this->QuietoDer->push_back(crearCuadro(308, 0, 77, 132));
	this->QuietoDer->push_back(crearCuadro(385, 0, 77, 132));
	this->QuietoDer->push_back(crearCuadro(462, 0, 77, 132));
	this->QuietoDer->push_back(crearCuadro(539, 0, 77, 132));
	this->QuietoDer->push_back(crearCuadro(616, 0, 77, 132));
	this->QuietoDer->push_back(crearCuadro(693, 0, 77, 132));
	this->QuietoDer->push_back(crearCuadro(770, 0, 77, 132));
	this->QuietoDer->push_back(crearCuadro(847, 0, 77, 132));
	this->QuietoDer->push_back(crearCuadro(924, 0, 77, 132));
	this->QuietoDer->push_back(crearCuadro(1001, 0, 77, 132));
	this->QuietoDer->push_back(crearCuadro(1078, 0, 77, 132));
	this->QuietoDer->push_back(crearCuadro(1155, 0, 77, 132));
	
	

	

	//caminar
	this->CaminandoDer->push_back(crearCuadro(0, 268, 77, 132));
	this->CaminandoDer->push_back(crearCuadro(78, 268, 77, 132));
	this->CaminandoDer->push_back(crearCuadro(156, 268, 77, 132));
	this->CaminandoDer->push_back(crearCuadro(234, 268, 77, 132));
	this->CaminandoDer->push_back(crearCuadro(312, 268, 77, 132));
	this->CaminandoDer->push_back(crearCuadro(390, 268, 77, 132));
	this->CaminandoDer->push_back(crearCuadro(468, 268, 77, 132));
	this->CaminandoDer->push_back(crearCuadro(546, 268, 77, 132));


	//salto
	this->SaltandoDer->push_back(crearCuadro(0, 400, 77, 132));
	
	
	//xjose... esto anda para el.... tengo que repetir cuadros para que la animacion quede bien
	//ademas si tocas la gravedad te altera la reproducion de los sprites y los vuelve a joder
	//caida del salto
	this->CayendoDer->push_back(crearCuadro(78, 400, 77, 132));
	this->CayendoDer->push_back(crearCuadro(78, 400, 77, 132));
	this->CayendoDer->push_back(crearCuadro(78, 400, 77, 132));
	this->CayendoDer->push_back(crearCuadro(78, 400, 77, 132));
	this->CayendoDer->push_back(crearCuadro(78, 400, 77, 132));
	this->CayendoDer->push_back(crearCuadro(78, 400, 77, 132));
	this->CayendoDer->push_back(crearCuadro(78, 400, 77, 132));
	this->CayendoDer->push_back(crearCuadro(156, 400, 77, 132));
	this->CayendoDer->push_back(crearCuadro(156, 400, 77, 132));
	
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


	


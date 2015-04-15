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
	this->Caida = new std::vector<SDL_Rect*>();
	this->Salto = new std::vector<SDL_Rect*>();
	this->CaminandoParaAdelante = new std::vector<SDL_Rect*>();
	this->CaminandoParaAtras = new std::vector<SDL_Rect*>();
	this->SaltoDiagonal = new std::vector<SDL_Rect*>();
	this->Quieto = new std::vector<SDL_Rect*>();

	//Quieto
	this->Quieto->push_back(crearCuadro(0, 0, 77, 132));
	this->Quieto->push_back(crearCuadro(77, 0, 77, 132));
	this->Quieto->push_back(crearCuadro(154, 0, 77, 132));
	this->Quieto->push_back(crearCuadro(231, 0, 77, 132));
	this->Quieto->push_back(crearCuadro(308, 0, 77, 132));
	this->Quieto->push_back(crearCuadro(385, 0, 77, 132));
	this->Quieto->push_back(crearCuadro(462, 0, 77, 132));
	this->Quieto->push_back(crearCuadro(539, 0, 77, 132));
	this->Quieto->push_back(crearCuadro(616, 0, 77, 132));
	this->Quieto->push_back(crearCuadro(693, 0, 77, 132));
	this->Quieto->push_back(crearCuadro(770, 0, 77, 132));
	this->Quieto->push_back(crearCuadro(847, 0, 77, 132));
	this->Quieto->push_back(crearCuadro(924, 0, 77, 132));
	this->Quieto->push_back(crearCuadro(1001, 0, 77, 132));
	this->Quieto->push_back(crearCuadro(1078, 0, 77, 132));
	this->Quieto->push_back(crearCuadro(1155, 0, 77, 132));
	
	//Caminar para Adelante
	this->CaminandoParaAdelante->push_back(crearCuadro(0, 268, 77, 132));
	this->CaminandoParaAdelante->push_back(crearCuadro(78, 268, 77, 132));
	this->CaminandoParaAdelante->push_back(crearCuadro(156, 268, 77, 132));
	this->CaminandoParaAdelante->push_back(crearCuadro(234, 268, 77, 132));
	this->CaminandoParaAdelante->push_back(crearCuadro(312, 268, 77, 132));
	this->CaminandoParaAdelante->push_back(crearCuadro(390, 268, 77, 132));
	this->CaminandoParaAdelante->push_back(crearCuadro(468, 268, 77, 132));
	this->CaminandoParaAdelante->push_back(crearCuadro(546, 268, 77, 132));

	//Caminar para Atrás
	this->CaminandoParaAtras->push_back(crearCuadro(0, 136, 77, 132));
	this->CaminandoParaAtras->push_back(crearCuadro(78, 136, 77, 132));
	this->CaminandoParaAtras->push_back(crearCuadro(156, 136, 77, 132));
	this->CaminandoParaAtras->push_back(crearCuadro(234, 136, 77, 132));
	this->CaminandoParaAtras->push_back(crearCuadro(312, 136, 77, 132));
	this->CaminandoParaAtras->push_back(crearCuadro(390, 136, 77, 132));
	this->CaminandoParaAtras->push_back(crearCuadro(468, 136, 77, 132));
	this->CaminandoParaAtras->push_back(crearCuadro(546, 136, 77, 132));


	//Salto
	this->Salto->push_back(crearCuadro(0, 400, 77, 132));
	this->Salto->push_back(crearCuadro(78, 400, 77, 132));
	this->Salto->push_back(crearCuadro(156, 400, 77, 132));

	//Salto Diagonal
	this->SaltoDiagonal->push_back(crearCuadro(0, 534, 77, 132));
	
	//xjose... esto anda para el.... tengo que repetir cuadros para que la animacion quede bien
	//ademas si tocas la gravedad te altera la reproducion de los sprites y los vuelve a joder
	//caida del salto
	//caida del salto
	/*
	this->Caida->push_back(crearCuadro(78, 400, 77, 132));
	this->Caida->push_back(crearCuadro(78, 400, 77, 132));
	this->Caida->push_back(crearCuadro(78, 400, 77, 132));
	this->Caida->push_back(crearCuadro(78, 400, 77, 132));
	this->Caida->push_back(crearCuadro(78, 400, 77, 132));
	this->Caida->push_back(crearCuadro(78, 400, 77, 132));
	this->Caida->push_back(crearCuadro(78, 400, 77, 132));
	this->Caida->push_back(crearCuadro(156, 400, 77, 132));
	this->Caida->push_back(crearCuadro(156, 400, 77, 132));
	*/
	//xjose necesitamos 2 caidas.... 
	this->Caida->push_back(crearCuadro(77, 534, 77, 132));
	this->Caida->push_back(crearCuadro(154, 534, 77, 132));
	this->Caida->push_back(crearCuadro(231, 534, 77, 132));
	this->Caida->push_back(crearCuadro(308, 534, 77, 132));
	this->Caida->push_back(crearCuadro(385, 534, 77, 132));
	this->Caida->push_back(crearCuadro(462, 534, 77, 132));
		this->Caida->push_back(crearCuadro(539, 534, 77, 132));
		this->Caida->push_back(crearCuadro(539, 534, 77, 132));
	this->Caida->push_back(crearCuadro(0, 534, 77, 132));
	
}

std::vector<SDL_Rect*>* Sprite::listaDeCuadros(std::string unEstado){
	if (unEstado == "CaminarParaAdelante"){
		return CaminandoParaAdelante;
	}
	if (unEstado == "CaminarParaAtras"){
		return CaminandoParaAtras;
	}
	if (unEstado == "Quieto"){
		return Quieto;
	}
	if (unEstado == "Salto"){
		return Salto;
	}
	if (unEstado == "SaltoDiagonal"){
		return SaltoDiagonal;
	}
	
	return Caida;
}

Sprite::~Sprite()
{
	for (size_t i = 0; i < Caida->size(); i++) 
		delete Caida->at(i);
	Caida->clear();
	delete Caida;

	for (size_t i = 0; i < Salto->size(); i++)
		delete Salto->at(i);
	Salto->clear();
	delete Salto;

	for (size_t i = 0; i < SaltoDiagonal->size(); i++)
		delete SaltoDiagonal->at(i);
	SaltoDiagonal->clear();
	delete SaltoDiagonal;

	for (size_t i = 0; i < CaminandoParaAdelante->size(); i++)
		delete CaminandoParaAdelante->at(i);
	CaminandoParaAdelante->clear();
	delete CaminandoParaAdelante;

	for (size_t i = 0; i < CaminandoParaAtras->size(); i++)
		delete CaminandoParaAtras->at(i);
	CaminandoParaAtras->clear();
	delete CaminandoParaAtras;

	for (size_t i = 0; i < Quieto->size(); i++)
		delete Quieto->at(i);
	Quieto->clear();
	delete Quieto;
}


	


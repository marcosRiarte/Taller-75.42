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
	this->Quieto->push_back(crearCuadro(0, 0, 154, 264));
	this->Quieto->push_back(crearCuadro(154, 0, 154, 264));
	this->Quieto->push_back(crearCuadro(308, 0, 154, 264));
	this->Quieto->push_back(crearCuadro(462, 0, 154, 264));
	this->Quieto->push_back(crearCuadro(616, 0, 154, 264));
	this->Quieto->push_back(crearCuadro(770, 0, 154, 264));
	this->Quieto->push_back(crearCuadro(924, 0, 154, 264));
	this->Quieto->push_back(crearCuadro(1078, 0, 154, 264));
	this->Quieto->push_back(crearCuadro(1232, 0, 154, 264));
	this->Quieto->push_back(crearCuadro(1386, 0, 154, 264));
	this->Quieto->push_back(crearCuadro(1540, 0, 154, 264));
	this->Quieto->push_back(crearCuadro(1694, 0, 154, 264));
	this->Quieto->push_back(crearCuadro(1848, 0, 154, 264));
	this->Quieto->push_back(crearCuadro(2002, 0, 154, 264));
	this->Quieto->push_back(crearCuadro(2156, 0, 154, 264));
	this->Quieto->push_back(crearCuadro(2310, 0, 154, 264));
	
	//Caminar para Adelante
	this->CaminandoParaAdelante->push_back(crearCuadro(0, 272, 154, 264));
	this->CaminandoParaAdelante->push_back(crearCuadro(0, 272, 154, 264));
	this->CaminandoParaAdelante->push_back(crearCuadro(156, 272, 154, 264));
	this->CaminandoParaAdelante->push_back(crearCuadro(312, 272, 154, 264));
	this->CaminandoParaAdelante->push_back(crearCuadro(468, 272, 154, 264));
	this->CaminandoParaAdelante->push_back(crearCuadro(468, 272, 154, 264));
	this->CaminandoParaAdelante->push_back(crearCuadro(624, 272, 154, 264));
	this->CaminandoParaAdelante->push_back(crearCuadro(780, 272, 154, 264));
	this->CaminandoParaAdelante->push_back(crearCuadro(936, 272, 154, 264));
	this->CaminandoParaAdelante->push_back(crearCuadro(936, 272, 154, 264));
	this->CaminandoParaAdelante->push_back(crearCuadro(1092, 272, 154, 264));


	//Caminar para Atrás
	this->CaminandoParaAtras->push_back(crearCuadro(0, 536, 154, 264));
	this->CaminandoParaAtras->push_back(crearCuadro(156, 536, 154, 264));
	this->CaminandoParaAtras->push_back(crearCuadro(156, 536, 154, 264));
	this->CaminandoParaAtras->push_back(crearCuadro(312, 536, 154, 264));
	this->CaminandoParaAtras->push_back(crearCuadro(468, 536, 154, 264));
	this->CaminandoParaAtras->push_back(crearCuadro(468, 536, 154, 264));
	this->CaminandoParaAtras->push_back(crearCuadro(624, 536, 154, 264));
	this->CaminandoParaAtras->push_back(crearCuadro(780, 536, 154, 264));
	this->CaminandoParaAtras->push_back(crearCuadro(780, 536, 154, 264));
	this->CaminandoParaAtras->push_back(crearCuadro(936, 536, 154, 264));
	this->CaminandoParaAtras->push_back(crearCuadro(1092, 536, 154, 264));
	this->CaminandoParaAtras->push_back(crearCuadro(1092, 536, 154, 264));


	//Salto
	this->Salto->push_back(crearCuadro(156, 800, 154, 264));
	this->Salto->push_back(crearCuadro(156, 800, 154, 264));
	this->Salto->push_back(crearCuadro(156, 800, 154, 264));
	this->Salto->push_back(crearCuadro(156, 800, 154, 264));
	this->Salto->push_back(crearCuadro(156, 800, 154, 264));
	this->Salto->push_back(crearCuadro(156, 800, 154, 264));
	this->Salto->push_back(crearCuadro(156, 800, 154, 264));
	this->Salto->push_back(crearCuadro(156, 800, 154, 264));
	this->Salto->push_back(crearCuadro(156, 800, 154, 264));
	this->Salto->push_back(crearCuadro(156, 800, 154, 264));
	this->Salto->push_back(crearCuadro(156, 800, 154, 264));
	this->Salto->push_back(crearCuadro(156, 800, 154, 264));
	

	//Salto Diagonal
	this->SaltoDiagonal->push_back(crearCuadro(154, 1068, 154, 264));
	this->SaltoDiagonal->push_back(crearCuadro(154, 1068, 154, 264));
	this->SaltoDiagonal->push_back(crearCuadro(308, 1068, 154, 264));
	this->SaltoDiagonal->push_back(crearCuadro(308, 1068, 154, 264));
	this->SaltoDiagonal->push_back(crearCuadro(462, 1068, 154, 264));
	this->SaltoDiagonal->push_back(crearCuadro(462, 1068, 154, 264));
	this->SaltoDiagonal->push_back(crearCuadro(616, 1068, 154, 264));
	this->SaltoDiagonal->push_back(crearCuadro(616, 1068, 154, 264));
	this->SaltoDiagonal->push_back(crearCuadro(770, 1068, 154, 264));
	this->SaltoDiagonal->push_back(crearCuadro(770, 1068, 154, 264));
	this->SaltoDiagonal->push_back(crearCuadro(924, 1068, 154, 264));
	this->SaltoDiagonal->push_back(crearCuadro(924, 1068, 154, 264));
	this->SaltoDiagonal->push_back(crearCuadro(1078, 1068, 154, 264));
	this->SaltoDiagonal->push_back(crearCuadro(1078, 1068, 154, 264));
	
	
		
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
	
	return Quieto;
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


	


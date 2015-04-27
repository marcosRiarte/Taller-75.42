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
	this->SaltoDiagonalIzq = new std::vector<SDL_Rect*>();
	this->Quieto = new std::vector<SDL_Rect*>();

	//Quieto
	this->Quieto->push_back(crearCuadro(1, 1, 256, 494));
	this->Quieto->push_back(crearCuadro(1, 1, 256, 494));
	this->Quieto->push_back(crearCuadro(1, 1, 256, 494));
	this->Quieto->push_back(crearCuadro(1, 496, 256, 494));
	this->Quieto->push_back(crearCuadro(1, 496, 256, 494));
	this->Quieto->push_back(crearCuadro(258, 1, 256, 494));
	this->Quieto->push_back(crearCuadro(258, 1, 256, 494));
	this->Quieto->push_back(crearCuadro(258, 1, 256, 494));
	this->Quieto->push_back(crearCuadro(515, 1, 256, 494));
	this->Quieto->push_back(crearCuadro(515, 1, 256, 494));
	this->Quieto->push_back(crearCuadro(258, 496, 256, 494));
	this->Quieto->push_back(crearCuadro(258, 496, 256, 494));
	this->Quieto->push_back(crearCuadro(258, 496, 256, 494));
	this->Quieto->push_back(crearCuadro(515, 496, 256, 494));
	this->Quieto->push_back(crearCuadro(515, 496, 256, 494));
	
	//Caminar para Adelante
	this->CaminandoParaAdelante->push_back(crearCuadro(1, 1025, 256, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(1, 1025, 256, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(258, 1025, 320, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(258, 1025, 320, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(579, 1025, 320, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(579, 1025, 320, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(258, 1520, 320, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(258, 1520, 320, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(1, 1520, 256, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(1, 1520, 256, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(579, 1520, 256, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(579, 1520, 256, 494));


	//Caminar para Atrás
	this->CaminandoParaAtras->push_back(crearCuadro(1, 2049, 256, 494));
	this->CaminandoParaAtras->push_back(crearCuadro(1, 2049, 256, 494));
	this->CaminandoParaAtras->push_back(crearCuadro(258, 2049, 320, 494));
	this->CaminandoParaAtras->push_back(crearCuadro(258, 2049, 320, 494));
	this->CaminandoParaAtras->push_back(crearCuadro(1, 2544, 256, 494));
	this->CaminandoParaAtras->push_back(crearCuadro(1, 2544, 256, 494));
	this->CaminandoParaAtras->push_back(crearCuadro(579, 2049, 256, 494));
	this->CaminandoParaAtras->push_back(crearCuadro(579, 2049, 256, 494));
	this->CaminandoParaAtras->push_back(crearCuadro(258, 2544, 256, 494));
	this->CaminandoParaAtras->push_back(crearCuadro(258, 2544, 256, 494));
	this->CaminandoParaAtras->push_back(crearCuadro(515, 2544, 256, 494));
	this->CaminandoParaAtras->push_back(crearCuadro(515, 2544, 256, 494));


	//Salto
	this->Salto->push_back(crearCuadro(1, 3043, 256, 494));
	this->Salto->push_back(crearCuadro(1, 3043, 256, 494));
	this->Salto->push_back(crearCuadro(258, 3043, 256, 576));
	this->Salto->push_back(crearCuadro(258, 3043, 256, 576));
	this->Salto->push_back(crearCuadro(258, 3043, 256, 576));
	this->Salto->push_back(crearCuadro(515, 3043, 256, 576));
	this->Salto->push_back(crearCuadro(515, 3043, 256, 576));
	this->Salto->push_back(crearCuadro(768, 3042, 256, 494));
	this->Salto->push_back(crearCuadro(768, 3042, 256, 494));
	this->Salto->push_back(crearCuadro(768, 3042, 256, 494));
	this->Salto->push_back(crearCuadro(768, 3042, 256, 494));
	this->Salto->push_back(crearCuadro(768, 3042, 256, 494));
	this->Salto->push_back(crearCuadro(0, 3551, 256, 494));
	this->Salto->push_back(crearCuadro(0, 3551, 256, 494));
	this->Salto->push_back(crearCuadro(367, 3552, 256, 494));
	this->Salto->push_back(crearCuadro(367, 3552, 256, 494));
	this->Salto->push_back(crearCuadro(367, 3552, 256, 494));
	this->Salto->push_back(crearCuadro(768, 3490, 256, 576));
	this->Salto->push_back(crearCuadro(768, 3490, 256, 576));
	this->Salto->push_back(crearCuadro(768, 3490, 256, 576));
	this->Salto->push_back(crearCuadro(768, 3490, 256, 576));
	

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
	
	
	*SaltoDiagonalIzq = *SaltoDiagonal;
	std::reverse(SaltoDiagonalIzq->begin(), SaltoDiagonalIzq->end());
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

	if (unEstado == "SaltoDiagonalIzq"){
		
		return SaltoDiagonalIzq;
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


	


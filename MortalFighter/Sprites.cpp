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
	this->Quieto->push_back(crearCuadro(60, 18, 256, 494));
	this->Quieto->push_back(crearCuadro(60, 18, 256, 494));
	this->Quieto->push_back(crearCuadro(60, 18, 256, 494));
	this->Quieto->push_back(crearCuadro(377, 19, 256, 494));
	this->Quieto->push_back(crearCuadro(377, 19, 256, 494));
	this->Quieto->push_back(crearCuadro(724, 19, 256, 494));
	this->Quieto->push_back(crearCuadro(724, 19, 256, 494));
	this->Quieto->push_back(crearCuadro(724, 19, 256, 494));
	this->Quieto->push_back(crearCuadro(1071, 19, 256, 494));
	this->Quieto->push_back(crearCuadro(1071, 19, 256, 494));
	this->Quieto->push_back(crearCuadro(1447, 16, 256, 494));
	this->Quieto->push_back(crearCuadro(1447, 16, 256, 494));
	this->Quieto->push_back(crearCuadro(1447, 16, 256, 494));
	this->Quieto->push_back(crearCuadro(1797, 19, 256, 494));
	this->Quieto->push_back(crearCuadro(1797, 19, 256, 494));

	//Caminar para Adelante
	this->CaminandoParaAdelante->push_back(crearCuadro(9, 524, 256, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(9, 524, 256, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(378, 535, 320, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(378, 535, 320, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(745, 532, 320, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(745, 532, 320, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(1112, 532, 320, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(1112, 532, 320, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(1509, 542, 256, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(1509, 542, 256, 494));
	this->CaminandoParaAdelante->push_back(crearCuadro(1864, 538, 256, 494));
		
	//Salto
	this->Salto->push_back(crearCuadro(16, 1071, 256, 494));
	this->Salto->push_back(crearCuadro(16, 1071, 256, 494));
	this->Salto->push_back(crearCuadro(16, 1071, 256, 494));
	this->Salto->push_back(crearCuadro(354, 1047, 256, 576));
	this->Salto->push_back(crearCuadro(354, 1047, 256, 576));
	this->Salto->push_back(crearCuadro(640, 1053, 256, 576));
	this->Salto->push_back(crearCuadro(640, 1053, 256, 576));
	this->Salto->push_back(crearCuadro(640, 1053, 256, 576));
	this->Salto->push_back(crearCuadro(946, 1111, 256, 494));
	this->Salto->push_back(crearCuadro(946, 1111, 256, 494));
	this->Salto->push_back(crearCuadro(1231, 1111, 256, 494));
	this->Salto->push_back(crearCuadro(1231, 1111, 256, 494));
	this->Salto->push_back(crearCuadro(1231, 1111, 256, 494));
	this->Salto->push_back(crearCuadro(1517, 1111, 256, 494));
	this->Salto->push_back(crearCuadro(1517, 1111, 256, 494));
	this->Salto->push_back(crearCuadro(1854, 1072, 256, 576));
	this->Salto->push_back(crearCuadro(1854, 1072, 256, 576));
	this->Salto->push_back(crearCuadro(1854, 1072, 256, 576));

	//Salto Diagonal
	this->SaltoDiagonal->push_back(crearCuadro(30, 1673, 256, 576));
	this->SaltoDiagonal->push_back(crearCuadro(30, 1673, 256, 576));
	this->SaltoDiagonal->push_back(crearCuadro(30, 1673, 256, 576));
	this->SaltoDiagonal->push_back(crearCuadro(316, 1769, 256, 412));
	this->SaltoDiagonal->push_back(crearCuadro(316, 1769, 256, 412));
	this->SaltoDiagonal->push_back(crearCuadro(316, 1769, 256, 412));
	this->SaltoDiagonal->push_back(crearCuadro(621, 1771, 448, 330));	
	this->SaltoDiagonal->push_back(crearCuadro(1114, 1709, 256, 494));
	this->SaltoDiagonal->push_back(crearCuadro(1114, 1709, 256, 494));
	this->SaltoDiagonal->push_back(crearCuadro(1434, 1782, 512, 248));	
	this->SaltoDiagonal->push_back(crearCuadro(2002, 1670, 320, 576));
	this->SaltoDiagonal->push_back(crearCuadro(2002, 1670, 320, 576));
	this->SaltoDiagonal->push_back(crearCuadro(2002, 1670, 320, 576));
	this->SaltoDiagonal->push_back(crearCuadro(2383, 1675, 256, 576));
	this->SaltoDiagonal->push_back(crearCuadro(2383, 1675, 256, 576));
	this->SaltoDiagonal->push_back(crearCuadro(2383, 1675, 256, 576));
	
	//Caminar para Atrás
	this->CaminandoParaAtras->push_back(crearCuadro(36, 5195, 256, 494));	
	this->CaminandoParaAtras->push_back(crearCuadro(392, 5201, 256, 494));	
	this->CaminandoParaAtras->push_back(crearCuadro(718, 5193, 320, 494));
	this->CaminandoParaAtras->push_back(crearCuadro(718, 5193, 320, 494));
	this->CaminandoParaAtras->push_back(crearCuadro(1161, 5187, 256, 494));	
	this->CaminandoParaAtras->push_back(crearCuadro(1161, 5187, 256, 494));	
	this->CaminandoParaAtras->push_back(crearCuadro(1161, 5187, 256, 494));
	this->CaminandoParaAtras->push_back(crearCuadro(1497, 5186, 256, 494));	
	this->CaminandoParaAtras->push_back(crearCuadro(1874, 5186, 256, 494));	
	this->CaminandoParaAtras->push_back(crearCuadro(2187, 5192, 256, 494));

	
	
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


	


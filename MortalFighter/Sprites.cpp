#include "stdafx.h"
#include "Sprites.h"
#include <list>

SDL_Rect* Sprite::crearCuadro(int x, int y, int w, int h){
	SDL_Rect* unCuadro = new SDL_Rect;
	unCuadro->x = x;
	unCuadro->y = y;
	unCuadro->w = w;
	unCuadro->h = h;
	return unCuadro;
}

SDL_Rect* Sprite::crearCuadro(Json::Value cuadro){
	SDL_Rect* unCuadro = new SDL_Rect;
	unCuadro->x = cuadro.get("x", 0).asInt();
	unCuadro->y = cuadro.get("y", 0).asInt();
	unCuadro->w = cuadro.get("ancho", 0).asInt();
	unCuadro->h = cuadro.get("alto", 0).asInt();

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
	
	Json::Value raiz = ParsearSprites();
	Json::Value sprites = raiz["sprites"]["coordenadas"];

	Json::Value quieto = sprites["Quieto"];
	for (size_t i = 0; i < quieto.size(); i++)
		this->Quieto->push_back(crearCuadro(quieto[i]));

	Json::Value caminar = sprites["Caminar"];
	for (size_t i = 0; i < caminar.size(); i++)
		this->CaminandoParaAdelante->push_back(crearCuadro(caminar[i]));

	Json::Value salto = sprites["Salto"];
	for (size_t i = 0; i < salto.size(); i++)
		this->Salto->push_back(crearCuadro(salto[i]));

	Json::Value saltoDiagonal = sprites["SaltoDiagonal"];
	for (size_t i = 0; i < saltoDiagonal.size(); i++)
		this->SaltoDiagonal->push_back(crearCuadro(saltoDiagonal[i]));

	Json::Value caminarAtras = sprites["CaminarAtras"];
	for (size_t i = 0; i < caminarAtras.size(); i++)
		this->CaminandoParaAtras->push_back(crearCuadro(caminarAtras[i]));
		
	
	*SaltoDiagonalIzq = *SaltoDiagonal;
	std::reverse(SaltoDiagonalIzq->begin(), SaltoDiagonalIzq->end());
}

Json::Value	Sprite::ParsearSprites()
{
	Json::Value raiz;
	
	Json::Reader lector(Json::Features::strictMode());
	std::ifstream archivo(JSON_SPRITES, std::ifstream::binary);

	lector.parse(archivo, raiz, true);
	archivo.close();

	return raiz;	
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


	


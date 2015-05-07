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

Sprite::Sprite(std::string jsonSprites){
	this->Caida = new std::vector<SDL_Rect*>();
	this->Salto = new std::vector<SDL_Rect*>();
	this->CaminandoParaAdelante = new std::vector<SDL_Rect*>();
	this->CaminandoParaAtras = new std::vector<SDL_Rect*>();
	this->SaltoDiagonal = new std::vector<SDL_Rect*>();
	this->SaltoDiagonalIzq = new std::vector<SDL_Rect*>();
	this->Quieto = new std::vector<SDL_Rect*>();
	this->Agacharse = new std::vector<SDL_Rect*>();
	this->PatadaAlta = new std::vector<SDL_Rect*>();
	this->Golpeado = new std::vector<SDL_Rect*>();
	
	Json::Value raiz = ParsearSprites(jsonSprites);
	Json::Value sprites = raiz["sprites"]["coordenadas"];
		
	// Sprites Quieto
	cargarSprites(this->Quieto, "Quieto", sprites);
	// Sensores Quieto
	cargarSensores("Quieto", sprites);
	
	// Sprites Caminar
	cargarSprites(this->CaminandoParaAdelante, "Caminar", sprites);
	// Sensores Caminar
	cargarSensores("Caminar", sprites);

	// Sprites Salto
	cargarSprites(this->Salto, "Salto", sprites);
	// Sensores Salto
	cargarSensores("Salto", sprites);

	// Sprites SaltoDiagonal
	cargarSprites(this->SaltoDiagonal, "SaltoDiagonal", sprites);
	// Sensores SaltoDiagonal
	cargarSensores("SaltoDiagonal", sprites);
	
	// Sprites CaminarAtras
	cargarSprites(this->CaminandoParaAtras, "CaminarAtras", sprites);
	// Sensores CaminarAtras
	cargarSensores("CaminarAtras", sprites);

	// Sprites Agacharse
	cargarSprites(this->Agacharse, "Agacharse", sprites);
	// Sensores Agacharse
	cargarSensores("Agacharse", sprites);

	// Sprites PatadaAlta
	cargarSprites(this->PatadaAlta, "PatadaAlta", sprites);
	// Sensores PatadaAlta
	cargarSensores("PatadaAlta", sprites);

	// Sprites Golpeado
	cargarSprites(this->Golpeado, "Golpeado", sprites);
	// Sensores Golpeado
	cargarSensores("Golpeado", sprites);
		
	
	*SaltoDiagonalIzq = *SaltoDiagonal;
	std::reverse(SaltoDiagonalIzq->begin(), SaltoDiagonalIzq->end());
}


void Sprite::cargarSensores(std::string unEstadoStr, Json::Value spritesRaiz)
{
	Json::Value estadoSens = spritesRaiz[unEstadoStr]["sensores"];
	Json::Value estadoSprites = spritesRaiz[unEstadoStr]["secuenciaSprites"];
	this->Sensores.push_back(new std::vector<Sensor*>());
	for (size_t j = 0; j < estadoSens.size(); j++) {
		//seteo de variables
		float xSens = estadoSens[j].get("x", 0).asFloat() - estadoSprites[0].get("x", 0).asFloat();
		float ySens = estadoSens[j].get("y", 0).asFloat() - estadoSprites[0].get("y", 0).asFloat();
		std::pair<float, float> XYSens = std::make_pair(xSens, ySens);
		int anchoSens = estadoSens[j].get("ancho", 0).asFloat();
		int altoSens = estadoSens[j].get("alto", 0).asFloat();
		bool esHitBoxSens = estadoSens[j].get("esHitBox", false).asBool();
		// se carga el sensor
		this->Sensores.back()->push_back(new Sensor(XYSens, anchoSens, altoSens, esHitBoxSens, unEstadoStr));
	}
}

void Sprite::cargarSprites(std::vector<SDL_Rect*>* estadoCuadros, std::string unEstadoStr, Json::Value spritesRaiz)
{
	Json::Value estadoSprites = spritesRaiz[unEstadoStr]["secuenciaSprites"];
	for (size_t i = 0; i < estadoSprites.size(); i++)
		estadoCuadros->push_back(crearCuadro(estadoSprites[i]));
}

std::vector<std::vector<Sensor*>*> Sprite::getSensores() const
{
	return Sensores;
}

Json::Value	Sprite::ParsearSprites(std::string jsonSprites)
{
	Json::Value raiz;
	
	Json::Reader lector(Json::Features::strictMode());
	std::ifstream archivo(jsonSprites.c_str(), std::ifstream::binary);

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



	if (unEstado == "Agacharse"){

		return Agacharse;
	}
	if (unEstado == "PatadaAlta"){

		return PatadaAlta;
	}
	if (unEstado == "Golpeado"){

		return Golpeado;
	}

	return Quieto;
}

int Sprite::getConstantes(std::string estadoDelPersonaje){
	if (estadoDelPersonaje == "CaminarParaAdelante")
		return (tiempoCaminarParaAdelante / (this->CaminandoParaAdelante->size()) / MSxCUADRO);
	if (estadoDelPersonaje == "CaminarParaAtras")
		return (tiempoCaminarParaAtras / (this->CaminandoParaAtras->size()) / MSxCUADRO);
	if (estadoDelPersonaje == "Quieto")
		return (tiempoQuieto / (this->Quieto->size()) / MSxCUADRO);
	if (estadoDelPersonaje == "Salto")
		return (tiempoSalto / (this->Salto->size()) / MSxCUADRO);
	if (estadoDelPersonaje == "SaltoDiagonal")
		return (tiempoSaltoDiagonal / (this->SaltoDiagonal->size()) / MSxCUADRO);
	if (estadoDelPersonaje == "Agacharse")
		return (tiempoAgacharse / (this->Agacharse->size()) / MSxCUADRO);
	if (estadoDelPersonaje == "PatadaAlta")
		return (tiempoPatadaAlta / (this->PatadaAlta->size()) / MSxCUADRO);
	if (estadoDelPersonaje == "Golpeado")
		return (tiempoGolpeado / (this->Golpeado->size()) / MSxCUADRO);
	if (estadoDelPersonaje == "SaltoDiagonalIzq")
		return (tiempoSaltoDiagonalIzq / (this->SaltoDiagonalIzq->size()) / MSxCUADRO);
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



	for (size_t i = 0; i < Agacharse->size(); i++)
		delete Agacharse->at(i);
	Agacharse->clear();
	delete Agacharse;

	for (size_t i = 0; i < PatadaAlta->size(); i++)
		delete PatadaAlta->at(i);
	PatadaAlta->clear();
	delete PatadaAlta;

	for (size_t i = 0; i < Golpeado->size(); i++)
		delete Golpeado->at(i);
	Golpeado->clear();
	delete Golpeado;




	for (size_t i = 0; i < Quieto->size(); i++)
		delete Quieto->at(i);
	Quieto->clear();
	delete Quieto;

	for (size_t i = 0; i < Sensores.size(); i++) {
		for (size_t j = 0; j < Sensores[i]->size(); j++) 
			delete Sensores[i]->at(j);
		Sensores[i]->clear();
		delete Sensores[i];
	}
	Sensores.clear();

}


	


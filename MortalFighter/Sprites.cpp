#include "stdafx.h"
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
	this->Defensa = new std::vector<SDL_Rect*>();
	this->PatadaAlta = new std::vector<SDL_Rect*>();

	this->PatadaBaja = new std::vector<SDL_Rect*>();
	this->GolpeAlto = new std::vector<SDL_Rect*>();
	this->GolpeBajo = new std::vector<SDL_Rect*>();
	this->Arma = new std::vector<SDL_Rect*>();

	this->Golpeado = new std::vector<SDL_Rect*>();

	this->AgachadoGolpeado = new std::vector<SDL_Rect*>();
	this->SaltoGolpeado = new std::vector<SDL_Rect*>();
	this->AgachadoDefensa = new std::vector<SDL_Rect*>();

	this->Gancho = new std::vector<SDL_Rect*>();
	this->AgachadoGolpeBajo = new std::vector<SDL_Rect*>();
	this->SaltoGolpe = new std::vector<SDL_Rect*>();
	this->SaltoPatada = new std::vector<SDL_Rect*>();
	this->SaltoDiagonalPatada = new std::vector<SDL_Rect*>();
	this->AgachadoPatadaBaja = new std::vector<SDL_Rect*>();
	this->AgachadoPatadaAlta = new std::vector<SDL_Rect*>();
	this->Disparo = new std::vector<SDL_Rect*>();

	// si recibe una direccion de imagen busca el json asociado
	std::size_t found = jsonSprites.find(".png");
	if (found != std::string::npos)
		jsonSprites.replace(jsonSprites.end() - 3, jsonSprites.end(), "json");

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

	// Sprites Defensa
	cargarSprites(this->Defensa, "Defensa", sprites);
	// Sensores Defensa
	cargarSensores("Defensa", sprites);

	// Sprites PatadaAlta
	cargarSprites(this->PatadaAlta, "PatadaAlta", sprites);
	// Sensores PatadaAlta
	cargarSensores("PatadaAlta", sprites);

	// Sprites Golpeado
	cargarSprites(this->Golpeado, "Golpeado", sprites);
	// Sensores Golpeado
	cargarSensores("Golpeado", sprites);
		
	// Sprites AgachadoGolpeado
	cargarSprites(this->AgachadoGolpeado, "AgachadoGolpeado", sprites);
	// Sensores AgachadoGolpeado
	cargarSensores("AgachadoGolpeado", sprites);

	// Sprites SaltoGolpeado
	cargarSprites(this->SaltoGolpeado, "SaltoGolpeado", sprites);
	// Sensores SaltoGolpeado
	cargarSensores("SaltoGolpeado", sprites);

	// Sprites AgachadoDefensa
	cargarSprites(this->AgachadoDefensa, "AgachadoDefensa", sprites);
	// Sensores AgachadoDefensa
	cargarSensores("AgachadoDefensa", sprites);

	// Sprites PatadaBaja
	cargarSprites(this->PatadaBaja, "PatadaBaja", sprites);
	// Sensores PatadaBaja
	cargarSensores("PatadaBaja", sprites);

	// Sprites GolpeBajo
	cargarSprites(this->GolpeBajo, "GolpeBajo", sprites);
	// Sensores GolpeBajo
	cargarSensores("GolpeBajo", sprites);

	// Sprites GolpeAlto
	cargarSprites(this->GolpeAlto, "GolpeAlto", sprites);
	// Sensores GolpeAlto
	cargarSensores("GolpeAlto", sprites);

	// Sprites Arma
	cargarSprites(this->Arma, "Arma", sprites);
	// Sensores Arma
	cargarSensores("Arma", sprites);



	// Sprites Gancho
	cargarSprites(this->Gancho, "Gancho", sprites);
	// Sensores Gancho
	cargarSensores("Gancho", sprites);

	// Sprites AgachadoGolpeBajo
	cargarSprites(this->AgachadoGolpeBajo, "AgachadoGolpeBajo", sprites);
	// Sensores AgachadoGolpeBajo
	cargarSensores("AgachadoGolpeBajo", sprites);

	// Sprites SaltoGolpe
	cargarSprites(this->SaltoGolpe, "SaltoGolpe", sprites);
	// Sensores SaltoGolpe
	cargarSensores("SaltoGolpe", sprites);

	// Sprites SaltoPatada
	cargarSprites(this->SaltoPatada, "SaltoPatada", sprites);
	// Sensores SaltoPatada
	cargarSensores("SaltoPatada", sprites);

	// Sprites SaltoDiagonalPatada
	cargarSprites(this->SaltoDiagonalPatada, "SaltoDiagonalPatada", sprites);
	// Sensores SaltoDiagonalPatada
	cargarSensores("SaltoDiagonalPatada", sprites);

	// Sprites AgachadoPatadaBaja
	cargarSprites(this->AgachadoPatadaBaja, "AgachadoPatadaBaja", sprites);
	// Sensores AgachadoPatadaBaja
	cargarSensores("AgachadoPatadaBaja", sprites);

	// Sprites AgachadoPatadaAlta
	cargarSprites(this->AgachadoPatadaAlta, "AgachadoPatadaAlta", sprites);
	// Sensores AgachadoPatadaAlta
	cargarSensores("AgachadoPatadaAlta", sprites);

	// Sprites Disparo
	cargarSprites(this->Disparo, "Disparo", sprites);
	// Sensores Disparo
	cargarSensores("Disparo", sprites);
	

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
		int nSprite = estadoSens[j].get("nSprite", 0).asInt();
		float xSens = estadoSens[j].get("x", 0).asFloat();
		float ySens = estadoSens[j].get("y", 0).asFloat();
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

std::vector<SDL_Rect*>* Sprite::listaDeCuadros(ESTADO unEstado){
	if (unEstado.golpeado == GOLPEADO){
		if (unEstado.movimiento == SALTO || unEstado.movimiento == SALTODIAGIZQ || unEstado.movimiento == SALTODIAGDER)
			return SaltoGolpeado;
		return Golpeado;
	}
	if (unEstado.accion == PATADA_ALTA){
		return PatadaAlta;
	}
	if (unEstado.accion == PATADA_BAJA){
		return PatadaBaja;
	}
	if (unEstado.accion == GOLPE_ALTO){
		return GolpeAlto;
	}
	if (unEstado.accion == GOLPE_BAJO){
		return GolpeBajo;
	}
	if (unEstado.accion == ARMA_ARROJABLE){
		return Arma;
	}
	
	if (unEstado.movimiento == AGACHADO){
		if (unEstado.accion == GUARDIA)
			return AgachadoDefensa;
		return Agacharse;
	}
	if (unEstado.accion == GUARDIA){
		if (unEstado.movimiento == AGACHADO)
			return AgachadoDefensa;
		return Defensa;
	}
	if (unEstado.movimiento == CAMINARDER){
		return CaminandoParaAdelante;
	}
	if (unEstado.movimiento == CAMINARIZQ){
		return CaminandoParaAtras;
	}
	if (unEstado.movimiento == PARADO){
		return Quieto;
	}
	if (unEstado.movimiento == SALTO){
		return Salto;
	}
	if (unEstado.movimiento == SALTODIAGDER){
		return SaltoDiagonal;
	}
	if (unEstado.movimiento == SALTODIAGIZQ){
		
		return SaltoDiagonalIzq;
	}
	if (unEstado.movimiento == AGACHADO){

		return Agacharse;
	}
	return Quieto;
}

int Sprite::getConstantes(ESTADO estadoDelPersonaje){
	if (estadoDelPersonaje.golpeado == GOLPEADO){
		if (estadoDelPersonaje.movimiento == SALTO || estadoDelPersonaje.movimiento == SALTODIAGIZQ || estadoDelPersonaje.movimiento == SALTODIAGDER)
			return (tiempoSaltoGolpeado / (this->SaltoGolpeado->size()) / MSxCUADRO);
		if (estadoDelPersonaje.accion == GUARDIA)
			return (tiempoDefensa / (this->Defensa->size()) / MSxCUADRO);
		return (tiempoGolpeado / (this->Golpeado->size()) / MSxCUADRO);
	}
	if (estadoDelPersonaje.accion == PATADA_BAJA)
		return (tiempoPatadaBaja / (this->PatadaBaja->size()) / MSxCUADRO);
	if (estadoDelPersonaje.accion == GOLPE_ALTO)
		return (tiempoGolpeAlto / (this->GolpeAlto->size()) / MSxCUADRO);
	if (estadoDelPersonaje.accion == GOLPE_BAJO)
		return (tiempoGolpeBajo / (this->GolpeBajo->size()) / MSxCUADRO);
	if (estadoDelPersonaje.accion == ARMA_ARROJABLE)
		return (tiempoArmaArrojable / (this->Arma->size()) / MSxCUADRO);
	if (estadoDelPersonaje.accion == PATADA_ALTA)
		return (tiempoPatadaAlta / (this->PatadaAlta->size()) / MSxCUADRO);
	if (estadoDelPersonaje.accion == GUARDIA){
		if (estadoDelPersonaje.movimiento == AGACHADO)
			return (tiempoAgachadoDefensa / (this->Defensa->size()) / MSxCUADRO);
		return (tiempoDefensa / (this->Defensa->size()) / MSxCUADRO);
	}
	if (estadoDelPersonaje.movimiento == CAMINARDER)
		return (tiempoCaminarParaAdelante / (this->CaminandoParaAdelante->size()) / MSxCUADRO);
	if (estadoDelPersonaje.movimiento == CAMINARIZQ)
		return (tiempoCaminarParaAtras / (this->CaminandoParaAtras->size()) / MSxCUADRO);
	if (estadoDelPersonaje.movimiento == SALTO)
		return (tiempoSalto / (this->Salto->size()) / MSxCUADRO);
	if (estadoDelPersonaje.movimiento == SALTODIAGDER)
		return (tiempoSaltoDiagonal / (this->SaltoDiagonal->size()) / MSxCUADRO);
	if (estadoDelPersonaje.movimiento == AGACHADO)
		return (tiempoAgacharse / (this->Agacharse->size()) / MSxCUADRO);
	if (estadoDelPersonaje.movimiento == SALTODIAGIZQ)
		return (tiempoSaltoDiagonalIzq / (this->SaltoDiagonalIzq->size()) / MSxCUADRO);
	if (estadoDelPersonaje.movimiento == PARADO)
		return (tiempoQuieto / (this->Quieto->size()) / MSxCUADRO);
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

	for (size_t i = 0; i < Arma->size(); i++)
		delete Arma->at(i);
	Arma->clear();
	delete Arma;

	for (size_t i = 0; i < GolpeBajo->size(); i++)
		delete GolpeBajo->at(i);
	GolpeBajo->clear();
	delete GolpeBajo;

	for (size_t i = 0; i < GolpeAlto->size(); i++)
		delete GolpeAlto->at(i);
	GolpeAlto->clear();
	delete GolpeAlto;

	for (size_t i = 0; i < PatadaBaja->size(); i++)
		delete PatadaBaja->at(i);
	PatadaBaja->clear();
	delete PatadaBaja;

	SaltoDiagonalIzq->clear();
	delete SaltoDiagonalIzq;
		

	for (size_t i = 0; i < AgachadoDefensa->size(); i++)
		delete AgachadoDefensa->at(i);
	AgachadoDefensa->clear();
	delete AgachadoDefensa;

	for (size_t i = 0; i < SaltoGolpeado->size(); i++)
		delete SaltoGolpeado->at(i);
	SaltoGolpeado->clear();
	delete SaltoGolpeado;

	for (size_t i = 0; i < AgachadoGolpeado->size(); i++)
		delete AgachadoGolpeado->at(i);
	AgachadoGolpeado->clear();
	delete AgachadoGolpeado;

	for (size_t i = 0; i < Gancho->size(); i++)
		delete Gancho->at(i);
	Gancho->clear();
	delete Gancho;

	for (size_t i = 0; i < AgachadoGolpeBajo->size(); i++)
		delete AgachadoGolpeBajo->at(i);
	AgachadoGolpeBajo->clear();
	delete AgachadoGolpeBajo;

	for (size_t i = 0; i < SaltoGolpe->size(); i++)
		delete SaltoGolpe->at(i);
	SaltoGolpe->clear();
	delete SaltoGolpe;

	for (size_t i = 0; i < SaltoPatada->size(); i++)
		delete SaltoPatada->at(i);
	SaltoPatada->clear();
	delete SaltoPatada;

	for (size_t i = 0; i < SaltoDiagonalPatada->size(); i++)
		delete SaltoDiagonalPatada->at(i);
	SaltoDiagonalPatada->clear();
	delete SaltoDiagonalPatada;

	for (size_t i = 0; i < AgachadoPatadaBaja->size(); i++)
		delete AgachadoPatadaBaja->at(i);
	AgachadoPatadaBaja->clear();
	delete AgachadoPatadaBaja;

	for (size_t i = 0; i < AgachadoPatadaAlta->size(); i++)
		delete AgachadoPatadaAlta->at(i);
	AgachadoPatadaAlta->clear();
	delete AgachadoPatadaAlta;

	for (size_t i = 0; i < Disparo->size(); i++)
		delete Disparo->at(i);
	Disparo->clear();
	delete Disparo;

	for (size_t i = 0; i < Sensores.size(); i++) {
		for (size_t j = 0; j < Sensores[i]->size(); j++) 
			delete Sensores[i]->at(j);
		Sensores[i]->clear();
		delete Sensores[i];
	}
	Sensores.clear();

}


	


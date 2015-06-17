#include "stdafx.h"
#include "Fatality.h"
#include "Personaje.h"

Fatality::Fatality()
{
}

Fatality::Fatality(std::string jsonSprites)
{
	this->friendShipScorpion = new std::vector<SDL_Rect*>();
	this->fatalityLiuKangDragon = new std::vector<SDL_Rect*>();

	// si recibe una direccion de imagen busca el json asociado
	std::size_t found = jsonSprites.find(".png");
	if (found != std::string::npos)
		jsonSprites.replace(jsonSprites.end() - 3, jsonSprites.end(), "json");

	Json::Value raiz = this->parsearSprites(jsonSprites);
	Json::Value sprites = raiz["sprites"]["coordenadas"];

	// Sprites del friendShip de scopion
	this->cargarSprites(this->friendShipScorpion,"friendShip", sprites);
	
}

SDL_Rect* Fatality::crearCuadro(Json::Value cuadro){
	SDL_Rect* unCuadro = new SDL_Rect;
	unCuadro->x = cuadro.get("x", 0).asInt();
	unCuadro->y = cuadro.get("y", 0).asInt();
	unCuadro->w = cuadro.get("ancho", 0).asInt();
	unCuadro->h = cuadro.get("alto", 0).asInt();
	return unCuadro;
}

Json::Value	Fatality::parsearSprites(std::string jsonSprites)
{
	Json::Value raiz;

	Json::Reader lector(Json::Features::strictMode());
	std::ifstream archivo(jsonSprites.c_str(), std::ifstream::binary);
	bool parseoExitoso;
	if (!archivo.is_open()){
		Log::getInstancia().logearMensajeEnModo("  [BAD] No se pudo abrir el json de prueba o no existe", Log::MODO_WARNING);
		parseoExitoso = false;
	}
	else //el archivo existe, lo parseo
		parseoExitoso = lector.parse(archivo, raiz, true);
	archivo.close();

	return raiz;
}

void Fatality::cargarSprites(std::vector<SDL_Rect*>* estadoCuadros, std::string unFinish, Json::Value spritesRaiz)
{
	Json::Value estadoSprites = spritesRaiz[unFinish]["secuenciaSprites"];
	for (size_t i = 0; i < estadoSprites.size(); i++)
		estadoCuadros->push_back(crearCuadro(estadoSprites[i]));
}

std::vector<SDL_Rect*>* Fatality::spritesDeSecuencia(ESTADO unEstado)
{
	if (unEstado.golpeado == NOGOLPEADO){
		if (unEstado.accion == SIN_ACCION)
				return this->friendShipScorpion;
	}
}

std::vector<SDL_Rect*>* Fatality::spritesDeSecuencia()
{
	return this->friendShipScorpion;
}

int Fatality::getTiempoDeSecuenciaDelSprite()
{
	return ((tiempoSaltoGolpeado / (this->friendShipScorpion->size())) / MSxCUADRO);
}

int Fatality::getTiempoDeSecuenciaDelSprite(ESTADO estadoDelPersonaje)
{
	if (estadoDelPersonaje.golpeado == NOGOLPEADO)
	{
		if (estadoDelPersonaje.movimiento == SIN_ACCION )
			return ((tiempoSaltoGolpeado / (this->friendShipScorpion->size())) / MSxCUADRO);
		/*if (estadoDelPersonaje.movimiento == AGACHADO)
			return ((tiempoAgachadoGolpeado / (this->AgachadoGolpeado->size())) / MSxCUADRO);
		if (estadoDelPersonaje.accion == GUARDIA)
			return ((tiempoDefensa / (this->Defensa->size())) / MSxCUADRO);
		return ((tiempoGolpeado / (this->Golpeado->size())) / MSxCUADRO);*/
	}
}

Fatality::~Fatality()
{
	 //Borra los punteros del friendShip
	for (size_t i = 0; i < friendShipScorpion->size(); i++)
		delete friendShipScorpion->at(i);
	friendShipScorpion->clear();
	//delete friendShipScorpion;

	//Borra los punteros de la fatality de liu kang
	for (size_t i = 0; i < fatalityLiuKangDragon->size(); i++)
		delete fatalityLiuKangDragon->at(i);
	fatalityLiuKangDragon->clear();
	//delete fatalityLiuKangDragon;
}

#pragma once
#include "Personaje.h"

class Fatality
{
private:
	std::vector<SDL_Rect*>* friendShipScorpion;
	std::vector<SDL_Rect*>* fatalityLiuKangDragon;
public:

	Fatality(std::string);
	SDL_Rect* crearCuadro(Json::Value cuadro);
	Json::Value	parsearSprites(std::string jsonSprites);
	void cargarSprites(std::vector<SDL_Rect*>* estadoCuadros, std::string unFinish, Json::Value spritesRaiz);
	int getTiempoDeSecuenciaDelSprite();
	int getTiempoDeSecuenciaDelSprite(ESTADO estadoDelPersonaje);
	std::vector<SDL_Rect*>* spritesDeSecuencia(ESTADO unEstado);
	std::vector<SDL_Rect*>* spritesDeSecuencia();
	Fatality();
	~Fatality();
};


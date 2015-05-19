#pragma once
#include <vector>
#include <string>
#include "Sensor.h"
#include "Personaje.h"

// por dependencia circular declaro y despues 
// se define en Personaje.h
struct ESTADO;

class Sprite{
private:	
	std::vector<SDL_Rect*>* Caida;
	std::vector<SDL_Rect*>* Salto;
	std::vector<SDL_Rect*>* CaminandoParaAdelante;
	std::vector<SDL_Rect*>* CaminandoParaAtras;
	std::vector<SDL_Rect*>* SaltoDiagonal;
	std::vector<SDL_Rect*>* SaltoDiagonalIzq;
	std::vector<SDL_Rect*>* Quieto;
	std::vector<SDL_Rect*>* Defensa;

	std::vector<SDL_Rect*>*Agacharse;
	std::vector<SDL_Rect*>*PatadaAlta;
	std::vector<SDL_Rect*>*Golpeado;
	std::vector<SDL_Rect*>*PatadaBaja;
	std::vector<SDL_Rect*>*GolpeAlto;
	std::vector<SDL_Rect*>*GolpeBajo;
	std::vector<SDL_Rect*>*Arma;

	std::vector<SDL_Rect*>*AgachadoGolpeado;
	std::vector<SDL_Rect*>*SaltoGolpeado;
	std::vector<SDL_Rect*>*AgachadoDefensa;

	std::vector<SDL_Rect*>* Gancho;
	std::vector<SDL_Rect*>* AgachadoGolpeBajo;
	std::vector<SDL_Rect*>* SaltoGolpe;
	std::vector<SDL_Rect*>* SaltoPatada;
	std::vector<SDL_Rect*>* SaltoDiagonalPatada;
	std::vector<SDL_Rect*>* AgachadoPatadaBaja;
	std::vector<SDL_Rect*>* AgachadoPatadaAlta;
	std::vector<SDL_Rect*>* Disparo;

	std::vector<float>* cuadrosRep;

	std::vector<std::vector<Sensor*>*> Sensores;
	std::vector<Sensor*> sensoresDisparo;
	SDL_Rect* crearCuadro(int x, int y, int w, int h);
	SDL_Rect* crearCuadro(Json::Value cuadro);	
	void cargarSensores(std::string unEstadoStr, Json::Value spritesRaiz);
	void cargarSprites(std::vector<SDL_Rect*>* estadoCuadros, std::string unEstadoStr, Json::Value spritesRaiz);	


public:
	Sprite(std::string);
	std::vector<SDL_Rect*>* listaDeCuadros(ESTADO unEstado);
	Json::Value	ParsearSprites(std::string);
	std::vector<std::vector<Sensor*>*> getSensores() const;
	std::vector<Sensor*> getSensoresDisparo() const;
	int getConstantes(ESTADO estadoDelPersonaje);
	~Sprite();
};

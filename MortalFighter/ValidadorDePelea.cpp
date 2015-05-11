#include "stdafx.h"
#include "ValidadorDePelea.h"


ValidadorDePelea::ValidadorDePelea()
{
}


void ValidadorDePelea::validarPeleaDesdeParaLosPeronajes(Json::Value unaPelea, std::vector<Personaje*>* personajes){
	std::string fighters;
	std::string peleaAux;

	int posicion;
	size_t i = 0;
	bool corte = false;

	bool peleador1 = false;
	bool peleador2 = false;

	pelea = PELEA_INICIAL;
	if (!unaPelea)
	{
		Log::getInstancia().logearMensajeEnModo("[BAD] Fallo el parseo de la pelea", Log::MODO_WARNING);
		Log::getInstancia().logearMensajeEnModo("Se carga el combate por defecto", Log::MODO_WARNING);
		return;
	}
	else{
		if (unaPelea.isMember("fighters") && (unaPelea.get("fighters", PELEA_INICIAL).isString()) ){
			fighters = unaPelea.get("fighters", PELEA_INICIAL).asString();

			posicion = fighters.find(" ");

			//PELEADOR 1
			peleaAux = fighters;
			peleaAux = peleaAux.substr(0, posicion);

			while (!corte && i < personajes->size()){
				if (peleaAux == personajes->at(i)->getNombre()){
					peleador1 = true;
					corte = true;
				}
				i++;
			}

			//PELEADOR 2
			fighters = fighters.substr(posicion + 1, fighters.size() - posicion);
			posicion = fighters.find(" ");
			fighters = fighters.substr(posicion + 1, fighters.size() - posicion);

			i = 0;
			while (!corte && i < personajes->size()){
				if (fighters == personajes->at(i)->getNombre()){
					peleador2 = true;
					corte = true;
				}
				i++;
			}

			if (peleador1 && peleador2) pelea = unaPelea.get("fighters", PELEA_INICIAL).asString();
			else Log::getInstancia().logearMensajeEnModo("Se carga el combate por defecto", Log::MODO_WARNING);
		}
		else {
			Log::getInstancia().logearMensajeEnModo("Se carga el combate por defecto", Log::MODO_WARNING);
		}
	}
	Log::getInstancia().logearMensajeEnModo("Se cargo el combate correctamente", Log::MODO_DEBUG);
}


std::string ValidadorDePelea::getPelea(){
	return pelea;
}


ValidadorDePelea::~ValidadorDePelea()
{
	pelea.clear();
}

#include "stdafx.h"
#include "ValidadorDePelea.h"


ValidadorDePelea::ValidadorDePelea()
{
	laPelea = nullptr;
}


void ValidadorDePelea::validarPeleaDesdeParaLosPeronajes(Json::Value unaPelea, std::vector<Personaje*>* personajes){
	std::string fighters;
	std::string peleaAux;

	int posicion;
	size_t i;
	bool corte = false;

	bool peleador1 = false;
	bool peleador2 = false;

	laPelea = new Pelea();
	laPelea->setPersonaje1(personajes->at(0));
	if (personajes->size() > 1) laPelea->setPersonaje2(personajes->at(1));
	else laPelea->setPersonaje2(personajes->at(0));

	if (!unaPelea)
	{
		Log::getInstancia().logearMensajeEnModo("[BAD] Fallo el parseo de la pelea", Log::MODO_WARNING);
		Log::getInstancia().logearMensajeEnModo("Se carga el combate por defecto", Log::MODO_WARNING);
		pelea = laPelea->getPersonaje1()->getNombre() + " vs " + laPelea->getPersonaje2()->getNombre();
		return;
	}
	else{
		if (unaPelea.isMember("fighters") && (unaPelea.get("fighters", PELEA_INICIAL).isString())){
			fighters = unaPelea.get("fighters", PELEA_INICIAL).asString();

			posicion = fighters.find(" vs");
			if (posicion == std::string::npos) posicion = fighters.find(" VS");
			if (posicion != std::string::npos){

				//PELEADOR 1
				peleaAux = fighters;
				peleaAux = peleaAux.substr(0, posicion);
				i = 0;
				corte = false;
				while (!corte && (i < personajes->size())){
					if (peleaAux == personajes->at(i)->getNombre()){
						peleador1 = true;
						corte = true;
						laPelea->setPersonaje1(personajes->at(i));
						Log::getInstancia().logearMensajeEnModo("Se carga el primer peleador correctamente", Log::MODO_DEBUG);
					}
					i++;
				}
				
				//PELEADOR 2
				fighters = fighters.substr(posicion + 3, fighters.size() - posicion);
				posicion = fighters.find(" ");
				if (posicion != std::string::npos){
					fighters = fighters.substr(posicion + 1, fighters.size() - posicion);

					i = 0;
					corte = false;
					while (!corte && (i < personajes->size())){
						if (fighters == personajes->at(i)->getNombre()){
							peleador2 = true;
							corte = true;
							laPelea->setPersonaje2(personajes->at(i));
							Log::getInstancia().logearMensajeEnModo("Se carga el segundo peleador correctamente", Log::MODO_DEBUG);
						}
						i++;
					}
				}
				
				if (peleador1)	pelea = unaPelea.get("fighters", PELEA_INICIAL).asString();
				else Log::getInstancia().logearMensajeEnModo("Se carga el primer peleador por defecto", Log::MODO_WARNING);

				if (peleador2)	pelea = unaPelea.get("fighters", PELEA_INICIAL).asString();
				else Log::getInstancia().logearMensajeEnModo("Se carga el segundo peleador por defecto", Log::MODO_WARNING);
			}
			else {
				Log::getInstancia().logearMensajeEnModo("Se carga el combate por defecto", Log::MODO_WARNING);
			}
		}

		else{
			Log::getInstancia().logearMensajeEnModo("[BAD] Fallo el parseo de la pelea", Log::MODO_WARNING);
			Log::getInstancia().logearMensajeEnModo("Se carga el combate por defecto", Log::MODO_WARNING);
		}
	}

	pelea = laPelea->getPersonaje1()->getNombre() + " vs " + laPelea->getPersonaje2()->getNombre();
	if (laPelea->getPersonaje1() == laPelea->getPersonaje2()){
		Personaje* unPersonaje = new Personaje();
		unPersonaje->copiarAtributosDe(laPelea->getPersonaje2());
		laPelea->setPersonaje2(unPersonaje);
	}
	Log::getInstancia().logearMensajeEnModo("Se cargo el combate correctamente", Log::MODO_DEBUG);
}


std::string ValidadorDePelea::getPeleaComoString(){
	return pelea;
}


Pelea* ValidadorDePelea::getPelea(){
	return laPelea;
}


ValidadorDePelea::~ValidadorDePelea()
{
	pelea.clear();
	if (laPelea != nullptr) delete laPelea;
}

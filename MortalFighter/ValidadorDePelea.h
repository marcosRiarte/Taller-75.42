#pragma once
#include "Pelea.h"

class ValidadorDePelea
{
private:
	std::string pelea;
	Pelea* laPelea;

public:
	ValidadorDePelea();
	void validarPeleaDesdeParaLosPeronajes(Json::Value unaPelea, std::vector<Personaje*>* personajes);
	Pelea* getPelea();
	std::string ValidadorDePelea::getPeleaComoString();
	~ValidadorDePelea();
};


#pragma once
#include "Validador.h"
class ValidadorDeCapas :
	public Validador
{
private:
	std::vector<Capa*>* capas;

	bool validarCapas(float *anchoCapa, std::string *fondo, size_t numerocapa);

public:
	ValidadorDeCapas();
	bool validarCapasDesde(Json::Value capasParseadas);
	std::vector<Capa*>* getCapas();
	~ValidadorDeCapas();
};


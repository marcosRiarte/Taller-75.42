#pragma once
#include "Vector2D.h"

class Cuerpo
{
public:
	Cuerpo();
private:
	std::string nombre;
	vector2D posicion, velocidad;
	float masa;
};
#pragma once
#include "Vector2D.h"

class Cuerpo
{
public:
	Cuerpo();

	inline const vector2D& getPosicion() const
	{
		return posicion;
	}

	inline void SetPosicion(const vector2D& unaPosicion)
	{
		posicion = unaPosicion;
	}

	inline const vector2D& getVelocidad() const
	{
		return velocidad;
	}

	inline void SetVelocidad(const vector2D& unaVelocidad)
	{
		velocidad = unaVelocidad;
	}

	inline float getMasa() const
	{
		return masa;
	}

	// Aplica un impulso lineal al cuerpo. Modifica inmediatamente la velocidad
	// El impulso ser�a en unidades de N.s o Kg.m/s
	inline void Cuerpo::aplicarImpulso(vector2D& impulso, const vector2D& point, bool wake)
	{
		impulso *= masa;
		velocidad += impulso;

	}

private:
	std::string nombre;
	vector2D posicion, velocidad;
	float masa;
};
#pragma once
#include "Vector2D.h"
#include "Personaje.h"

struct defCuerpo
{
	// constructor con valores por defecto
	defCuerpo()
	{
		nombre = "Scorpion";
		posicion = vector2D(0.0f, 0.0f);
		velocidad = vector2D(0.0f, 0.0f);		
		masa = 15.0f;
	}

	std::string nombre;
	vector2D posicion, velocidad;
	float masa;
};

class Cuerpo
{
public:
	Cuerpo(const  defCuerpo unaDefCuerpo);

	inline const vector2D& getPosicion() const
	{
		return posicion;
	}

	inline void SetPosicion(const vector2D& unaPosicion)
	{
		posicion = unaPosicion;
	}

	void sumarPosicion(const vector2D& unaPosicion)
	{
		
		posicion += unaPosicion;
		// Que no se mueva debajo del piso, mejorar a condicion piso generica
		if (estaEnPiso() && unaPosicion.y < 0.0f) {
			posicion.y = 0.0f;
		}
	}

	inline const vector2D& getVelocidad() const
	{
		return velocidad;
	}

	inline void SetVelocidad(const vector2D& unaVelocidad)
	{
		velocidad = unaVelocidad;
	}

	void sumarVelocidad(const vector2D& unaVelocidad)
	{
		velocidad += unaVelocidad;		
	}


	inline float getMasa() const
	{
		return masa;
	}

	// Devuelve true si está en contacto con el piso o false en caso contrario
	bool estaEnPiso();

	// Aplica un impulso lineal al cuerpo. Modifica inmediatamente la velocidad
	// El impulso sería en unidades de N.s o Kg.m/s
	inline void Cuerpo::aplicarImpulso(vector2D& impulso)
	{
		impulso /= masa;
		velocidad += impulso;
	}

	//observer extremadamente simplificado, mejorar
	void recibeObservador(Personaje* unObservador);

	void notificarObservadores();

	void moverDerecha();
	void moverIzquierda();

private:
	std::string nombre;
	vector2D posicion, velocidad;
	float masa;
	Personaje* observador;	
};
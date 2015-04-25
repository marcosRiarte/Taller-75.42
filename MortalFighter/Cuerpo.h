#pragma once
#include "Personaje.h"
#include "Mundo.h"

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
	Cuerpo(const  defCuerpo unaDefCuerpo, Controlador* controladorNuevo);

	inline const vector2D& getPosicion() const
	{
		return posicion;
	}

	inline void SetPosicion(const vector2D& unaPosicion)
	{
		posicion = unaPosicion;
	}

	void sumarPosicion(const vector2D& unaPosicion);

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

	// Obtener el controlador asociado
	inline Controlador* getControlador()  const
	{
		return controlador;
	}

	// Devuelve true si está en contacto con el piso o false en caso contrario
	bool estaEnPiso();

	// Devuelve true si está en borde derecho o false en caso contrario
	// borde izquierdo se toma cero siempre
	bool estaEnBorde();

	// Aplica un impulso lineal al cuerpo. Modifica inmediatamente la velocidad
	// El impulso sería en unidades de N.s o Kg.m/s
	inline void aplicarImpulso(vector2D& impulso)
	{
		impulso /= masa;
		velocidad += impulso;
	}

	//observer extremadamente simplificado, mejorar
	void recibeObservador(Personaje* unObservador);

	void notificarObservadores(ESTADO nuevoEstado);

	void mover(float unaDistancia);

private:
	Controlador* controlador;
	std::string nombre;
	vector2D posicion, velocidad;
	float masa;
	Personaje* observador;
	float yPiso;
};
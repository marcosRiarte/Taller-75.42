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
		demora = 0;
		estaFrenado = false;
		estaGolpeado = false;
		estaSuperpuesto = false;
	}

	std::string nombre;
	vector2D posicion, velocidad;
	float masa;
	bool estaFrenado;
	bool estaGolpeado;
	bool estaSuperpuesto;
	int demora;
};

class Cuerpo
{
public:
	Cuerpo(const  defCuerpo unaDefCuerpo, Controlador* controladorNuevo, float posicionEnX, Personaje* refPersonaje);

	inline const vector2D& getPosicion() const
	{
		return posicion;
	}

	// Obtiene los sensores activos actualmente
	std::vector<Sensor*>* getSensores() const
	{
		return getSensoresActivos();
	}

	// Inicializa el conjunto de todos los sensores asociados al cuerpo
	void setSensores(std::vector<std::vector<Sensor*>*> sensoresNuevo)
	{
		sensores = sensoresNuevo;
	}

	void setEstadoAnterior(ESTADO unestadoAnterior){
		estadoAnterior = unestadoAnterior;
	}

	// Le pasa el nombre del estado actual para activar los sensores correspondientes
	inline void SetSensorActivoStr(ESTADO estadoActual)
	{
		if (estadoActual.golpeado == GOLPEADO){
			if (estadoActual.movimiento == SALTO || estadoActual.movimiento == SALTODIAGDER || estadoActual.movimiento == SALTODIAGIZQ)
				sensorActivoStr = "SaltoGolpeado";
				sensorActivoStr = "Golpeado";
		}
		if (estadoActual.accion != SIN_ACCION){
		if (estadoActual.accion == PATADA_BAJA){
			sensorActivoStr = "PatadaBaja";
		}
		if (estadoActual.accion == PATADA_ALTA){
			sensorActivoStr = "PatadaAlta";
		}
		if (estadoActual.accion == GOLPE_BAJO){
			sensorActivoStr = "GolpeBajo";
		}
		if (estadoActual.accion == GOLPE_ALTO){
			sensorActivoStr = "GolpeAlto";
		}
		if (estadoActual.accion == ARMA_ARROJABLE){
			sensorActivoStr = "Arma";
		}
		}
		else{
		if (estadoActual.movimiento == CAMINARDER)
			sensorActivoStr = "Caminar";
		if (estadoActual.movimiento == PARADO)
			sensorActivoStr = "Quieto";
		if (estadoActual.movimiento == SALTO)
			sensorActivoStr = "Salto";
		if ((estadoActual.movimiento == SALTODIAGIZQ) || (estadoActual.movimiento == SALTODIAGDER))
			sensorActivoStr = "SaltoDiagonal";
		if (estadoActual.movimiento == CAMINARIZQ)
			sensorActivoStr = "CaminarAtras";
		if (estadoActual.movimiento == AGACHADO)
			sensorActivoStr = "Agacharse";
		}
	}

	inline void SetPosicion(const vector2D& unaPosicion)
	{
		posicion = unaPosicion;
	}

	inline void Superponer()
	{
		estaSuperpuesto = true;
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

	inline void SetVelocidadX(float velocidadenX)
	{
		velocidad.x = velocidadenX;
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

	// Devuelve true si lo fajaron o false en caso contrario
	bool estaGolpeado();

	// Devuelve la demora que hay para la reproduccion del sprite de patada, sino duraba un instante....

	//Xjose
	int GetDemora();
	void Cuerpo::setDemora(int demoratiempo);
	void Cuerpo::DisminuirDemora();

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

	// Evita que el cuerpo se mueva, sirve para evitar que los cuerpos se muevan
	// en ocasiones particulares del juego.
	//xjose y cuales son las ocaciones particulares???
	inline void Frenar()
	{
		estaFrenado = true;
	}

	// Libera al cuerpo para que se mueva, sirve para evitar que los cuerpos se muevan
	// en ocasiones particulares del juego.
	inline void Liberar()
	{
		estaFrenado = false;
	}

	inline bool EstaFrenado()
	{
		return estaFrenado;
	}

	inline bool EstaSuperpuesto()
	{
		return estaSuperpuesto;
	}
	//xjose .......................

	//pre recibe 2 cuerpos. si ambos estan en el piso, desplaza al cuerpo que estas tratando hacia la izquierda si es izquierdo
	//ojo chequear que no este en borde por que sino no lo podes desplazar
	//OJO LO HACE CON UN SOLO CUERPO por que este metodo es llamado luego con el otro cuerpo  va a hacer lo mismo
	//al final chequear si se resolvio o no.
	//si se resolvio setear estaSuperpuesto = false;
	//TODO XJOSE
	inline void ResolverSuperposicion()
	{
		//si ya se qe estoy frutenando
		// if (Mundo::DeterminarSuperposicionDeCuerpos())
		//resolve

		//else 
        // SI ESTA resuelta setear en falso
		estaSuperpuesto = false;
	}

	//observer extremadamente simplificado, mejorar
	void recibeObservador(Personaje* unObservador);

	int notificarObservadores(ESTADO nuevoEstado);

	void mover(float unaDistancia);
	ESTADO getEstado();
	ESTADO getEstadoAnterior();

	Personaje* Cuerpo::getRefPersonaje();

private:
	std::vector<Sensor*>* getSensoresActivos() const;
	Controlador* controlador;
	std::string nombre;
	vector2D posicion, velocidad;
	float masa;
	Personaje* observador;
	float yPiso;
	bool estaFrenado;
	bool estaSuperpuesto;
	int demora;
	ESTADO estadoAnterior;
	Personaje* refPersonaje;
	std::vector<std::vector<Sensor*>*> sensores;
	std::string sensorActivoStr;
};
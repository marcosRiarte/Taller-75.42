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
	Cuerpo(const  defCuerpo unaDefCuerpo, Controlador* controladorNuevo);

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

	void setSensoresProyectil(std::vector<Sensor*> sensoresProyectil)
	{
		sensoresDisparo = sensoresProyectil;
	}

	std::vector<Sensor*> getSensoresProyectil(){
		return sensoresDisparo;
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

	inline void Separados()
	{
		estaSuperpuesto = false;
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
	void setDemora(int demoratiempo);
	void DisminuirDemora();
	bool HayDemora();


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

	//PRE: recibe la posicion de dos cuerpos del mundo y el espacio que estan ocupando (guarda por que no es un punto sino un rectangulo)
	// si los cuerpos estan en el piso solo cheqea eje x que no se esten invadiendo
	//si los cuerpoes no estan en el piso tiene que determinar si se van a intersectar en el eje x e y en realidad esta parte tiene que evitar que se toquen 
	//devuelve true si el perosnaje esta ocupando espacio del  otro personaje
	 bool DeterminarSuperposicionDeCuerpos(vector2D *PosicionOtroCuerpo){
		
		//comparar estas dos posiciones para ver si se estan tocando
		//frutin abajo

		//if (Cuerpo::getPosicion() == PosicionOtroCuerpo )
			
		return true;
	}

	//pre recibe 2 cuerpos. si ambos estan en el piso, desplaza al cuerpo que estas tratando hacia la izquierda si es izquierdo
	//ojo chequear que no este en borde por que sino no lo podes desplazar
	//OJO LO HACE CON UN SOLO CUERPO por que este metodo es llamado luego con el otro cuerpo  va a hacer lo mismo
	//al final chequear si se resolvio o no.
	//si se resolvio setear estaSuperpuesto = false;
	//TODO XJOSE
	inline void ResolverSuperposicion(vector2D *PosicionOtroCuerpo)
	{
		

		if (DeterminarSuperposicionDeCuerpos(PosicionOtroCuerpo))
		{
			//resolve
		}
		

		else // SI ESTA resuelta setear en falso
		{
			estaSuperpuesto = false;
		}
        
		
	}

	//observer extremadamente simplificado, mejorar
	void recibeObservador(Personaje* unObservador);

	int notificarObservadores(ESTADO nuevoEstado);

	void mover(float unaDistancia);
	ESTADO getEstado();
	ESTADO getEstadoAnterior();
	std::string getNombre();

	Personaje* Cuerpo::getRefPersonaje();
	Sprite* getSprite() const;

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
	std::vector<std::vector<Sensor*>*> sensores;
	std::vector<Sensor*> sensoresDisparo;
	std::string sensorActivoStr;
};
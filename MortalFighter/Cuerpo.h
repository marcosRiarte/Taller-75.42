#pragma once
#include "Personaje.h"
#include "Mundo.h"

struct defCuerpo
{
	// constructor con valores por defecto
	defCuerpo()
	{
		nombre = "Scorpion"; //Xjose error esto esta hardco....
		posicion = vector2D(0.0f, 0.0f);
		velocidad = vector2D(0.0f, 0.0f);
		masa = 15.0f;
		demora = 0;
		estaFrenado = false;
		//xjose NO INSULTARME
		estaGolpeado = false; // PARA PROBARLO RAPIDAMENTE
	}

	std::string nombre;
	vector2D posicion, velocidad;
	float masa;
	bool estaFrenado;
	bool estaGolpeado;
	int demora;
};

class Cuerpo
{
public:
	Cuerpo(const  defCuerpo unaDefCuerpo, Controlador* controladorNuevo, float posicionEnX);

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
		if (estadoActual == DER)
			sensorActivoStr = "Caminar";
		if (estadoActual == QUIETODER)
			sensorActivoStr = "Quieto";
		if (estadoActual == ARRIBA_DER)
			sensorActivoStr = "Salto";
		if ((estadoActual == SALTOIZQ_DER) || (estadoActual == SALTODER_DER))
			sensorActivoStr = "SaltoDiagonal";
		if (estadoActual == IZQ_DER)
			sensorActivoStr = "CaminarAtras";
		if (estadoActual == ABAJO_DER)
			sensorActivoStr = "Agacharse";
		if (estadoActual == P_ALTADER)
			sensorActivoStr = "PatadaAlta";
		if (estadoActual == GOLPEADOIZQ)
			sensorActivoStr = "Golpeado";
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

	//xjose .......................

	

	//observer extremadamente simplificado, mejorar
	void recibeObservador(Personaje* unObservador);

	void notificarObservadores(ESTADO nuevoEstado);

	void mover(float unaDistancia);
	ESTADO getEstado();
	ESTADO getEstadoAnterior();

private:
	std::vector<Sensor*>* getSensoresActivos() const;
	Controlador* controlador;
	std::string nombre;
	vector2D posicion, velocidad;
	float masa;
	Personaje* observador;
	float yPiso;
	bool estaFrenado;
	int demora; // esto deberia ser privado y con metodo incrementar demora o disminuir demora... es para que reproduzca bien la patada
	int demoraAux;
	ESTADO nuevoEstado;
	ESTADO estadoAnterior;
	
	std::vector<std::vector<Sensor*>*> sensores;
	std::string sensorActivoStr;
};
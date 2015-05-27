#include "stdafx.h"
#include "Cuerpo.h"

Cuerpo::Cuerpo(const defCuerpo unaDefCuerpo, Controlador* controladorNuevo)
{
	controlador = controladorNuevo;
	nombre = unaDefCuerpo.nombre;
	posicion = unaDefCuerpo.posicion;
	velocidad = unaDefCuerpo.velocidad;
	masa = unaDefCuerpo.masa;
	yPiso = Parser::getInstancia().getEscenario().getYPiso();
	posicion.y = yPiso;
	estaFrenado = unaDefCuerpo.estaFrenado;
	demora = unaDefCuerpo.demora; //xjose
	sensorActivoStr = "";
	estadoAnterior.accion = SIN_ACCION;
	estadoAnterior.golpeado = NOGOLPEADO;
	estadoAnterior.movimiento = PARADO;
}

std::vector<Sensor*>* Cuerpo::getSensoresActivos() const
{
	for (size_t i = 0; i<sensores.size(); i++)
		if (sensores[i]->size() == 0) return sensores[0];
		else if (sensores[i]->at(0)->getEstadoStr() == sensorActivoStr)
			return sensores[i];

	// si no se seteo un sensor activo pasa el primero
	return sensores[0];
}

void Cuerpo::setposProyectilAnterior(float unaposAnteriorProyectil){
	posAnteriorProyectil = unaposAnteriorProyectil;
}

float Cuerpo::getXProyectilAnterior(){
	return posAnteriorProyectil;
}

bool Cuerpo::estaEnPiso()
{
	if (posicion.y > yPiso)
		return false;

	return true;
}

int Cuerpo::GetDemora()
{
	return demora;
}

ESTADO Cuerpo::getEstado()
{
	return observador->getEstado();
}

std::string Cuerpo::getNombre()
{
	return nombre;
}

ESTADO Cuerpo::getEstadoAnterior()
{
	return estadoAnterior;
}

void Cuerpo::setDemora(int demoratiempo)
{
		demora = demoratiempo;
}

void Cuerpo::DisminuirDemora()
{
	 if (demora>0) 	demora--;
}

bool Cuerpo::HayDemora()
{
	if (GetDemora() > 0) return true;
	
	return false;

}

bool Cuerpo::estaEnBorde()
{
	// nacho: chequea el borde considerando ancho del personaje
	// el +2 es para que no se vea una linea en el limite
	if (posicion.x + getRefPersonaje()->getAncho() + 2 < Parser::getInstancia().getEscenario().getAncho())
		return false;

	return true;
}

// XERROR Nacho: invento esta funcion por que la modificacion que le agrego posicion.x>0 hace que pinche el programa
bool Cuerpo::estaEnBorde2()
{
	// nacho: chequea el borde considerando ancho del personaje
	// el +2 es para que no se vea una linea en el limite
	if (posicion.x + getRefPersonaje()->getAncho() + 2 < Parser::getInstancia().getEscenario().getAncho()&& (posicion.x>0))
		return false;

	return true;
}

// nacho: devuelve el max x del sensor
int Cuerpo::getSensorLargo()
{
	// valor default
	int xSensor = 0;
	int maximo = 0;
	std::vector<Sensor*>* sensoresAct = getSensores();
	for (size_t i = 0; i < sensoresAct->size(); i++)
	{
		int xSensor = sensoresAct->at(i)->getPosicion().first;
		if (xSensor > maximo) 			
			maximo = xSensor;		
	}

	return maximo;
}

void Cuerpo::limitarAEscenario()
{
	ManejadorULogicas manejadorUnidades;
	float xSensorLog = manejadorUnidades.darLongUnidades(getSensorLargo());

	// limita inicio del escenario
	if (posicion.x + xSensorLog < 0)
		// la posicion tiene que ser negativa por el espacio 
		// transparente del sprite, se toma el x sensor, como inicio
		posicion.x = -xSensorLog;
	

	float largoPersonaje = getRefPersonaje()->getAncho() - xSensorLog;

	// limita fin de escenario
	if (posicion.x + largoPersonaje > Parser::getInstancia().getEscenario().getAncho())
		// se toma el ancho del sensor, como parametro
		posicion.x = Parser::getInstancia().getEscenario().getAncho() - largoPersonaje;
}


Personaje* Cuerpo::getRefPersonaje(){
	return observador;
}

void Cuerpo::sumarPosicion(const vector2D& unaPosicion)
{
	posicion += unaPosicion;

	// Que no se mueva debajo del piso
	if (estaEnPiso() && unaPosicion.y < yPiso) {
		posicion.y = yPiso;
		velocidad.x = 0.0f;
		velocidad.y = 0.0f;
	}

	// que no se mueva más allá de los límites del escenario
	limitarAEscenario();

}

void Cuerpo::mover(float unaDistancia)
{
	if (!(this->EstaFrenado()))
		posicion.x += unaDistancia;
}


void Cuerpo::recibeObservador(Personaje* unObservador)
{
	observador = unObservador;
}

int Cuerpo::notificarObservadores(ESTADO nuevoEstado)
{
	if (nuevoEstado.golpeado == FALLECIDO)
		return REINICIAR;
	observador->actualizar(posicion.x, posicion.y, nuevoEstado);
		return CONTINUAR;
}

Sprite* Cuerpo::getSprite() const
{
	return observador->getSprite();
}
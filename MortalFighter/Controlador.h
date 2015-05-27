#pragma once
#include "Constantes.h"
#include "ConversorDeEventos.h"
#include "ControladorDeTomas.h"

class Controlador
{
public:
	Controlador();
	
	~Controlador();
	int cambiar();
	std::vector<MOV_TIPO> getMovimientos();
	ConversorDeEventos* getConversorDeEventos();
	void setConversorDeEventos(ConversorDeEventos* unConversorDeEventos);
	MOV_TIPO getUltimoMovimientoActivo();
	ControladorDeTomas* getControladorDeTomas();

private:
	int j;
	std::vector<MOV_TIPO> movimientos;
	std::vector<MOV_TIPO> movimientosActivos;
	ConversorDeEventos* conversorDeEventos;
	SDL_Event event;
	const Uint8 *state;
	SDL_Keycode keyCode;
	SDL_JoystickID numeroDeJoystick;
	Uint8 jBoton;
	SDL_Joystick* unJoystick;
	SDL_Joystick* otroJoystick;
	Sint16 valorDelEje;
	int cantidadDeEventosAnterior;
	int otraCantidadDeEventosAnterior;
	ControladorDeTomas* controladorDeTomas;
	bool golpeBajoTecladoHabilitado;
	bool golpeAltoTecladoHabilitado;
	bool patadaBajaTecladoHabilitada;
	bool patadaAltaTecladoHabilitada;

	void mantenerMovimientos();
	void mantenerMovimientosActivos();
	
};


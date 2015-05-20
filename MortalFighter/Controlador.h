#pragma once
#include "Constantes.h"
#include "ConversorDeEventos.h"


enum MOV_TIPO { ARRIBA, ABAJO, DER, IZQ, DEFENSA, G_BAJO, G_ALTO, P_BAJA, P_ALTA, ARMA, CERRAR, RECARGAR, SALTOIZQ, SALTODER, DEFENSA_AGACHADO, G_ABAJO, G_GANCHO, G_SALTO, G_SALTOIZQ, G_SALTODER, P_BAJA_ABAJO, P_ALTA_ABAJO, P_SALTO, P_SALTOIZQ, P_SALTODER, QUIETO, FATALITY };


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
	bool tieneCombinacionDeFatalityParaLaOrientacion();

private:
	int j;
	std::vector<MOV_TIPO> movimientosParaFatality;
	std::vector<MOV_TIPO> movimientos;
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

	void mantenerMovimientos();
	
};


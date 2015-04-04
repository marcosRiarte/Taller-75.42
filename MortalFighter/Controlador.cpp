#include "stdafx.h"
#include "Controlador.h"


Controlador::Controlador()
{
}

MOV_TIPO Controlador::cambiar(){
	SDL_Event event;
	SDL_PollEvent(&event);
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			return CERRAR;
		case SDLK_UP:
			if ((state[SDL_SCANCODE_RIGHT]))
				return SALTODER;
			if ((state[SDL_SCANCODE_LEFT]))
				return SALTOIZQ;
			return ARRIBA;
		case SDLK_DOWN:
			return ABAJO;
		case SDLK_RIGHT:
			return DER;
		case SDLK_LEFT:
			return IZQ;

		default:
			return QUIETO;
		}
	}

	return QUIETO;
	//TODO: Hacer la salida
}

Controlador::~Controlador()
{
}

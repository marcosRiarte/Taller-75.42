#include "stdafx.h"
#include "Controlador.h"


Controlador::Controlador()
{
}

MOV_TIPO Controlador::cambiar(){
	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT) {
		return CERRAR;
	}

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
			if (state[SDL_SCANCODE_UP]) return ARRIBA;
			return ABAJO;
		case SDLK_RIGHT:
			if (state[SDL_SCANCODE_LEFT]) return IZQ;
			return DER;
		case SDLK_LEFT:
			return IZQ;
		case SDLK_r:
			return RECARGAR;
		}
	}

	if (state[SDL_SCANCODE_RIGHT]){
		if (state[SDL_SCANCODE_LEFT]) return QUIETO;
		return DER;
	}

	if (state[SDL_SCANCODE_LEFT]){
		if (state[SDL_SCANCODE_RIGHT]) return QUIETO;
		return IZQ;
	}

	if (state[SDL_SCANCODE_LEFT]){
		return IZQ;
	}

	if (state[SDL_SCANCODE_DOWN]){
		if ((state[SDL_SCANCODE_RIGHT]) || (state[SDL_SCANCODE_LEFT])) return ABAJO;
		if (state[SDL_SCANCODE_UP]) return ARRIBA;
		return ABAJO;
	}

	return QUIETO;
}

Controlador::~Controlador()
{
}
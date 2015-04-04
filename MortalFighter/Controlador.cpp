#include "stdafx.h"
#include "Controlador.h"


Controlador::Controlador()
{
}

MOV_TIPO Controlador::cambiar(){
	SDL_Event event;
	SDL_PollEvent(&event);
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	
	if (event.key.keysym.sym == SDLK_RIGHT){
		return DER;
	}
	if (event.key.keysym.sym == SDLK_LEFT){
		return IZQ;
	}
	if (event.key.keysym.sym == SDLK_UP){
		return ARRIBA;
	}
	if ((state[SDL_SCANCODE_LEFT]) && (event.key.keysym.sym == SDLK_UP)){
		return SALTOIZQ;
	}
	if ((state[SDL_SCANCODE_RIGHT]) && (event.key.keysym.sym == SDLK_UP)){
		return SALTODER;
	}

	if (event.key.keysym.sym == SDLK_q){
		return CERRAR;
	}

	//TODO: Hacer la salida
}

Controlador::~Controlador()
{
}

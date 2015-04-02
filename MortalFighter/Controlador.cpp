#include "stdafx.h"
#include "Controlador.h"


Controlador::Controlador()
{
}

Controlador::MOV_TIPO Controlador::cambiar(){
	SDL_Event event;
	SDL_PollEvent(&event);
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (event.key.keysym.sym == SDLK_LEFT){
		return MOV_TIPO::IZQ;
	}
	if (event.key.keysym.sym == SDLK_RIGHT){
		return MOV_TIPO::DER;
	}
	if (event.key.keysym.sym == SDLK_UP){
		return MOV_TIPO::ARRIBA;
	}
	if ((state[SDL_SCANCODE_LEFT]) && (event.key.keysym.sym == SDLK_UP)){
		return MOV_TIPO::SALTOIZQ;
	}
	if ((state[SDL_SCANCODE_RIGHT]) && (event.key.keysym.sym == SDLK_UP)){
		return MOV_TIPO::SALTODER;
	}
}

Controlador::~Controlador()
{
}

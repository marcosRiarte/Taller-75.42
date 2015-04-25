#include "stdafx.h"
#include "Controlador.h"

Controlador::Controlador()
{
	movimientos = std::vector<MOV_TIPO>();
}

int Controlador::cambiar(){

	SDL_Event event;
	SDL_PollEvent(&event);
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (event.type == SDL_QUIT) {
		return FIN;
	}
	
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			return FIN;
		case SDLK_UP:
			if (state[SDL_SCANCODE_RIGHT]){
				movimientos.clear();
				movimientos.push_back(SALTODER);
				return CONTINUAR;
			}
			if (state[SDL_SCANCODE_LEFT]){
				movimientos.clear();
				movimientos.push_back(SALTOIZQ);
			return CONTINUAR;
			}
			movimientos.clear();
			movimientos.push_back(ARRIBA);
			return CONTINUAR;
		case SDLK_DOWN:
			if (state[SDL_SCANCODE_UP]){
			movimientos.clear();
			movimientos.push_back(ARRIBA);
			return CONTINUAR;
			} else if(state[SDL_SCANCODE_LEFT]){
				movimientos.clear();
				movimientos.push_back(IZQ);
				return CONTINUAR;
			}
			else if (state[SDL_SCANCODE_RIGHT]){
				movimientos.clear();
				movimientos.push_back(DER);
				return CONTINUAR;
			}
			else{
			movimientos.clear();
			movimientos.push_back(ABAJO);
			return CONTINUAR;
			}
		case SDLK_RIGHT:
			if (state[SDL_SCANCODE_LEFT]){
				movimientos.clear();
				movimientos.push_back(IZQ);
			return CONTINUAR;
			}
			else{
				movimientos.clear();
				movimientos.push_back(DER);
			return CONTINUAR;
			}
		case SDLK_LEFT:
			if (state[SDL_SCANCODE_RIGHT]){
				movimientos.clear();
				movimientos.push_back(DER);
				return CONTINUAR;
			}
			else{
				movimientos.clear();
				movimientos.push_back(IZQ);
				return CONTINUAR;
			}
		case SDLK_r:
			return REINICIAR;
		}
	}
	
	if ((state[SDL_SCANCODE_LEFT]) && (state[SDL_SCANCODE_RIGHT]))
		if ((movimientos.at(0) == DER) || (movimientos.at(0) == IZQ))
		return CONTINUAR;
		
	if (state[SDL_SCANCODE_RIGHT]){
		movimientos.clear();
		movimientos.push_back(DER);
		return CONTINUAR;
	}

	if (state[SDL_SCANCODE_LEFT]){
		movimientos.clear();
		movimientos.push_back(IZQ);
		return CONTINUAR;
	}
	
	if ((state[SDL_SCANCODE_DOWN]) && (state[SDL_SCANCODE_UP])){
		movimientos.clear();
		movimientos.push_back(ARRIBA);
			return CONTINUAR;
	}

	if ((state[SDL_SCANCODE_DOWN]) && ((state[SDL_SCANCODE_RIGHT]))){
		movimientos.clear();
		movimientos.push_back(DER);
		return CONTINUAR;
	}

	if ((state[SDL_SCANCODE_DOWN]) && ((state[SDL_SCANCODE_LEFT]))){
		movimientos.clear();
		movimientos.push_back(IZQ);
		return CONTINUAR;
	}

	
	movimientos.clear();
	movimientos.push_back(QUIETO);

	return CONTINUAR;
}


std::vector<MOV_TIPO> Controlador::getMovimientos(){
	return movimientos;
}


Controlador::~Controlador()
{
}
#include "stdafx.h"
#include "Controlador.h"

Controlador::Controlador()
{
}

int Controlador::cambiar(std::vector<MOV_TIPO>* movimientos){

	movimientos->clear();

	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT) {
		return FIN;
	}

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			return FIN;
		case SDLK_UP:
			if (state[SDL_SCANCODE_RIGHT]){
				movimientos->push_back(SALTODER);
				return CONTINUAR;
			}
			if (state[SDL_SCANCODE_LEFT]){
				movimientos->push_back(SALTOIZQ);
			return CONTINUAR;
			}
			movimientos->push_back(ARRIBA);
			return CONTINUAR;
		case SDLK_DOWN:
			if (state[SDL_SCANCODE_UP])
			movimientos->push_back(ARRIBA);
			movimientos->push_back(ABAJO);
			return CONTINUAR;
		case SDLK_RIGHT:
			if (state[SDL_SCANCODE_LEFT])
			movimientos->push_back(IZQ);
			movimientos->push_back(DER);
			return CONTINUAR;
		case SDLK_LEFT:
			movimientos->push_back(IZQ);
			return CONTINUAR;
		case SDLK_r:
			return REINICIAR;
		}
	}

	if (state[SDL_SCANCODE_RIGHT]){
		if (state[SDL_SCANCODE_LEFT])
			movimientos->push_back(QUIETO);
		movimientos->push_back(DER);
		return CONTINUAR;
	}

	if (state[SDL_SCANCODE_LEFT]){
		if (state[SDL_SCANCODE_RIGHT]) 
			movimientos->push_back(QUIETO);
		movimientos->push_back(IZQ);
		return CONTINUAR;
	}

	if (state[SDL_SCANCODE_LEFT]){
		movimientos->push_back(IZQ);
		return CONTINUAR;
	}

	if (state[SDL_SCANCODE_DOWN]){
		if ((state[SDL_SCANCODE_RIGHT]) || (state[SDL_SCANCODE_LEFT]))
			movimientos->push_back(ABAJO);
		return CONTINUAR;
		if (state[SDL_SCANCODE_UP]) 
			movimientos->push_back(ARRIBA);
			movimientos->push_back(ABAJO);
		return CONTINUAR;
	}
	movimientos->push_back(QUIETO);
	return CONTINUAR;
}

Controlador::~Controlador()
{
}
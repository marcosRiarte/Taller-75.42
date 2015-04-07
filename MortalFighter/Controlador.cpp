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
			//ESTA PORQUERIA HACE QUE NO SE MUEVA SI APRETAS DOS COSAS A LA VEZ. 
			//ES UN ESPANTO Y ESTA MAL PERO NO LE ENCONTRE LA VUELTA PARA HACERLO DE OTRA FORMA.
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

	case SDL_QUIT:
		return CERRAR;
	}

	//TODA ESTA MIERDA QUE SIGUE ES LA QUE HACE QUE EL PERSONAJE SE MUEVA RAPIDO CUANDO DEJAS APRETADA ALGUNA TECLA.
	//SI NO SIRVE SE COMENTA Y CHAU.
	//PERO DE ESTA FORMA SI TENES PULSADA ALGUNA TECLA DESPUES DE SALTAR POR EJEMPLO SE SIGUE MOVIENDO.
	if (state[SDL_SCANCODE_RIGHT]){
		if (state[SDL_SCANCODE_LEFT]) return IZQ;
		return DER;
	}

	if (state[SDL_SCANCODE_LEFT]){
		return IZQ;
	}

	if (state[SDL_SCANCODE_UP]){
		if ((state[SDL_SCANCODE_RIGHT]) || (state[SDL_SCANCODE_LEFT]) || (state[SDL_SCANCODE_DOWN])) return QUIETO;
		return ARRIBA;
	}

	if (state[SDL_SCANCODE_DOWN]){
		if ((state[SDL_SCANCODE_RIGHT]) || (state[SDL_SCANCODE_LEFT])) return ABAJO;
		if (state[SDL_SCANCODE_UP]) return ARRIBA;
		return ABAJO;
	}
			
	return QUIETO;
	//TODO: Hacer la salida
}

Controlador::~Controlador()
{
}

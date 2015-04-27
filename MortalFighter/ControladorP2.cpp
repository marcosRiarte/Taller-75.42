#include "stdafx.h"
#include "ControladorP2.h"


ControladorP2::ControladorP2()
{
	movimientos = std::vector<MOV_TIPO>();
}



int ControladorP2::cambiar(){

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
		case SDLK_w:
			if (state[SDL_SCANCODE_J]){
				movimientos.clear();
				movimientos.push_back(DEFENSA);
				return CONTINUAR;
			}
			if (state[SDL_SCANCODE_D]){
				movimientos.clear();
				movimientos.push_back(SALTODER);
				return CONTINUAR;
			}
			if (state[SDL_SCANCODE_A]){
				movimientos.clear();
				movimientos.push_back(SALTOIZQ);
				return CONTINUAR;
			}
			movimientos.clear();
			movimientos.push_back(ARRIBA);
			return CONTINUAR;
		case SDLK_s:
			if (state[SDL_SCANCODE_J]){
				movimientos.clear();
				movimientos.push_back(DEFENSA);
				return CONTINUAR;
			}
			if (state[SDL_SCANCODE_W]){
				movimientos.clear();
				movimientos.push_back(ARRIBA);
				return CONTINUAR;
			}
			else if (state[SDL_SCANCODE_D]){
				movimientos.clear();
				movimientos.push_back(IZQ);
				return CONTINUAR;
			}
			else if (state[SDL_SCANCODE_A]){
				movimientos.clear();
				movimientos.push_back(DER);
				return CONTINUAR;
			}
			else{
				movimientos.clear();
				movimientos.push_back(ABAJO);
				return CONTINUAR;
			}
		case SDLK_d:
			if (state[SDL_SCANCODE_J]){
				movimientos.clear();
				movimientos.push_back(DEFENSA);
				return CONTINUAR;
			}
			if (state[SDL_SCANCODE_A]){
				movimientos.clear();
				movimientos.push_back(IZQ);
				return CONTINUAR;
			}
			else{
				movimientos.clear();
				movimientos.push_back(DER);
				return CONTINUAR;
			}
		case SDLK_a:
			if (state[SDL_SCANCODE_J]){
				movimientos.clear();
				movimientos.push_back(DEFENSA);
				return CONTINUAR;
			}
			if (state[SDL_SCANCODE_D]){
				movimientos.clear();
				movimientos.push_back(DER);
				return CONTINUAR;
			}
			else{
				movimientos.clear();
				movimientos.push_back(IZQ);
				return CONTINUAR;
			}
		case SDLK_k:
			if (movimientos.at(0) == ARRIBA){
				movimientos.clear();
				movimientos.push_back(G_SALTO);
				return CONTINUAR;
			}
			if (movimientos.at(0) == SALTODER){
				movimientos.clear();
				movimientos.push_back(G_SALTODER);
				return CONTINUAR;
			}
			if (movimientos.at(0) == SALTOIZQ){
				movimientos.clear();
				movimientos.push_back(G_SALTOIZQ);
				return CONTINUAR;
			}
			if (movimientos.at(0) == ABAJO){
				movimientos.clear();
				movimientos.push_back(G_ABAJO);
				return CONTINUAR;
			}
			movimientos.clear();
			movimientos.push_back(G_BAJO);
			return CONTINUAR;
		case SDLK_l:
			if (movimientos.at(0) == ARRIBA){
				movimientos.clear();
				movimientos.push_back(G_SALTO);
				return CONTINUAR;
			}
			if (movimientos.at(0) == SALTODER){
				movimientos.clear();
				movimientos.push_back(G_SALTODER);
				return CONTINUAR;
			}
			if (movimientos.at(0) == SALTOIZQ){
				movimientos.clear();
				movimientos.push_back(G_SALTOIZQ);
				return CONTINUAR;
			}
			if (movimientos.at(0) == ABAJO){
				movimientos.clear();
				movimientos.push_back(G_GANCHO);
				return CONTINUAR;
			}
			movimientos.clear();
			movimientos.push_back(G_ALTO);
			return CONTINUAR;
		case SDLK_i:
			if (movimientos.at(0) == ARRIBA){
				movimientos.clear();
				movimientos.push_back(P_SALTO);
				return CONTINUAR;
			}
			if (movimientos.at(0) == SALTODER){
				movimientos.clear();
				movimientos.push_back(P_SALTODER);
				return CONTINUAR;
			}
			if (movimientos.at(0) == SALTOIZQ){
				movimientos.clear();
				movimientos.push_back(P_SALTOIZQ);
				return CONTINUAR;
			}
			if (movimientos.at(0) == ABAJO){
				movimientos.clear();
				movimientos.push_back(P_BAJA_ABAJO);
				return CONTINUAR;
			}
			movimientos.clear();
			movimientos.push_back(P_BAJA);
			return CONTINUAR;
		case SDLK_o:
			if (movimientos.at(0) == ARRIBA){
				movimientos.clear();
				movimientos.push_back(P_SALTO);
				return CONTINUAR;
			}
			if (movimientos.at(0) == SALTODER){
				movimientos.clear();
				movimientos.push_back(P_SALTODER);
				return CONTINUAR;
			}
			if (movimientos.at(0) == SALTOIZQ){
				movimientos.clear();
				movimientos.push_back(P_SALTOIZQ);
				return CONTINUAR;
			}
			if (movimientos.at(0) == ABAJO){
				movimientos.clear();
				movimientos.push_back(P_ALTA_ABAJO);
				return CONTINUAR;
			}
			movimientos.clear();
			movimientos.push_back(P_ALTA);
			return CONTINUAR;
		case SDLK_u:
			movimientos.clear();
			movimientos.push_back(ARMA);
			return CONTINUAR;
		case SDLK_j:
			movimientos.clear();
			movimientos.push_back(DEFENSA);
			return CONTINUAR;
		case SDLK_r:
			return REINICIAR;
		}
	}

	if (state[SDL_SCANCODE_J]){
		movimientos.clear();
		movimientos.push_back(DEFENSA);
		return CONTINUAR;
	}

	if ((state[SDL_SCANCODE_A]) && (state[SDL_SCANCODE_D]))
		if ((movimientos.at(0) == DER) || (movimientos.at(0) == IZQ))
			return CONTINUAR;

	if (state[SDL_SCANCODE_D]){
		movimientos.clear();
		movimientos.push_back(DER);
		return CONTINUAR;
	}

	if (state[SDL_SCANCODE_A]){
		movimientos.clear();
		movimientos.push_back(IZQ);
		return CONTINUAR;
	}

	if (state[SDL_SCANCODE_S]){
		movimientos.clear();
		movimientos.push_back(ABAJO);
		return CONTINUAR;
	}


	movimientos.clear();
	movimientos.push_back(QUIETO);

	return CONTINUAR;
}


ControladorP2::~ControladorP2()
{
	movimientos.clear();
}

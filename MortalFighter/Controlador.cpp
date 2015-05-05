#include "stdafx.h"
#include "Controlador.h"

Controlador::Controlador()
{
	movimientos = std::vector<MOV_TIPO>();
}


void Controlador::setConversorDeEventos(ConversorDeEventos* unConversorDeEventos){
	conversorDeEventos = unConversorDeEventos;
}


std::vector<MOV_TIPO> Controlador::getMovimientos(){
	return movimientos;
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
		SDL_Keycode keyCode = (event.key.keysym.sym);
		{
			if (keyCode == conversorDeEventos->getKeyCodeDeLaAccion(ConversorDeEventos::QUIT)) return FIN;

			if (keyCode == conversorDeEventos->getKeyCodeDeLaAccion(ConversorDeEventos::UP)){
				if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::HOLD)]){
					movimientos.clear();
					movimientos.push_back(DEFENSA);
					return CONTINUAR;
				}
				if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::RIGHT)]){
					movimientos.clear();
					movimientos.push_back(SALTODER);
					return CONTINUAR;
				}
				if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::LEFT)]){
					movimientos.clear();
					movimientos.push_back(SALTOIZQ);
					return CONTINUAR;
				}
				movimientos.clear();
				movimientos.push_back(ARRIBA);
				return CONTINUAR;
			}

			if (keyCode == conversorDeEventos->getKeyCodeDeLaAccion(ConversorDeEventos::DOWN)){
				if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::HOLD)]){
					movimientos.push_back(DEFENSA);
					return CONTINUAR;
				}
				if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::UP)]){
					movimientos.clear();
					movimientos.push_back(ARRIBA);
					return CONTINUAR;
				}
				else if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::LEFT)]){
					movimientos.clear();
					movimientos.push_back(IZQ);
					return CONTINUAR;
				}
				else if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::RIGHT)]){
					movimientos.clear();
					movimientos.push_back(DER);
					return CONTINUAR;
				}
				else{
					movimientos.clear();
					movimientos.push_back(ABAJO);
					return CONTINUAR;
				}
			}
			
			if (keyCode == conversorDeEventos->getKeyCodeDeLaAccion(ConversorDeEventos::RIGHT)){
				if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::HOLD)]){
					movimientos.clear();
					movimientos.push_back(DEFENSA);
					return CONTINUAR;
				}
				if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::LEFT)]){
					movimientos.clear();
					movimientos.push_back(IZQ);
					return CONTINUAR;
				}
				else{
					movimientos.clear();
					movimientos.push_back(DER);
					return CONTINUAR;
				}
			}

			if (keyCode == conversorDeEventos->getKeyCodeDeLaAccion(ConversorDeEventos::LEFT)){
				if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::HOLD)]){
					movimientos.clear();
					movimientos.push_back(DEFENSA);
					return CONTINUAR;
				}
				if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::RIGHT)]){
					movimientos.clear();
					movimientos.push_back(DER);
					return CONTINUAR;
				}
				else{
					movimientos.clear();
					movimientos.push_back(IZQ);
					return CONTINUAR;
				}
			}

			if (keyCode == conversorDeEventos->getKeyCodeDeLaAccion(ConversorDeEventos::LOW_PUNCH)){
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
			}
			
			if (keyCode == conversorDeEventos->getKeyCodeDeLaAccion(ConversorDeEventos::HIGH_PUNCH)){
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
			}
			
			if (keyCode == conversorDeEventos->getKeyCodeDeLaAccion(ConversorDeEventos::LOW_KICK)){
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
			}
			
			if (keyCode == conversorDeEventos->getKeyCodeDeLaAccion(ConversorDeEventos::HIGH_KICK)){
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
			}
			
			if (keyCode == conversorDeEventos->getKeyCodeDeLaAccion(ConversorDeEventos::WEAPON)){
				movimientos.clear();
				movimientos.push_back(ARMA);
				return CONTINUAR;
			}

			if (keyCode == conversorDeEventos->getKeyCodeDeLaAccion(ConversorDeEventos::HOLD)){
				movimientos.clear();
				if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::DOWN)]){
					movimientos.push_back(DEFENSA_AGACHADO);
					return CONTINUAR;
				}
				movimientos.push_back(DEFENSA);
				return CONTINUAR;
			}

			if (keyCode == conversorDeEventos->getKeyCodeDeLaAccion(ConversorDeEventos::REBOOT)) return REINICIAR;
		}
	}

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::HOLD)]){
		if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::DOWN)]){
			if (movimientos.at(0) == ABAJO || movimientos.at(0) == DEFENSA_AGACHADO){
				movimientos.clear();
				movimientos.push_back(DEFENSA_AGACHADO);
				return CONTINUAR;
			}
		}
		movimientos.clear();
		movimientos.push_back(DEFENSA);
		return CONTINUAR;
	}

	if ((state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::LEFT)]) && (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::RIGHT)]))
		if ((movimientos.at(0) == DER) || (movimientos.at(0) == IZQ))
			return CONTINUAR;

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::RIGHT)]){
		movimientos.clear();
		movimientos.push_back(DER);
		return CONTINUAR;
	}

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::LEFT)]){
		movimientos.clear();
		movimientos.push_back(IZQ);
		return CONTINUAR;
	}

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::DOWN)]){
		movimientos.clear();
		movimientos.push_back(ABAJO);
		return CONTINUAR;
	}

	movimientos.clear();
	movimientos.push_back(QUIETO);

	return CONTINUAR;
}


Controlador::~Controlador()
{
	movimientos.clear();
}
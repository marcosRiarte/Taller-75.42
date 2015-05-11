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

	//TECLADO
	SDL_Event event;
	SDL_PollEvent(&event);
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (event.type == SDL_QUIT) {
		return FIN;
	}

	SDL_Keycode keyCode = (event.key.keysym.sym);
	SDL_JoystickID numeroDeJoystick = (event.jbutton.which);
	Uint8 jBoton = (event.jbutton.button);

	switch (event.type)
	{
	case SDL_KEYDOWN:
			
			if (keyCode == conversorDeEventos->getKeyCodeDeLaAccion(ConversorDeEventos::QUIT)) return FIN;

			if (keyCode == conversorDeEventos->getKeyCodeDeLaAccion(ConversorDeEventos::UP)){
				if (movimientos.at(0) == DEFENSA){
					movimientos.clear();
					movimientos.push_back(DEFENSA);
					return CONTINUAR;
				}
				if (movimientos.at(0) == ABAJO){
					movimientos.clear();
					movimientos.push_back(ABAJO);
					return CONTINUAR;
				}
				if (movimientos.at(0) == DEFENSA_AGACHADO){
					movimientos.clear();
					movimientos.push_back(DEFENSA_AGACHADO);
					return CONTINUAR;
				}
				if (movimientos.at(0) == DER){
					movimientos.clear();
					movimientos.push_back(SALTODER);
					return CONTINUAR;
				}
				if (movimientos.at(0) == IZQ){
					movimientos.clear();
					movimientos.push_back(SALTOIZQ);
					return CONTINUAR;
				}
				movimientos.clear();
				movimientos.push_back(ARRIBA);
				return CONTINUAR;
			}

			if (keyCode == conversorDeEventos->getKeyCodeDeLaAccion(ConversorDeEventos::DOWN)){
				if (movimientos.at(0) == DEFENSA){
					movimientos.push_back(DEFENSA_AGACHADO);
					return CONTINUAR;
				}

				else{
					movimientos.clear();
					movimientos.push_back(ABAJO);
					return CONTINUAR;
				}
			}
			
			if (keyCode == conversorDeEventos->getKeyCodeDeLaAccion(ConversorDeEventos::RIGHT)){
				if (movimientos.at(0) == DEFENSA){
					movimientos.clear();
					movimientos.push_back(DEFENSA);
					return CONTINUAR;
				}
				if (movimientos.at(0) == ABAJO){
					movimientos.clear();
					movimientos.push_back(ABAJO);
					return CONTINUAR;
				}
				if (movimientos.at(0) == DEFENSA_AGACHADO){
					movimientos.clear();
					movimientos.push_back(DEFENSA_AGACHADO);
					return CONTINUAR;
				}
				if (movimientos.at(0) == IZQ){
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
				if (movimientos.at(0) == DEFENSA){
					movimientos.clear();
					movimientos.push_back(DEFENSA);
					return CONTINUAR;
				}
				if (movimientos.at(0) == DEFENSA_AGACHADO){
					movimientos.clear();
					movimientos.push_back(DEFENSA_AGACHADO);
					return CONTINUAR;
				}
				if (movimientos.at(0) == ABAJO){
					movimientos.clear();
					movimientos.push_back(ABAJO);
					return CONTINUAR;
				}
				if (movimientos.at(0) == DER){
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
				if (movimientos.at(0) == ABAJO){
					movimientos.push_back(DEFENSA_AGACHADO);
					return CONTINUAR;
				}
				movimientos.push_back(DEFENSA);
				return CONTINUAR;
			}

			if (keyCode == conversorDeEventos->getKeyCodeDeLaAccion(ConversorDeEventos::REBOOT)) return REINICIAR;

		case SDL_JOYBUTTONDOWN:

			if ( (jBoton == conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::QUIT)) && (numeroDeJoystick == conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::QUIT)) ) return FIN;

			if ( (jBoton == conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::REBOOT)) && (numeroDeJoystick == conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::REBOOT)) ) return REINICIAR;

			if ( (jBoton == conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::WEAPON)) && (numeroDeJoystick == conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::WEAPON)) ){
				movimientos.clear();
				movimientos.push_back(ARMA);
				return CONTINUAR;
			}

			if ( (jBoton == conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LOW_PUNCH)) && (numeroDeJoystick == conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LOW_PUNCH)) ){
				if (movimientos.at(0) == ABAJO){
					movimientos.clear();
					movimientos.push_back(G_ABAJO);
					return CONTINUAR;
				}
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
				movimientos.clear();
				movimientos.push_back(G_BAJO);
				return CONTINUAR;
			}

			if ((jBoton == conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::HIGH_PUNCH)) && (numeroDeJoystick == conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::HIGH_PUNCH))){
				if (movimientos.at(0) == ABAJO){
					movimientos.clear();
					movimientos.push_back(G_GANCHO);
					return CONTINUAR;
				}
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
				movimientos.clear();
				movimientos.push_back(G_ALTO);
				return CONTINUAR;
			}

			if ((jBoton == conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LOW_KICK)) && (numeroDeJoystick == conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LOW_KICK))){
				if (movimientos.at(0) == ABAJO){
					movimientos.clear();
					movimientos.push_back(P_BAJA_ABAJO);
					return CONTINUAR;
				}
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
				movimientos.clear();
				movimientos.push_back(P_BAJA);
				return CONTINUAR;
			}

			if ((jBoton == conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::HIGH_KICK)) && (numeroDeJoystick == conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::HIGH_KICK))){
				if (movimientos.at(0) == ABAJO){
					movimientos.clear();
					movimientos.push_back(P_ALTA_ABAJO);
					return CONTINUAR;
				}
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
				movimientos.clear();
				movimientos.push_back(P_ALTA);
				return CONTINUAR;
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

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::DOWN)]){
		movimientos.clear();
		movimientos.push_back(ABAJO);
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

	//JOYSTICK
	SDL_JoystickUpdate();
	SDL_Joystick* unJoystick;
	Sint16 valorDelEje;

	unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::HOLD));
	if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::HOLD)){
		valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::HOLD));
		if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::HOLD)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::HOLD))){
			movimientos.clear();
			movimientos.push_back(DEFENSA);
			return CONTINUAR;
		}
	}
	else{
		if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::HOLD)) == 1){
			movimientos.clear();
			movimientos.push_back(DEFENSA);
			return CONTINUAR;
		}
		if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::HOLD)){
			if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::HOLD) == SDL_JoystickGetHat(unJoystick, 0)){
				movimientos.clear();
				movimientos.push_back(DEFENSA);
				return CONTINUAR;
			}
		}
	}

	unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::UP));
	if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::UP)){
		valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::UP));
		if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::UP)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::UP))){
			unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT));
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::RIGHT)){
				valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::RIGHT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::RIGHT))){
					movimientos.clear();
					movimientos.push_back(SALTODER);
					return CONTINUAR;
				}
			}
			else{
				unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT));
				if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT)) == 1){
					movimientos.clear();
					movimientos.push_back(SALTODER);
					return CONTINUAR;
				}
				unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT));
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::RIGHT)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_JoystickGetHat(unJoystick, 0)){
						movimientos.clear();
						movimientos.push_back(SALTODER);
						return CONTINUAR;
					}
				}
			}
			unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LEFT));
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LEFT)){
				valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LEFT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::LEFT))){
					movimientos.clear();
					movimientos.push_back(SALTOIZQ);
					return CONTINUAR;
				}
			}
			else{
				unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LEFT));
				if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT)) == 1){
					movimientos.clear();
					movimientos.push_back(SALTOIZQ);
					return CONTINUAR;
				}
				unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LEFT));
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::LEFT)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_JoystickGetHat(unJoystick, 0)){
						movimientos.clear();
						movimientos.push_back(SALTOIZQ);
						return CONTINUAR;
					}
				}
			}
			movimientos.clear();
			movimientos.push_back(ARRIBA);
			return CONTINUAR;
		}
	}
	else{
		unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::UP));
		if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::UP)) == 1){
			unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT));
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::RIGHT)){
				valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::RIGHT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::RIGHT))){
					movimientos.clear();
					movimientos.push_back(SALTODER);
					return CONTINUAR;
				}
			}
			else{
				unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT));
				if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT)) == 1){
					movimientos.clear();
					movimientos.push_back(SALTODER);
					return CONTINUAR;
				}
				unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT));
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::RIGHT)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_JoystickGetHat(unJoystick, 0)){
						movimientos.clear();
						movimientos.push_back(SALTODER);
						return CONTINUAR;
					}
				}
			}
			unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LEFT));
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LEFT)){
				valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LEFT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::LEFT))){
					movimientos.clear();
					movimientos.push_back(SALTOIZQ);
					return CONTINUAR;
				}
			}
			else{
				unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LEFT));
				if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT)) == 1){
					movimientos.clear();
					movimientos.push_back(SALTOIZQ);
					return CONTINUAR;
				}
				unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LEFT));
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::LEFT)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_JoystickGetHat(unJoystick, 0)){
						movimientos.clear();
						movimientos.push_back(SALTOIZQ);
						return CONTINUAR;
					}
				}
			}
			movimientos.clear();
			movimientos.push_back(ARRIBA);
			return CONTINUAR;
		}

		if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::UP) && conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::RIGHT)){
			if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::UP) == conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT)){
				unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::UP));
				if (SDL_JoystickGetHat(unJoystick, 0) == SDL_HAT_RIGHTUP){
					if (((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_UP) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_HAT_RIGHT)) || ((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_RIGHT) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_HAT_UP))){
						movimientos.clear();
						movimientos.push_back(SALTODER);
						return CONTINUAR;
					}
					if (((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_UP) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_HAT_LEFT)) || ((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_LEFT) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_HAT_UP))){
						movimientos.clear();
						movimientos.push_back(SALTOIZQ);
						return CONTINUAR;
					}
				}
				if (SDL_JoystickGetHat(unJoystick, 0) == SDL_HAT_LEFTUP){
					if (((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_UP) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_HAT_RIGHT)) || ((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_RIGHT) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_HAT_UP))){
						movimientos.clear();
						movimientos.push_back(SALTODER);
						return CONTINUAR;
					}
					if (((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_UP) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_HAT_LEFT)) || ((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_LEFT) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_HAT_UP))){
						movimientos.clear();
						movimientos.push_back(SALTOIZQ);
						return CONTINUAR;
					}
				}
				if (SDL_JoystickGetHat(unJoystick, 0) == SDL_HAT_RIGHTDOWN){
					if (((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_DOWN) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_HAT_RIGHT)) || ((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_RIGHT) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_HAT_DOWN))){
						movimientos.clear();
						movimientos.push_back(SALTODER);
						return CONTINUAR;
					}
					if (((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_DOWN) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_HAT_LEFT)) || ((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_LEFT) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_HAT_DOWN))){
						movimientos.clear();
						movimientos.push_back(SALTOIZQ);
						return CONTINUAR;
					}
				}
				if (SDL_JoystickGetHat(unJoystick, 0) == SDL_HAT_LEFTDOWN){
					if (((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_DOWN) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_HAT_RIGHT)) || ((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_RIGHT) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_HAT_DOWN))){
						movimientos.clear();
						movimientos.push_back(SALTODER);
						return CONTINUAR;
					}
					if (((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_DOWN) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_HAT_LEFT)) || ((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_LEFT) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_HAT_DOWN))){
						movimientos.clear();
						movimientos.push_back(SALTOIZQ);
						return CONTINUAR;
					}
				}
			}
		}

		unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::UP));
		if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::UP)){
			if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_JoystickGetHat(unJoystick, 0)){
				unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT));
				if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::RIGHT)){
					valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT));
					if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::RIGHT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::RIGHT))){
						movimientos.clear();
						movimientos.push_back(SALTODER);
						return CONTINUAR;
					}
				}
				else{
					unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT));
					if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT)) == 1){
						movimientos.clear();
						movimientos.push_back(SALTODER);
						return CONTINUAR;
					}
					unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT));
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::RIGHT)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_JoystickGetHat(unJoystick, 0)){
							movimientos.clear();
							movimientos.push_back(SALTODER);
							return CONTINUAR;
						}
					}
				}
				unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LEFT));
				if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LEFT)){
					valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT));
					if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LEFT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::LEFT))){
						movimientos.clear();
						movimientos.push_back(SALTOIZQ);
						return CONTINUAR;
					}
				}
				else{
					unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LEFT));
					if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT)) == 1){
						movimientos.clear();
						movimientos.push_back(SALTOIZQ);
						return CONTINUAR;
					}
					unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LEFT));
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::LEFT)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_JoystickGetHat(unJoystick, 0)){
							movimientos.clear();
							movimientos.push_back(SALTOIZQ);
							return CONTINUAR;
						}
					}
				}
				movimientos.clear();
				movimientos.push_back(ARRIBA);
				return CONTINUAR;
			}
		}
	}



	unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT));
	if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::RIGHT)){
		valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT));
		if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::RIGHT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::RIGHT))){
			if (movimientos.at(0) == IZQ){
				movimientos.clear();
				movimientos.push_back(IZQ);
				return CONTINUAR;
			}
			movimientos.clear();
			movimientos.push_back(DER);
			return CONTINUAR;
		}
	}
	else{
		if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT)) == 1){
			if (movimientos.at(0) == IZQ){
				movimientos.clear();
				movimientos.push_back(IZQ);
				return CONTINUAR;
			}
			movimientos.clear();
			movimientos.push_back(DER);
			return CONTINUAR;
		}
		if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::RIGHT)){
			if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_JoystickGetHat(unJoystick, 0)){
				if (movimientos.at(0) == IZQ){
					movimientos.clear();
					movimientos.push_back(IZQ);
					return CONTINUAR;
				}
				movimientos.clear();
				movimientos.push_back(DER);
				return CONTINUAR;
			}
		}
	}

	unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LEFT));
	if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LEFT)){
		valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT));
		if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LEFT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::LEFT))){
			if (movimientos.at(0) == DER){
				movimientos.clear();
				movimientos.push_back(DER);
				return CONTINUAR;
			}
			movimientos.clear();
			movimientos.push_back(IZQ);
			return CONTINUAR;
		}
	}
	else{
		if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT)) == 1){
			if (movimientos.at(0) == DER){
				movimientos.clear();
				movimientos.push_back(DER);
				return CONTINUAR;
			}
			movimientos.clear();
			movimientos.push_back(IZQ);
			return CONTINUAR;
		}
		if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::LEFT)){
			if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_JoystickGetHat(unJoystick, 0)){
				if (movimientos.at(0) == DER){
					movimientos.clear();
					movimientos.push_back(DER);
					return CONTINUAR;
				}
				movimientos.clear();
				movimientos.push_back(IZQ);
				return CONTINUAR;
			}
		}
	}

	unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::DOWN));
	if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
		valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
		if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
			movimientos.clear();
			movimientos.push_back(ABAJO);
			return CONTINUAR;
		}
	}
	else{
		if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
			movimientos.clear();
			movimientos.push_back(ABAJO);
			return CONTINUAR;
		}
		if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
			if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(unJoystick, 0)){
				movimientos.clear();
				movimientos.push_back(ABAJO);
				return CONTINUAR;
			}
		}
	}

	movimientos.clear();
	movimientos.push_back(QUIETO);

	return CONTINUAR;
}


Controlador::~Controlador()
{
	movimientos.clear();
}
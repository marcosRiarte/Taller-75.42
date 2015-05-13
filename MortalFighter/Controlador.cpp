#include "stdafx.h"
#include "Controlador.h"

Controlador::Controlador()
{
	movimientos = std::vector<MOV_TIPO>();
	if (SDL_NumJoysticks() > 0){
		unJoystick = SDL_JoystickOpen(0);
		if (SDL_NumJoysticks() > 1){
			otroJoystick = SDL_JoystickOpen(1);
		}
	}
}


void Controlador::setConversorDeEventos(ConversorDeEventos* unConversorDeEventos){
	conversorDeEventos = unConversorDeEventos;
}


std::vector<MOV_TIPO> Controlador::getMovimientos(){
	return movimientos;
}


int Controlador::cambiar(){
	SDL_JoystickUpdate();
	SDL_PumpEvents();
	state = SDL_GetKeyboardState(NULL);

	//TECLADO--------------------------------------------------------------------------
	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::QUIT)]) {
		return FIN;
	}

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::REBOOT)]) {
		return REINICIAR;
	}

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::LOW_PUNCH)]){
		if (movimientos.at(0) == G_BAJO){
			movimientos.clear();
			movimientos.push_back(QUIETO);
			return CONTINUAR;
		}
		if (movimientos.at(0) == G_ABAJO){
			movimientos.clear();
			movimientos.push_back(ABAJO);
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

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::HIGH_PUNCH)]){
		if (movimientos.at(0) == G_ALTO){
			movimientos.clear();
			movimientos.push_back(QUIETO);
			return CONTINUAR;
		}
		if (movimientos.at(0) == G_GANCHO){
			movimientos.clear();
			movimientos.push_back(ABAJO);
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

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::LOW_KICK)]){
		if (movimientos.at(0) == P_BAJA){
			movimientos.clear();
			movimientos.push_back(QUIETO);
			return CONTINUAR;
		}
		if (movimientos.at(0) == P_BAJA_ABAJO){
			movimientos.clear();
			movimientos.push_back(ABAJO);
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

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::HIGH_KICK)]){
		if (movimientos.at(0) == P_ALTA){
			movimientos.clear();
			movimientos.push_back(QUIETO);
			return CONTINUAR;
		}
		if (movimientos.at(0) == P_ALTA_ABAJO){
			movimientos.clear();
			movimientos.push_back(ABAJO);
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
	
	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::WEAPON)]){
		movimientos.clear();
		movimientos.push_back(ARMA);
		return CONTINUAR;
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
		if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::UP)]){
			movimientos.clear();
			movimientos.push_back(SALTODER);
			return CONTINUAR;
		}
		movimientos.clear();
		movimientos.push_back(DER);
		return CONTINUAR;
	}

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::LEFT)]){
		if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::UP)]){
			movimientos.clear();
			movimientos.push_back(SALTOIZQ);
			return CONTINUAR;
		}
		movimientos.clear();
		movimientos.push_back(IZQ);
		return CONTINUAR;
	}

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::UP)]){
		movimientos.clear();
		movimientos.push_back(ARRIBA);
		return CONTINUAR;
	}

	//JOYSTICK-----------------------------------------------------------------------------------
	if (SDL_NumJoysticks() > 0){
		SDL_Joystick* joystickAlternativo = nullptr;

		//PATADA ALTA----------------------------------------------------------------------------
		if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::HIGH_KICK) == 0){
			joystickAlternativo = unJoystick;
		}
		else{
			if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::HIGH_KICK) == 1) joystickAlternativo = otroJoystick;
		}
		if (joystickAlternativo != nullptr){

			//BOTON
			if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::HIGH_KICK)) == 1){
				//BOTON
				if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
					movimientos.clear();
					movimientos.push_back(P_ALTA_ABAJO);
					return CONTINUAR;
				}
				//FLECHAS
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
						movimientos.clear();
						movimientos.push_back(P_ALTA_ABAJO);
						return CONTINUAR;
					}
				}
				//EJES
				if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
					valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
					if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
						movimientos.clear();
						movimientos.push_back(P_ALTA_ABAJO);
						return CONTINUAR;
					}
				}
				//NADA
				movimientos.clear();
				movimientos.push_back(P_ALTA);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::HIGH_KICK)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::HIGH_KICK) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						movimientos.clear();
						movimientos.push_back(P_ALTA_ABAJO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							movimientos.clear();
							movimientos.push_back(P_ALTA_ABAJO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							movimientos.clear();
							movimientos.push_back(P_ALTA_ABAJO);
							return CONTINUAR;
						}
					}
					//NADA
					movimientos.clear();
					movimientos.push_back(P_ALTA);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::HIGH_KICK)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::HIGH_KICK));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::HIGH_KICK)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::HIGH_KICK))){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						movimientos.clear();
						movimientos.push_back(P_ALTA_ABAJO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							movimientos.clear();
							movimientos.push_back(P_ALTA_ABAJO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							movimientos.clear();
							movimientos.push_back(P_ALTA_ABAJO);
							return CONTINUAR;
						}
					}
					//NADA
					movimientos.clear();
					movimientos.push_back(P_ALTA);
					return CONTINUAR;
				}
			}

		}

		//PATADA BAJA----------------------------------------------------------------------------
		if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LOW_KICK) == 0){
			joystickAlternativo = unJoystick;
		}
		else{
			if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LOW_KICK) == 1) joystickAlternativo = otroJoystick;
		}
		if (joystickAlternativo != nullptr){

			//BOTON
			if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LOW_KICK)) == 1){
				//BOTON
				if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
					movimientos.clear();
					movimientos.push_back(P_BAJA_ABAJO);
					return CONTINUAR;
				}
				//FLECHAS
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
						movimientos.clear();
						movimientos.push_back(P_BAJA_ABAJO);
						return CONTINUAR;
					}
				}
				//EJES
				if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
					valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
					if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
						movimientos.clear();
						movimientos.push_back(P_BAJA_ABAJO);
						return CONTINUAR;
					}
				}
				//NADA
				movimientos.clear();
				movimientos.push_back(P_BAJA);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::LOW_KICK)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LOW_KICK) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						movimientos.clear();
						movimientos.push_back(P_BAJA_ABAJO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							movimientos.clear();
							movimientos.push_back(P_BAJA_ABAJO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							movimientos.clear();
							movimientos.push_back(P_BAJA_ABAJO);
							return CONTINUAR;
						}
					}
					//NADA
					movimientos.clear();
					movimientos.push_back(P_BAJA);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LOW_KICK)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LOW_KICK));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LOW_KICK)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::LOW_KICK))){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						movimientos.clear();
						movimientos.push_back(P_BAJA_ABAJO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							movimientos.clear();
							movimientos.push_back(P_BAJA_ABAJO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							movimientos.clear();
							movimientos.push_back(P_BAJA_ABAJO);
							return CONTINUAR;
						}
					}
					//NADA
					movimientos.clear();
					movimientos.push_back(P_BAJA);
					return CONTINUAR;
				}
			}

		}


		//GOLPE ALTO----------------------------------------------------------------------------
		if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::HIGH_PUNCH) == 0){
			joystickAlternativo = unJoystick;
		}
		else{
			if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::HIGH_PUNCH) == 1) joystickAlternativo = otroJoystick;
		}
		if (joystickAlternativo != nullptr){

			//BOTON
			if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::HIGH_PUNCH)) == 1){
				//BOTON
				if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
					movimientos.clear();
					movimientos.push_back(G_GANCHO);
					return CONTINUAR;
				}
				//FLECHAS
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
						movimientos.clear();
						movimientos.push_back(G_GANCHO);
						return CONTINUAR;
					}
				}
				//EJES
				if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
					valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
					if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
						movimientos.clear();
						movimientos.push_back(G_GANCHO);
						return CONTINUAR;
					}
				}
				//NADA
				movimientos.clear();
				movimientos.push_back(G_ALTO);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::HIGH_PUNCH)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::HIGH_PUNCH) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						movimientos.clear();
						movimientos.push_back(G_GANCHO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							movimientos.clear();
							movimientos.push_back(G_GANCHO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							movimientos.clear();
							movimientos.push_back(G_GANCHO);
							return CONTINUAR;
						}
					}
					//NADA
					movimientos.clear();
					movimientos.push_back(G_ALTO);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::HIGH_PUNCH)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::HIGH_PUNCH));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::HIGH_PUNCH)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::HIGH_PUNCH))){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						movimientos.clear();
						movimientos.push_back(G_GANCHO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							movimientos.clear();
							movimientos.push_back(G_GANCHO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							movimientos.clear();
							movimientos.push_back(G_GANCHO);
							return CONTINUAR;
						}
					}
					//NADA
					movimientos.clear();
					movimientos.push_back(G_ALTO);
					return CONTINUAR;
				}
			}

		}

		//GOLPE BAJO----------------------------------------------------------------------------
		if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LOW_PUNCH) == 0){
			joystickAlternativo = unJoystick;
		}
		else{
			if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LOW_PUNCH) == 1) joystickAlternativo = otroJoystick;
		}
		if (joystickAlternativo != nullptr){

			//BOTON
			if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LOW_PUNCH)) == 1){
				//BOTON
				if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
					movimientos.clear();
					movimientos.push_back(G_ABAJO);
					return CONTINUAR;
				}
				//FLECHAS
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
						movimientos.clear();
						movimientos.push_back(G_ABAJO);
						return CONTINUAR;
					}
				}
				//EJES
				if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
					valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
					if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
						movimientos.clear();
						movimientos.push_back(G_ABAJO);
						return CONTINUAR;
					}
				}
				//NADA
				movimientos.clear();
				movimientos.push_back(G_BAJO);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::LOW_PUNCH)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LOW_PUNCH) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						movimientos.clear();
						movimientos.push_back(G_ABAJO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							movimientos.clear();
							movimientos.push_back(G_ABAJO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							movimientos.clear();
							movimientos.push_back(G_ABAJO);
							return CONTINUAR;
						}
					}
					//NADA
					movimientos.clear();
					movimientos.push_back(G_BAJO);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LOW_PUNCH)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LOW_PUNCH));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LOW_PUNCH)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::HIGH_PUNCH))){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						movimientos.clear();
						movimientos.push_back(G_ABAJO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							movimientos.clear();
							movimientos.push_back(G_ABAJO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							movimientos.clear();
							movimientos.push_back(G_ABAJO);
							return CONTINUAR;
						}
					}
					//NADA
					movimientos.clear();
					movimientos.push_back(G_BAJO);
					return CONTINUAR;
				}
			}

		}


		//ARMA----------------------------------------------------------------------------
		if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::WEAPON) == 0){
			joystickAlternativo = unJoystick;
		}
		else{
			if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::WEAPON) == 1) joystickAlternativo = otroJoystick;
		}
		if (joystickAlternativo != nullptr){

			//BOTON
			if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::WEAPON)) == 1){
				//NADA
				movimientos.clear();
				movimientos.push_back(ARMA);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::WEAPON)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::WEAPON) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					//NADA
					movimientos.clear();
					movimientos.push_back(ARMA);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::WEAPON)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::WEAPON));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::WEAPON)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::HIGH_PUNCH))){
					//NADA
					movimientos.clear();
					movimientos.push_back(ARMA);
					return CONTINUAR;
				}
			}

		}

		//SALIR----------------------------------------------------------------------------
		if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::QUIT) == 0){
			joystickAlternativo = unJoystick;
		}
		else{
			if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::QUIT) == 1) joystickAlternativo = otroJoystick;
		}
		if (joystickAlternativo != nullptr){

			//BOTON
			if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::QUIT)) == 1){
				return FIN;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::QUIT)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::QUIT) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					return FIN;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::QUIT)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::QUIT));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::QUIT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::QUIT))){
					return FIN;
				}
			}

		}


		//REINICIAR----------------------------------------------------------------------------
		if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::REBOOT) == 0){
			joystickAlternativo = unJoystick;
		}
		else{
			if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::REBOOT) == 1) joystickAlternativo = otroJoystick;
		}
		if (joystickAlternativo != nullptr){

			//BOTON
			if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::REBOOT)) == 1){
				return REINICIAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::REBOOT)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::REBOOT) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					return REINICIAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::REBOOT)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::REBOOT));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::REBOOT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::REBOOT))){
					return REINICIAR;
				}
			}

		}


		//DEFENSA----------------------------------------------------------------------------
		if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::HOLD) == 0){
			joystickAlternativo = unJoystick;
		}
		else{
			if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::HOLD) == 1) joystickAlternativo = otroJoystick;
		}
		if (joystickAlternativo != nullptr){

			//BOTON
			if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::HOLD)) == 1){
				//BOTON
				if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
					movimientos.clear();
					movimientos.push_back(DEFENSA_AGACHADO);
					return CONTINUAR;
				}
				//FLECHAS
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
						movimientos.clear();
						movimientos.push_back(DEFENSA_AGACHADO);
						return CONTINUAR;
					}
				}
				//EJES
				if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
					valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
					if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
						movimientos.clear();
						movimientos.push_back(DEFENSA_AGACHADO);
						return CONTINUAR;
					}
				}
				//NADA
				movimientos.clear();
				movimientos.push_back(DEFENSA);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::HOLD)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::HOLD) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						movimientos.clear();
						movimientos.push_back(DEFENSA_AGACHADO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							movimientos.clear();
							movimientos.push_back(DEFENSA_AGACHADO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							movimientos.clear();
							movimientos.push_back(DEFENSA_AGACHADO);
							return CONTINUAR;
						}
					}
					//NADA
					movimientos.clear();
					movimientos.push_back(DEFENSA);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::HOLD)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::HOLD));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::HOLD)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::HOLD))){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						movimientos.clear();
						movimientos.push_back(DEFENSA_AGACHADO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							movimientos.clear();
							movimientos.push_back(DEFENSA_AGACHADO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							movimientos.clear();
							movimientos.push_back(DEFENSA_AGACHADO);
							return CONTINUAR;
						}
					}
					//NADA
					movimientos.clear();
					movimientos.push_back(DEFENSA);
					return CONTINUAR;
				}
			}

		}


		//ABAJO----------------------------------------------------------------------------
		if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::DOWN) == 0){
			joystickAlternativo = unJoystick;
		}
		else{
			if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::DOWN) == 1) joystickAlternativo = otroJoystick;
		}
		if (joystickAlternativo != nullptr){

			//BOTON
			if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
				movimientos.clear();
				movimientos.push_back(ABAJO);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					movimientos.clear();
					movimientos.push_back(ABAJO);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
					movimientos.clear();
					movimientos.push_back(ABAJO);
					return CONTINUAR;
				}
			}

		}



		//ARRIBA----------------------------------------------------------------------------
		if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::UP) == 0){
			joystickAlternativo = unJoystick;
		}
		else{
			if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::UP) == 1) joystickAlternativo = otroJoystick;
		}
		if (joystickAlternativo != nullptr){

			//BOTON
			if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::UP)) == 1){
				//BOTON DER
				if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT)) == 1){
					movimientos.clear();
					movimientos.push_back(SALTODER);
					return CONTINUAR;
				}
				//FLECHAS DER 
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::RIGHT)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_JoystickGetHat(joystickAlternativo, 0)){
						movimientos.clear();
						movimientos.push_back(SALTODER);
						return CONTINUAR;
					}
				}
				//EJES DER
				if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::RIGHT)){
					valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT));
					if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::RIGHT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::RIGHT))){
						movimientos.clear();
						movimientos.push_back(SALTODER);
						return CONTINUAR;
					}
				}
				//BOTON IZQ
				if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT)) == 1){
					movimientos.clear();
					movimientos.push_back(SALTOIZQ);
					return CONTINUAR;
				}
				//FLECHAS IZQ
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::LEFT)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_JoystickGetHat(joystickAlternativo, 0)){
						movimientos.clear();
						movimientos.push_back(SALTOIZQ);
						return CONTINUAR;
					}
				}
				//EJES IZQ
				if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LEFT)){
					valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT));
					if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LEFT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::LEFT))){
						movimientos.clear();
						movimientos.push_back(SALTOIZQ);
						return CONTINUAR;
					}
				}
				//NADA
				movimientos.clear();
				movimientos.push_back(ARRIBA);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::UP)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT)) == 1){
						movimientos.clear();
						movimientos.push_back(SALTODER);
						return CONTINUAR;
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::RIGHT)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::RIGHT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::RIGHT))){
							movimientos.clear();
							movimientos.push_back(SALTODER);
							return CONTINUAR;
						}
					}
					//BOTON IZQ
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT)) == 1){
						movimientos.clear();
						movimientos.push_back(SALTOIZQ);
						return CONTINUAR;
					}
					//EJES IZQ
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LEFT)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LEFT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::LEFT))){
							movimientos.clear();
							movimientos.push_back(SALTOIZQ);
							return CONTINUAR;
						}
					}
					//NADA
					movimientos.clear();
					movimientos.push_back(ARRIBA);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::UP)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::UP));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::UP)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::UP))){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT)) == 1){
						movimientos.clear();
						movimientos.push_back(SALTODER);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::RIGHT)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							movimientos.clear();
							movimientos.push_back(SALTODER);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::RIGHT)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::RIGHT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::RIGHT))){
							movimientos.clear();
							movimientos.push_back(SALTODER);
							return CONTINUAR;
						}
					}
					//BOTON IZQ
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT)) == 1){
						movimientos.clear();
						movimientos.push_back(SALTOIZQ);
						return CONTINUAR;
					}
					//FLECHAS IZQ
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::LEFT)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							movimientos.clear();
							movimientos.push_back(SALTOIZQ);
							return CONTINUAR;
						}
					}
					//EJES IZQ
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LEFT)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LEFT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::LEFT))){
							movimientos.clear();
							movimientos.push_back(SALTOIZQ);
							return CONTINUAR;
						}
					}
					//NADA
					movimientos.clear();
					movimientos.push_back(ARRIBA);
					return CONTINUAR;
				}
			}

		}

		//SALTOS COSTADOS CON FLECHAS-----------------------------------------------------------------------------
		if ((conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::UP) == 0) && (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT) == 0)){
			joystickAlternativo = unJoystick;
		}
		else{
			if ((conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::UP) == 1) && (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT) == 1)) joystickAlternativo = otroJoystick;
		}
		if (joystickAlternativo != nullptr){
			if (SDL_JoystickGetHat(joystickAlternativo, 0) == SDL_HAT_RIGHTUP){
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

			if (SDL_JoystickGetHat(joystickAlternativo, 0) == SDL_HAT_LEFTUP){
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
			if (SDL_JoystickGetHat(joystickAlternativo, 0) == SDL_HAT_RIGHTDOWN){
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

			if (SDL_JoystickGetHat(joystickAlternativo, 0) == SDL_HAT_LEFTDOWN){
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


		//DERECHA----------------------------------------------------------------------------
		if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT) == 0){
			joystickAlternativo = unJoystick;
		}
		else{
			if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT) == 1) joystickAlternativo = otroJoystick;
		}
		if (joystickAlternativo != nullptr){

			//BOTON
			if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT)) == 1){
				if (movimientos.at(0) == IZQ){
					movimientos.clear();
					movimientos.push_back(IZQ);
					return CONTINUAR;
				}
				movimientos.clear();
				movimientos.push_back(DER);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::RIGHT)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_JoystickGetHat(joystickAlternativo, 0)){
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

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::RIGHT)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT));
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

		}


		//IZQUIERDA----------------------------------------------------------------------------
		if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LEFT) == 0){
			joystickAlternativo = unJoystick;
		}
		else{
			if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LEFT) == 1) joystickAlternativo = otroJoystick;
		}
		if (joystickAlternativo != nullptr){

			//BOTON
			if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT)) == 1){
				if (movimientos.at(0) == DER){
					movimientos.clear();
					movimientos.push_back(DER);
					return CONTINUAR;
				}
				movimientos.clear();
				movimientos.push_back(IZQ);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::LEFT)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_JoystickGetHat(joystickAlternativo, 0)){
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

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LEFT)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT));
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
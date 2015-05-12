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
	SDL_JoystickUpdate();
	SDL_PumpEvents();
	state = SDL_GetKeyboardState(NULL);

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


	if (SDL_PollEvent(&event) != 0){

		if (SDL_NumJoysticks() > 0){
			if (event.type == SDL_JOYBUTTONDOWN){
				std::cout << "se presiono un boton de joystcik \n";
				numeroDeJoystick = (event.jbutton.which);
				jBoton = (event.jbutton.button);

				if ((jBoton == conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::QUIT)) && (numeroDeJoystick == conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::QUIT))) return FIN;

				if ((jBoton == conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::REBOOT)) && (numeroDeJoystick == conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::REBOOT))) return REINICIAR;

				if ((jBoton == conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::WEAPON)) && (numeroDeJoystick == conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::WEAPON))){
					movimientos.clear();
					movimientos.push_back(ARMA);
					return CONTINUAR;
				}

				if ((jBoton == conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LOW_PUNCH)) && (numeroDeJoystick == conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LOW_PUNCH))){
					if (movimientos.at(0) == ABAJO){
						movimientos.clear();
						movimientos.push_back(G_ABAJO);
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
					movimientos.clear();
					movimientos.push_back(P_ALTA);
					return CONTINUAR;
				}
			}
		}
	}

	//JOYSTICK
	if (SDL_NumJoysticks() > 0){
		unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::HOLD));
		if (unJoystick != nullptr){
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::HOLD)){
				valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::HOLD));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::HOLD)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::HOLD))){
					unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::DOWN));
					if (unJoystick != nullptr){
						if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
							valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
							if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
								movimientos.clear();
								movimientos.push_back(DEFENSA_AGACHADO);
								return CONTINUAR;
							}
						}

						if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
							if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(unJoystick, 0)){
								movimientos.clear();
								movimientos.push_back(DEFENSA_AGACHADO);
								return CONTINUAR;
							}
						}

						if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
							movimientos.clear();
							movimientos.push_back(DEFENSA_AGACHADO);
							return CONTINUAR;
						}
					}
					movimientos.clear();
					movimientos.push_back(DEFENSA);
					return CONTINUAR;
				}
			}
			else{
				if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::HOLD)) == 1){
					unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::DOWN));
					if (unJoystick != nullptr){
						if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
							valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
							if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
								movimientos.clear();
								movimientos.push_back(DEFENSA_AGACHADO);
								return CONTINUAR;
							}
						}

						if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
							if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(unJoystick, 0)){
								movimientos.clear();
								movimientos.push_back(DEFENSA_AGACHADO);
								return CONTINUAR;
							}
						}

						if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
							movimientos.clear();
							movimientos.push_back(DEFENSA_AGACHADO);
							return CONTINUAR;
						}
					}
					movimientos.clear();
					movimientos.push_back(DEFENSA);
					return CONTINUAR;
				}
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::HOLD)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::HOLD) == SDL_JoystickGetHat(unJoystick, 0)){
						unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::DOWN));
						if (unJoystick != nullptr){
							if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
								valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
								if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
									movimientos.clear();
									movimientos.push_back(DEFENSA_AGACHADO);
									return CONTINUAR;
								}
							}

							if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
								if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(unJoystick, 0)){
									movimientos.clear();
									movimientos.push_back(DEFENSA_AGACHADO);
									return CONTINUAR;
								}
							}

							if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
								movimientos.clear();
								movimientos.push_back(DEFENSA_AGACHADO);
								return CONTINUAR;
							}
						}
						movimientos.clear();
						movimientos.push_back(DEFENSA);
						return CONTINUAR;
					}
				}
			}
		}

		unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::UP));
		if (unJoystick != nullptr){
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::UP)){
				valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::UP));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::UP)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::UP))){
					unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT));
					if (unJoystick != nullptr){
						if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::RIGHT)){
							valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT));
							if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::RIGHT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::RIGHT))){
								movimientos.clear();
								movimientos.push_back(SALTODER);
								return CONTINUAR;
							}
						}
					
					else{
							if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT)) == 1){
								movimientos.clear();
								movimientos.push_back(SALTODER);
								return CONTINUAR;
							}
							if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::RIGHT)){
								if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_JoystickGetHat(unJoystick, 0)){
									movimientos.clear();
									movimientos.push_back(SALTODER);
									return CONTINUAR;
								}
							}
						}
					}
					unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LEFT));
					if (unJoystick != nullptr){
						if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LEFT)){
							valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT));
							if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LEFT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::LEFT))){
								movimientos.clear();
								movimientos.push_back(SALTOIZQ);
								return CONTINUAR;
							}
						}
						else{
							if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT)) == 1){
								movimientos.clear();
								movimientos.push_back(SALTOIZQ);
								return CONTINUAR;
							}

							if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::LEFT)){
								if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_JoystickGetHat(unJoystick, 0)){
									movimientos.clear();
									movimientos.push_back(SALTOIZQ);
									return CONTINUAR;
								}
							}

						}
					}
					movimientos.clear();
					movimientos.push_back(ARRIBA);
					return CONTINUAR;
				}
			}
			else{
					if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::UP)) == 1){
						unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT));
						if (unJoystick != nullptr){
							if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::RIGHT)){
								valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT));
								if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::RIGHT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::RIGHT))){
									movimientos.clear();
									movimientos.push_back(SALTODER);
									return CONTINUAR;
								}
							}
							else{
									if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT)) == 1){
										movimientos.clear();
										movimientos.push_back(SALTODER);
										return CONTINUAR;
									}
							
									if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::RIGHT)){
										if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_JoystickGetHat(unJoystick, 0)){
											movimientos.clear();
											movimientos.push_back(SALTODER);
											return CONTINUAR;
										}
									}
								
							}
						}
						unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LEFT));
						if (unJoystick != nullptr){
							if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LEFT)){
								valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT));
								if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LEFT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::LEFT))){
									movimientos.clear();
									movimientos.push_back(SALTOIZQ);
									return CONTINUAR;
								}
							}

							else{

									if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT)) == 1){
										movimientos.clear();
										movimientos.push_back(SALTOIZQ);
										return CONTINUAR;
									}
								
									if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::LEFT)){
										if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_JoystickGetHat(unJoystick, 0)){
											movimientos.clear();
											movimientos.push_back(SALTOIZQ);
											return CONTINUAR;
										}
									}
								
							}
						}
						movimientos.clear();
						movimientos.push_back(ARRIBA);
						return CONTINUAR;
					}

				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::UP) && conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::RIGHT)){
					if (conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::UP) == conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT)){
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

					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::UP)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_JoystickGetHat(unJoystick, 0)){
							unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT));
							if (unJoystick != nullptr){
								if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::RIGHT)){
									valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT));
									if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::RIGHT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::RIGHT))){
										movimientos.clear();
										movimientos.push_back(SALTODER);
										return CONTINUAR;
									}
								}

								else{
										if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT)) == 1){
											movimientos.clear();
											movimientos.push_back(SALTODER);
											return CONTINUAR;
										}
									
										if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::RIGHT)){
											if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_JoystickGetHat(unJoystick, 0)){
												movimientos.clear();
												movimientos.push_back(SALTODER);
												return CONTINUAR;
											}
										}
									
								}
							}
							unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LEFT));
							if (unJoystick != nullptr){
								if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LEFT)){
									valorDelEje = SDL_JoystickGetAxis(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT));
									if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LEFT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::LEFT))){
										movimientos.clear();
										movimientos.push_back(SALTOIZQ);
										return CONTINUAR;
									}
								}

								else{
										if (SDL_JoystickGetButton(unJoystick, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT)) == 1){
											movimientos.clear();
											movimientos.push_back(SALTOIZQ);
											return CONTINUAR;
										}
									
										if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::LEFT)){
											if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_JoystickGetHat(unJoystick, 0)){
												movimientos.clear();
												movimientos.push_back(SALTOIZQ);
												return CONTINUAR;
											}
										}
									
								}
							}
							movimientos.clear();
							movimientos.push_back(ARRIBA);
							return CONTINUAR;
						}
					}
				
			}
		}



			unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::RIGHT));
			if (unJoystick != nullptr){
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
			}

			unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::LEFT));
			if (unJoystick != nullptr){
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
			}

			unJoystick = SDL_JoystickOpen(conversorDeEventos->geNnumeroDeJoystickDeLaAccion(ConversorDeEventos::DOWN));
			if (unJoystick != nullptr){
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
#include "stdafx.h"
#include "Controlador.h"
#include "ConversorAString.h"

Controlador::Controlador()
{
	cantidadDeEventosAnterior = 0;
	otraCantidadDeEventosAnterior = 0;
	j = 0;
	golpeBajoTecladoHabilitado = true;
	golpeAltoTecladoHabilitado = true;
	patadaBajaTecladoHabilitada = true;
	patadaAltaTecladoHabilitada = true;

	movimientos = std::vector<MOV_TIPO>();
	movimientos.push_back(QUIETO);

	movimientosActivos = std::vector<MOV_TIPO>();
	movimientosActivos.push_back(QUIETO);

	controladorDeTomas = new ControladorDeTomas();
	controladorDeTomas->setMovimientos(&movimientosActivos);

	conversorDeEventos = nullptr;
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


void Controlador::mantenerMovimientosActivos(){
	std::vector<MOV_TIPO> movimientosAuxilares;

	if (movimientosActivos.size() == 6){
		movimientosAuxilares = std::vector<MOV_TIPO>();
		for (size_t i = 1; i < movimientosActivos.size(); i++){
			movimientosAuxilares.push_back(movimientosActivos.at(i));
		}
		movimientosActivos = movimientosAuxilares;
	}
}


void Controlador::mantenerMovimientos(){
	std::vector<MOV_TIPO> movimientosAuxilares;

	if (movimientos.size() == CANTIDAD_MAXIMA_EVENTOS){
		movimientosAuxilares = std::vector<MOV_TIPO>();
		for (size_t i = (movimientos.size() - (CANTIDAD_MAXIMA_EVENTOS / 2) - 1); i < movimientos.size(); i++){
			movimientosAuxilares.push_back(movimientos.at(i));
		}
		movimientos = movimientosAuxilares;
	}

}


ControladorDeTomas* Controlador::getControladorDeTomas(){
	return controladorDeTomas;
}


MOV_TIPO Controlador::getUltimoMovimientoActivo(){
	
	MOV_TIPO unMovimiento;
	if (!movimientos.empty()){
		unMovimiento = movimientos.back();
		if (cantidadDeEventosAnterior != movimientos.size()){
			cantidadDeEventosAnterior = movimientos.size();
			if (unMovimiento != QUIETO) return unMovimiento;
		}
	}
	return QUIETO;
}


int Controlador::cambiar(){

	if (conversorDeEventos != nullptr){

	SDL_JoystickUpdate();
	SDL_PumpEvents();
	state = SDL_GetKeyboardState(NULL);

	//ACTUALIZO EL VECTOR
	mantenerMovimientos();
	mantenerMovimientosActivos();
	ConversorAString* unConversorAString = new ConversorAString();

	MOV_TIPO unMovimiento;
	unMovimiento = getUltimoMovimientoActivo();
	if (unMovimiento != QUIETO) movimientosActivos.push_back(unMovimiento);

	if (MOSTRAR_MOVIMIENTOS){
		std::string mensaje = unConversorAString->getTeclaComoStringDelMovimientoParaElConversorDeEventos(unMovimiento, conversorDeEventos);
		if (mensaje != "") std::cout << mensaje << "\n";
		delete unConversorAString;
	}

	//TECLADO--------------------------------------------------------------------------
	if (!state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::LOW_PUNCH)]) golpeBajoTecladoHabilitado = true;
	if (!state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::HIGH_PUNCH)]) golpeAltoTecladoHabilitado = true;
	if (!state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::LOW_KICK)]) patadaBajaTecladoHabilitada = true;
	if (!state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::HIGH_KICK)]) patadaAltaTecladoHabilitada = true;

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::QUIT)]) {
		return FIN;
	}

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::REBOOT)]) {
		return REINICIAR;
	}

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::LOW_PUNCH)]){
		if (golpeBajoTecladoHabilitado){
			golpeBajoTecladoHabilitado = false;
			if (movimientos.back() == ABAJO){
				movimientos.push_back(G_ABAJO);
				return CONTINUAR;
			}
			if (movimientos.back() == G_ABAJO) return CONTINUAR;

			if (movimientos.back() != G_BAJO) movimientos.push_back(G_BAJO);
			return CONTINUAR;
		}
	}

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::HIGH_PUNCH)]){
		if (golpeAltoTecladoHabilitado){
			golpeAltoTecladoHabilitado = false;
			if (movimientos.back() == ABAJO){
				movimientos.push_back(G_GANCHO);
				return CONTINUAR;
			}
			if (movimientos.back() == G_GANCHO) return CONTINUAR;

			if (movimientos.back() != G_ALTO) movimientos.push_back(G_ALTO);
			return CONTINUAR;
		}
	}

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::LOW_KICK)]){
		if (patadaBajaTecladoHabilitada){
			patadaBajaTecladoHabilitada = false;
			if (movimientos.back() == ABAJO){
				movimientos.push_back(P_BAJA_ABAJO);
				return CONTINUAR;
			}
			if (movimientos.back() == P_BAJA_ABAJO) return CONTINUAR;

			if (movimientos.back() != P_BAJA) movimientos.push_back(P_BAJA);
			return CONTINUAR;
		}
	}

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::HIGH_KICK)]){
		if (patadaAltaTecladoHabilitada){
			patadaAltaTecladoHabilitada = false;
			if (movimientos.back() == ABAJO){
				movimientos.push_back(P_ALTA_ABAJO);
				return CONTINUAR;
			}
			if (movimientos.back() == P_ALTA_ABAJO) return CONTINUAR;

			if (movimientos.back() != P_ALTA) movimientos.push_back(P_ALTA);
			return CONTINUAR;
		}
	}
	
	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::WEAPON)]){
		if (movimientos.back() != ARMA) movimientos.push_back(ARMA);
		return CONTINUAR;
	}


	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::HOLD)]){
		if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::DOWN)]){
				if (movimientos.back() != DEFENSA_AGACHADO) movimientos.push_back(DEFENSA_AGACHADO);
				return CONTINUAR;
		}
		if (movimientos.back() != DEFENSA) movimientos.push_back(DEFENSA);
		return CONTINUAR;
	}

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::DOWN)]){
		if (movimientos.back() != ABAJO) movimientos.push_back(ABAJO);
		return CONTINUAR;
	}

	if ((state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::LEFT)]) && (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::RIGHT)]))
		if ((movimientos.back() == DER) || (movimientos.back() == IZQ))
			return CONTINUAR;

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::RIGHT)]){
		if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::UP)]){
			if (movimientos.back() != SALTODER) movimientos.push_back(SALTODER);
			return CONTINUAR;
		}
		if (movimientos.back() != DER) movimientos.push_back(DER);
		return CONTINUAR;
	}

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::LEFT)]){
		if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::UP)]){
			if (movimientos.back() != SALTOIZQ) movimientos.push_back(SALTOIZQ);
			return CONTINUAR;
		}
		if (movimientos.back() != IZQ) movimientos.push_back(IZQ);
		return CONTINUAR;
	}

	if (state[conversorDeEventos->getScanCodeDeLaAccion(ConversorDeEventos::UP)]){
		if (movimientos.back() != ARRIBA) movimientos.push_back(ARRIBA);
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
					if (movimientos.back() != P_ALTA_ABAJO) movimientos.push_back(P_ALTA_ABAJO);
					return CONTINUAR;
				}
				//FLECHAS
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
						if (movimientos.back() != P_ALTA_ABAJO) movimientos.push_back(P_ALTA_ABAJO);
						return CONTINUAR;
					}
				}
				//EJES
				if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
					valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
					if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
						if (movimientos.back() != P_ALTA_ABAJO) movimientos.push_back(P_ALTA_ABAJO);
						return CONTINUAR;
					}
				}
				//NADA
				if (movimientos.back() != P_ALTA) movimientos.push_back(P_ALTA);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::HIGH_KICK)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::HIGH_KICK) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						if (movimientos.back() != P_ALTA_ABAJO) movimientos.push_back(P_ALTA_ABAJO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							if (movimientos.back() != P_ALTA_ABAJO) movimientos.push_back(P_ALTA_ABAJO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							if (movimientos.back() != P_ALTA_ABAJO) movimientos.push_back(P_ALTA_ABAJO);
							return CONTINUAR;
						}
					}
					//NADA
					if (movimientos.back() != P_ALTA) movimientos.push_back(P_ALTA);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::HIGH_KICK)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::HIGH_KICK));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::HIGH_KICK)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::HIGH_KICK))){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						if (movimientos.back() != P_ALTA_ABAJO) movimientos.push_back(P_ALTA_ABAJO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							if (movimientos.back() != P_ALTA_ABAJO) movimientos.push_back(P_ALTA_ABAJO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							if (movimientos.back() != P_ALTA_ABAJO) movimientos.push_back(P_ALTA_ABAJO);
							return CONTINUAR;
						}
					}
					//NADA
					if (movimientos.back() != P_ALTA) movimientos.push_back(P_ALTA);
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
					if (movimientos.back() != P_BAJA_ABAJO) movimientos.push_back(P_BAJA_ABAJO);
					return CONTINUAR;
				}
				//FLECHAS
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
						if (movimientos.back() != P_BAJA_ABAJO)  movimientos.push_back(P_BAJA_ABAJO);
						return CONTINUAR;
					}
				}
				//EJES
				if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
					valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
					if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
						if (movimientos.back() != P_BAJA_ABAJO) movimientos.push_back(P_BAJA_ABAJO);
						return CONTINUAR;
					}
				}
				//NADA
				if (movimientos.back() != P_BAJA) movimientos.push_back(P_BAJA);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::LOW_KICK)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LOW_KICK) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						if (movimientos.back() != P_BAJA_ABAJO) movimientos.push_back(P_BAJA_ABAJO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							if (movimientos.back() != P_BAJA_ABAJO) movimientos.push_back(P_BAJA_ABAJO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							if (movimientos.back() != P_BAJA_ABAJO) movimientos.push_back(P_BAJA_ABAJO);
							return CONTINUAR;
						}
					}
					//NADA
					if (movimientos.back() != P_BAJA) movimientos.push_back(P_BAJA);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LOW_KICK)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LOW_KICK));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LOW_KICK)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::LOW_KICK))){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						if (movimientos.back() != P_BAJA_ABAJO) movimientos.push_back(P_BAJA_ABAJO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							if (movimientos.back() != P_BAJA_ABAJO) movimientos.push_back(P_BAJA_ABAJO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							if (movimientos.back() != P_BAJA_ABAJO) movimientos.push_back(P_BAJA_ABAJO);
							return CONTINUAR;
						}
					}
					//NADA
					if (movimientos.back() != P_BAJA) movimientos.push_back(P_BAJA);
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
					if (movimientos.back() != G_GANCHO) movimientos.push_back(G_GANCHO);
					return CONTINUAR;
				}
				//FLECHAS
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
						if (movimientos.back() != G_GANCHO) movimientos.push_back(G_GANCHO);
						return CONTINUAR;
					}
				}
				//EJES
				if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
					valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
					if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
						if (movimientos.back() != G_GANCHO) movimientos.push_back(G_GANCHO);
						return CONTINUAR;
					}
				}
				//NADA
				if (movimientos.back() != G_ALTO) movimientos.push_back(G_ALTO);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::HIGH_PUNCH)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::HIGH_PUNCH) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						if (movimientos.back() != G_GANCHO) movimientos.push_back(G_GANCHO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							if (movimientos.back() != G_GANCHO) movimientos.push_back(G_GANCHO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							if (movimientos.back() != G_GANCHO) movimientos.push_back(G_GANCHO);
							return CONTINUAR;
						}
					}
					//NADA
					if (movimientos.back() != G_ALTO) movimientos.push_back(G_ALTO);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::HIGH_PUNCH)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::HIGH_PUNCH));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::HIGH_PUNCH)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::HIGH_PUNCH))){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						if (movimientos.back() != G_GANCHO) movimientos.push_back(G_GANCHO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							if (movimientos.back() != G_GANCHO) movimientos.push_back(G_GANCHO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							if (movimientos.back() != G_GANCHO) movimientos.push_back(G_GANCHO);
							return CONTINUAR;
						}
					}
					//NADA
					if (movimientos.back() != G_ALTO) movimientos.push_back(G_ALTO);
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
					if (movimientos.back() != G_ABAJO) movimientos.push_back(G_ABAJO);
					return CONTINUAR;
				}
				//FLECHAS
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
						if (movimientos.back() != G_ABAJO) movimientos.push_back(G_ABAJO);
						return CONTINUAR;
					}
				}
				//EJES
				if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
					valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
					if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
						if (movimientos.back() != G_ABAJO) movimientos.push_back(G_ABAJO);
						return CONTINUAR;
					}
				}
				//NADA
				if (movimientos.back() != G_BAJO) movimientos.push_back(G_BAJO);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::LOW_PUNCH)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LOW_PUNCH) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						if (movimientos.back() != G_ABAJO) movimientos.push_back(G_ABAJO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							if (movimientos.back() != G_ABAJO) movimientos.push_back(G_ABAJO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							if (movimientos.back() != G_ABAJO) movimientos.push_back(G_ABAJO);
							return CONTINUAR;
						}
					}
					//NADA
					if (movimientos.back() != G_BAJO) movimientos.push_back(G_BAJO);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LOW_PUNCH)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LOW_PUNCH));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LOW_PUNCH)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::HIGH_PUNCH))){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						if (movimientos.back() != G_ABAJO) movimientos.push_back(G_ABAJO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							if (movimientos.back() != G_ABAJO) movimientos.push_back(G_ABAJO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							if (movimientos.back() != G_ABAJO) movimientos.push_back(G_ABAJO);
							return CONTINUAR;
						}
					}
					//NADA
					if (movimientos.back() != G_BAJO) movimientos.push_back(G_BAJO);
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
				if (movimientos.back() != ARMA) movimientos.push_back(ARMA);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::WEAPON)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::WEAPON) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					//NADA
					if (movimientos.back() != ARMA) movimientos.push_back(ARMA);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::WEAPON)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::WEAPON));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::WEAPON)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::HIGH_PUNCH))){
					//NADA
					if (movimientos.back() != ARMA) movimientos.push_back(ARMA);
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
					if (movimientos.back() != DEFENSA_AGACHADO) movimientos.push_back(DEFENSA_AGACHADO);
					return CONTINUAR;
				}
				//FLECHAS
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
						if (movimientos.back() != DEFENSA_AGACHADO) movimientos.push_back(DEFENSA_AGACHADO);
						return CONTINUAR;
					}
				}
				//EJES
				if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
					valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
					if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
						if (movimientos.back() != DEFENSA_AGACHADO) movimientos.push_back(DEFENSA_AGACHADO);
						return CONTINUAR;
					}
				}
				//NADA
				if (movimientos.back() != DEFENSA) movimientos.push_back(DEFENSA);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::HOLD)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::HOLD) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						if (movimientos.back() != DEFENSA_AGACHADO) movimientos.push_back(DEFENSA_AGACHADO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							if (movimientos.back() != DEFENSA_AGACHADO) movimientos.push_back(DEFENSA_AGACHADO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							if (movimientos.back() != DEFENSA_AGACHADO) movimientos.push_back(DEFENSA_AGACHADO);
							return CONTINUAR;
						}
					}
					//NADA
					if (movimientos.back() != DEFENSA) movimientos.push_back(DEFENSA);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::HOLD)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::HOLD));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::HOLD)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::HOLD))){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN)) == 1){
						if (movimientos.back() != DEFENSA_AGACHADO) movimientos.push_back(DEFENSA_AGACHADO);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							if (movimientos.back() != DEFENSA_AGACHADO) movimientos.push_back(DEFENSA_AGACHADO);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
							if (movimientos.back() != DEFENSA_AGACHADO) movimientos.push_back(DEFENSA_AGACHADO);
							return CONTINUAR;
						}
					}
					//NADA
					if (movimientos.back() != DEFENSA) movimientos.push_back(DEFENSA);
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
				if (movimientos.back() != ABAJO) movimientos.push_back(ABAJO);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::DOWN)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::DOWN) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					if (movimientos.back() != ABAJO) movimientos.push_back(ABAJO);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::DOWN)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::DOWN));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::DOWN)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::DOWN))){
					if (movimientos.back() != ABAJO) movimientos.push_back(ABAJO);
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
					if (movimientos.back() != SALTODER) movimientos.push_back(SALTODER);
					return CONTINUAR;
				}
				//FLECHAS DER 
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::RIGHT)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_JoystickGetHat(joystickAlternativo, 0)){
						if (movimientos.back() != SALTODER) movimientos.push_back(SALTODER);
						return CONTINUAR;
					}
				}
				//EJES DER
				if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::RIGHT)){
					valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT));
					if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::RIGHT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::RIGHT))){
						if (movimientos.back() != SALTODER) movimientos.push_back(SALTODER);
						return CONTINUAR;
					}
				}
				//BOTON IZQ
				if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT)) == 1){
					if (movimientos.back() != SALTOIZQ) movimientos.push_back(SALTOIZQ);
					return CONTINUAR;
				}
				//FLECHAS IZQ
				if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::LEFT)){
					if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_JoystickGetHat(joystickAlternativo, 0)){
						if (movimientos.back() != SALTOIZQ) movimientos.push_back(SALTOIZQ);
						return CONTINUAR;
					}
				}
				//EJES IZQ
				if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LEFT)){
					valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT));
					if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LEFT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::LEFT))){
						if (movimientos.back() != SALTOIZQ) movimientos.push_back(SALTOIZQ);
						return CONTINUAR;
					}
				}
				//NADA
				if (movimientos.back() != ARRIBA) movimientos.push_back(ARRIBA);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::UP)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT)) == 1){
						if (movimientos.back() != SALTODER) movimientos.push_back(SALTODER);
						return CONTINUAR;
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::RIGHT)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::RIGHT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::RIGHT))){
							if (movimientos.back() != SALTODER) movimientos.push_back(SALTODER);
							return CONTINUAR;
						}
					}
					//BOTON IZQ
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT)) == 1){
						if (movimientos.back() != SALTOIZQ) movimientos.push_back(SALTOIZQ);
						return CONTINUAR;
					}
					//EJES IZQ
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LEFT)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LEFT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::LEFT))){
							if (movimientos.back() != SALTOIZQ) movimientos.push_back(SALTOIZQ);
							return CONTINUAR;
						}
					}
					//NADA
					if (movimientos.back() != ARRIBA) movimientos.push_back(ARRIBA);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::UP)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::UP));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::UP)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::UP))){
					//BOTON
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT)) == 1){
						if (movimientos.back() != SALTODER) movimientos.push_back(SALTODER);
						return CONTINUAR;
					}
					//FLECHAS
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::RIGHT)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							if (movimientos.back() != SALTODER) movimientos.push_back(SALTODER);
							return CONTINUAR;
						}
					}
					//EJES
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::RIGHT)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::RIGHT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::RIGHT))){
							if (movimientos.back() != SALTODER) movimientos.push_back(SALTODER);
							return CONTINUAR;
						}
					}
					//BOTON IZQ
					if (SDL_JoystickGetButton(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT)) == 1){
						if (movimientos.back() != SALTOIZQ) movimientos.push_back(SALTOIZQ);
						return CONTINUAR;
					}
					//FLECHAS IZQ
					if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::LEFT)){
						if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_JoystickGetHat(joystickAlternativo, 0)){
							if (movimientos.back() != SALTOIZQ) movimientos.push_back(SALTOIZQ);
							return CONTINUAR;
						}
					}
					//EJES IZQ
					if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LEFT)){
						valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT));
						if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LEFT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::LEFT))){
							if (movimientos.back() != SALTOIZQ) movimientos.push_back(SALTOIZQ);
							return CONTINUAR;
						}
					}
					//NADA
					if (movimientos.back() != ARRIBA) movimientos.push_back(ARRIBA);
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
					if (movimientos.back() != SALTODER) movimientos.push_back(SALTODER);
					return CONTINUAR;
				}
				if (((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_UP) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_HAT_LEFT)) || ((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_LEFT) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_HAT_UP))){
					if (movimientos.back() != SALTOIZQ) movimientos.push_back(SALTOIZQ);
					return CONTINUAR;
				}
			}

			if (SDL_JoystickGetHat(joystickAlternativo, 0) == SDL_HAT_LEFTUP){
				if (((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_UP) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_HAT_RIGHT)) || ((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_RIGHT) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_HAT_UP))){
					if (movimientos.back() != SALTODER) movimientos.push_back(SALTODER);
					return CONTINUAR;
				}
				if (((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_UP) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_HAT_LEFT)) || ((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_LEFT) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_HAT_UP))){
					if (movimientos.back() != SALTOIZQ) movimientos.push_back(SALTOIZQ);
					return CONTINUAR;
				}
			}
			if (SDL_JoystickGetHat(joystickAlternativo, 0) == SDL_HAT_RIGHTDOWN){
				if (((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_DOWN) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_HAT_RIGHT)) || ((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_RIGHT) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_HAT_DOWN))){
					if (movimientos.back() != SALTODER) movimientos.push_back(SALTODER);
					return CONTINUAR;
				}
				if (((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_DOWN) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_HAT_LEFT)) || ((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_LEFT) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_HAT_DOWN))){
					if (movimientos.back() != SALTOIZQ) movimientos.push_back(SALTOIZQ);
					return CONTINUAR;
				}
			}

			if (SDL_JoystickGetHat(joystickAlternativo, 0) == SDL_HAT_LEFTDOWN){
				if (((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_DOWN) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_HAT_RIGHT)) || ((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_RIGHT) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_HAT_DOWN))){
					if (movimientos.back() != SALTODER) movimientos.push_back(SALTODER);
					return CONTINUAR;
				}
				if (((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_DOWN) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_HAT_LEFT)) || ((conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::UP) == SDL_HAT_LEFT) && (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_HAT_DOWN))){
					if (movimientos.back() != SALTOIZQ) movimientos.push_back(SALTOIZQ);
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
				if (movimientos.back() == IZQ){
					return CONTINUAR;
				}
				if (movimientos.back() != DER) movimientos.push_back(DER);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::RIGHT)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::RIGHT) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					if (movimientos.back() == IZQ){
						return CONTINUAR;
					}
					if (movimientos.back() != DER) movimientos.push_back(DER);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::RIGHT)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::RIGHT));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::RIGHT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::RIGHT))){
					if (movimientos.back() == IZQ){
						return CONTINUAR;
					}
					if (movimientos.back() != DER) movimientos.push_back(DER);
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
				if (movimientos.back() == DER){
					return CONTINUAR;
				}
				if (movimientos.back() != IZQ) movimientos.push_back(IZQ);
				return CONTINUAR;
			}

			//FLECHAS
			if (conversorDeEventos->hayFlechasParaLaAccion(ConversorDeEventos::LEFT)){
				if (conversorDeEventos->getHatDeLaAccion(ConversorDeEventos::LEFT) == SDL_JoystickGetHat(joystickAlternativo, 0)){
					if (movimientos.back() == DER){
						return CONTINUAR;
					}
					if (movimientos.back() != IZQ) movimientos.push_back(IZQ);
					return CONTINUAR;
				}
			}

			//EJES
			if (conversorDeEventos->hayEjeParaLaAccion(ConversorDeEventos::LEFT)){
				valorDelEje = SDL_JoystickGetAxis(joystickAlternativo, conversorDeEventos->getJbotonDeLaAccion(ConversorDeEventos::LEFT));
				if ((valorDelEje >= conversorDeEventos->getValorDesdeDelEjeDeLaAccion(ConversorDeEventos::LEFT)) && (valorDelEje <= conversorDeEventos->getValorHastaDelEjeDeLaAccion(ConversorDeEventos::LEFT))){
					if (movimientos.back() == DER){
						return CONTINUAR;
					}
					if (movimientos.back() != IZQ) movimientos.push_back(IZQ);
					return CONTINUAR;
				}
			}

		}
	}

	}

	if (movimientos.back() != QUIETO) movimientos.push_back(QUIETO);

	return CONTINUAR;
	
}


ConversorDeEventos* Controlador::getConversorDeEventos(){
	return conversorDeEventos;
}


Controlador::~Controlador()
{
	movimientos.clear();
	delete controladorDeTomas;
}
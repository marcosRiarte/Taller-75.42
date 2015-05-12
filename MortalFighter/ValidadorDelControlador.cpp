#include "stdafx.h"
#include "ValidadorDelControlador.h"


ValidadorDelControlador::ValidadorDelControlador()
{
	controlador1 = nullptr;
	controlador2 = nullptr;
}


std::vector<std::string>* ValidadorDelControlador::cargarConstantesParaElControlador(int numeroDeControlador){
	std::vector<std::string>* constantes = new std::vector<std::string>();

	if (numeroDeControlador == 1){
		constantes->push_back(ARRIBA_DEFAULT_1);
		constantes->push_back(ABAJO_DEFAULT_1);
		constantes->push_back(IZQUIERDA_DEFAULT_1);
		constantes->push_back(DERECHA_DEFAULT_1);
		constantes->push_back(DEFENSA_DEFAULT_1);
		constantes->push_back(ARMA_DEFAULT_1);
		constantes->push_back(REINICIAR_DEFAULT);
		constantes->push_back(SALIR_DEFAULT);
		constantes->push_back(G_BAJO_DEFAULT_1);
		constantes->push_back(G_ALTO_DEFAULT_1);
		constantes->push_back(P_BAJA_DEFAULT_1);
		constantes->push_back(P_ALTA_DEFAULT_1);
		return constantes;
	}
	constantes->push_back(ARRIBA_DEFAULT_2);
	constantes->push_back(ABAJO_DEFAULT_2);
	constantes->push_back(IZQUIERDA_DEFAULT_2);
	constantes->push_back(DERECHA_DEFAULT_2);
	constantes->push_back(DEFENSA_DEFAULT_2);
	constantes->push_back(ARMA_DEFAULT_2);
	constantes->push_back(REINICIAR_DEFAULT);
	constantes->push_back(SALIR_DEFAULT);
	constantes->push_back(G_BAJO_DEFAULT_2);
	constantes->push_back(G_ALTO_DEFAULT_2);
	constantes->push_back(P_BAJA_DEFAULT_2);
	constantes->push_back(P_ALTA_DEFAULT_2);
	return constantes;

}


int ValidadorDelControlador::crearYobtenerNumeroDeControlador(){
	if (!controlador1){
		controlador1 = new Controlador();
		return 1;
	}
	if (!controlador2){
			controlador2 = new Controlador();
			return 2;
	}
	return 1;
}


void ValidadorDelControlador::validarControladorDesde(Json::Value unControlador){
	ConversorDeEventos* unConversorDeEventos = new ConversorDeEventos();

	std::string arriba, abajo, izquierda, derecha, golpe_bajo, golpe_alto;
	std::string patada_baja, patada_alta, defensa, arma, reiniciar, salir;
	std::string mensaje, mensajeDelNumeroDeControlador;
	int numeroDeControlador;
	std::vector<std::string>* acciones;

	if (!unControlador){
		Log::getInstancia().logearMensajeEnModo("Fallo el parseo del Control 1, se cargara por defecto", Log::MODO_WARNING);
	}
	else{
		numeroDeControlador = crearYobtenerNumeroDeControlador();

		if (numeroDeControlador == 1) mensajeDelNumeroDeControlador = "1 no tiene un valor correcto asignado, quedara sin setear";
		else mensajeDelNumeroDeControlador = "2 no tiene un valor correcto asignado, quedara sin setear";

		acciones = cargarConstantesParaElControlador(numeroDeControlador);

		arriba = acciones->at(0);
		abajo = acciones->at(1);
		izquierda = acciones->at(2);
		derecha = acciones->at(3);
		defensa = acciones->at(4);
		arma = acciones->at(5);
		reiniciar = acciones->at(6);
		salir = acciones->at(7);
		golpe_bajo = acciones->at(8);
		golpe_alto = acciones->at(9);
		patada_baja = acciones->at(10);
		patada_alta = acciones->at(11);

		delete acciones;
		

		if ((unControlador.isMember("arriba") && unControlador.get("arriba", ARRIBA_DEFAULT_1).isString())){
			arriba = unControlador.get("arriba", ARRIBA_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton arriba por defecto", Log::MODO_WARNING);
		}

		if ((unControlador.isMember("abajo") && unControlador.get("abajo", ABAJO_DEFAULT_1).isString())){
			abajo = unControlador.get("abajo", ABAJO_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton abajo por defecto", Log::MODO_WARNING);
		}

		if ((unControlador.isMember("izquierda") && unControlador.get("izquierda", IZQUIERDA_DEFAULT_1).isString())){
			izquierda = unControlador.get("izquierda", IZQUIERDA_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton izquierda por defecto", Log::MODO_WARNING);
		}

		if ((unControlador.isMember("derecha") && unControlador.get("derecha", DERECHA_DEFAULT_1).isString())){
			derecha = unControlador.get("derecha", DERECHA_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton derecha por defecto", Log::MODO_WARNING);
		}

		if ((unControlador.isMember("defensa") && unControlador.get("defensa", DEFENSA_DEFAULT_1).isString())){
			defensa = unControlador.get("defensa", DEFENSA_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton defensa por defecto", Log::MODO_WARNING);
		}

		if ((unControlador.isMember("arma") && unControlador.get("arma", ARMA_DEFAULT_1).isString())){
			arma = unControlador.get("arma", ARMA_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton arma por defecto", Log::MODO_WARNING);
		}

		if ((unControlador.isMember("reiniciar") && unControlador.get("reiniciar", REINICIAR_DEFAULT).isString())){
			reiniciar = unControlador.get("reiniciar", REINICIAR_DEFAULT).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton reiniciar por defecto", Log::MODO_WARNING);
		}

		if ((unControlador.isMember("salir") && unControlador.get("salir", SALIR_DEFAULT).isString())){
			salir = unControlador.get("salir", SALIR_DEFAULT).asString();
		}

		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton salir por defecto", Log::MODO_WARNING);
		}

		if ((unControlador.isMember("golpe_bajo") && unControlador.get("golpe_bajo", G_BAJO_DEFAULT_1).isString())){
			golpe_bajo = unControlador.get("golpe_bajo", G_BAJO_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton golpe_bajo por defecto", Log::MODO_WARNING);
		}

		if ((unControlador.isMember("golpe_alto") && unControlador.get("golpe_alto", G_ALTO_DEFAULT_1).isString())){
			golpe_alto = unControlador.get("golpe_alto", G_ALTO_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton golpe_alto por defecto", Log::MODO_WARNING);
		}

		if ((unControlador.isMember("patada_baja") && unControlador.get("patada_baja", P_BAJA_DEFAULT_1).isString())){
			patada_baja = unControlador.get("patada_baja", P_BAJA_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton patada_baja por defecto", Log::MODO_WARNING);
		}

		if ((unControlador.isMember("patada_alta") && unControlador.get("patada_alta", P_ALTA_DEFAULT_1).isString())){
			patada_alta = unControlador.get("patada_alta", P_ALTA_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton patada_alta por defecto", Log::MODO_WARNING);
		}
	}



	if (!unConversorDeEventos->setAccion(ConversorDeEventos::UP, arriba)){
		mensaje = "Accion arriba del control " + mensajeDelNumeroDeControlador;
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
	}

	if (!unConversorDeEventos->setAccion(ConversorDeEventos::DOWN, abajo)){
		mensaje = "Accion abajo del control " + mensajeDelNumeroDeControlador;
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
	}

	if(!unConversorDeEventos->setAccion(ConversorDeEventos::RIGHT, derecha)){
		mensaje = "Accion derecha del control " + mensajeDelNumeroDeControlador;
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
	}
	
	if (!unConversorDeEventos->setAccion(ConversorDeEventos::LEFT, izquierda)){
		mensaje = "Accion izquierda del control " + mensajeDelNumeroDeControlador;
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
	}

	if (!unConversorDeEventos->setAccion(ConversorDeEventos::HOLD, defensa)){
		mensaje = "Accion defensa del control " + mensajeDelNumeroDeControlador;
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
	}

	if (!unConversorDeEventos->setAccion(ConversorDeEventos::REBOOT, reiniciar)){
		mensaje = "Accion reiniciar del control " + mensajeDelNumeroDeControlador;
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
	}

	if (!unConversorDeEventos->setAccion(ConversorDeEventos::WEAPON, arma)){
		mensaje = "Accion arma del control " + mensajeDelNumeroDeControlador;
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
	}

	if (!unConversorDeEventos->setAccion(ConversorDeEventos::QUIT, salir)){
		mensaje = "Accion salir del control " + mensajeDelNumeroDeControlador;
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
	}

	if (!unConversorDeEventos->setAccion(ConversorDeEventos::LOW_PUNCH, golpe_bajo)){
		mensaje = "Accion golpe bajo del control " + mensajeDelNumeroDeControlador;
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
	}

	if (!unConversorDeEventos->setAccion(ConversorDeEventos::HIGH_PUNCH, golpe_alto)){
		mensaje = "Accion golpe alto del control " + mensajeDelNumeroDeControlador;
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
	}

	if (!unConversorDeEventos->setAccion(ConversorDeEventos::LOW_KICK, patada_baja)){
		mensaje = "Accion pataeda baja del control " + mensajeDelNumeroDeControlador;
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
	}

	if (!unConversorDeEventos->setAccion(ConversorDeEventos::HIGH_KICK, patada_alta)){
		mensaje = "Accion patada alta del control " + mensajeDelNumeroDeControlador;
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
	}

	if (numeroDeControlador == 1){
		controlador1->setConversorDeEventos(unConversorDeEventos);
		Log::getInstancia().logearMensajeEnModo("Se cargaron los valores para el control 1", Log::MODO_DEBUG);
	}
	else {
		controlador2->setConversorDeEventos(unConversorDeEventos);
		Log::getInstancia().logearMensajeEnModo("Se cargaron los valores para el control 2", Log::MODO_DEBUG);
	}
}


Controlador* ValidadorDelControlador::getControlador1(){
	return controlador1;
}


Controlador* ValidadorDelControlador::getControlador2(){
	return controlador2;
}


ValidadorDelControlador::~ValidadorDelControlador()
{
	delete controlador1;
	delete controlador2;
}

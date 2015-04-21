#include "stdafx.h"
#include "Log.h"
#include <fstream>
#include "FechayHora.h"
#include "MortalFigther.h"




std::string Log::pathDelArchivo = "log.txt";


Log::Log(){

	modoActual = MODO_DEBUG;

	//si esta definido lo imprimo por pantalla
	#ifdef DEBUGENVENTANA
		cout << "---------------------------------------------------------------------------" << "\n" << "\n";
	#endif

	#ifndef DEBUGENVENTANA
		//ABRO EL ARCHIVO. SI NO EXISTE LO CREO.
		std::ofstream archivoLog(pathDelArchivo, std::ios::out | std::ios::app);
		if (archivoLog.is_open()){

			archivoLog << "---------------------------------------------------------------------------------" << "\n" << "\n";
			archivoLog.close();
		}
	#endif

}


void Log::setModoDeLog(ModoDeLog unModoDeLog){

	modoActual = unModoDeLog;

}


void Log::logearMensajeEnModo(std::string unMensaje, ModoDeLog unModoDeLog){

	if (unModoDeLog >= modoActual){

		//si esta definido lo imprimo por pantalla
#ifdef DEBUGENVENTANA
		cout << FechayHora::obtenerUnicaInstancia()->obtenerFechayHoraActual() << " [" << toString(unModoDeLog) << "] " << unMensaje << "\n";
#endif

#ifndef DEBUGENVENTANA
		//ABRO EL ARCHIVO. SI NO EXISTE LO CREO.
		std::ofstream archivoLog(pathDelArchivo, std::ios::out | std::ios::app);

		if (archivoLog.is_open()){

			archivoLog << FechayHora::obtenerUnicaInstancia()->obtenerFechayHoraActual() << " [" << toString(unModoDeLog) << "] " << unMensaje << "\n";

			archivoLog.close();
		}
#endif
	}

}


std::string Log::toString(ModoDeLog unModoDeLog){

	switch (unModoDeLog)
	{
	case MODO_DEBUG: return "DEBUG";
	case MODO_WARNING: return "WARNING";
	case MODO_ERROR: return "ERROR";
	default: return "????";
	}

}

Log& Log::getInstancia() {

	static Log instancia;
	// Se garantiza que será destruido.
	// Se instancia en el primer uso.
	return instancia;

}


Log::~Log(){

#ifndef DEBUGENVENTANA
	//ABRO EL ARCHIVO. SI NO EXISTE LO CREO.
	std::ofstream archivoLog(pathDelArchivo, std::ios::out | std::ios::app);
	if (archivoLog.is_open()){
		archivoLog << "\n";
		archivoLog.close();
	}

#endif
	FechayHora::obtenerUnicaInstancia()->borrarUnicaInstacia();
}
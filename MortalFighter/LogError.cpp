#include "stdafx.h"
#include "LogError.h"

LogError* LogError::unicaInstancia = nullptr;


LogError::LogError(){

	inicializarLog();
	tipoDeLog = "ERROR";

}


LogError* LogError::obtenerUnicaInstancia(){

	if (unicaInstancia == nullptr) {
		unicaInstancia = new LogError();
	}

	return unicaInstancia;

}


LogError::~LogError(){

	destruirLog();
	delete unicaInstancia;

}
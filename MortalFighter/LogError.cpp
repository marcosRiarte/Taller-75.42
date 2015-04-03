#include "stdafx.h"
#include "LogError.h"

LogError* LogError::unicaInstancia = nullptr;


LogError::LogError(){

	tipoDeLog = "ERROR";

}


LogError* LogError::obtenerUnicaInstancia(){

	if (unicaInstancia == nullptr) {
		unicaInstancia = new LogError();
	}

	return unicaInstancia;

}


LogError::~LogError(){

	delete &pathDelArchivo;
	delete &tipoDeLog;
	delete unicaInstancia;

}
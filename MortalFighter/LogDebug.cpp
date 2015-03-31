#include "stdafx.h"
#include "LogDebug.h"

LogDebug* LogDebug::unicaInstancia = nullptr;

LogDebug::LogDebug(){

	inicializarLog();
	tipoDeLog = "DEBUG";

}


LogDebug* LogDebug::obtenerUnicaInstancia(){

	if (unicaInstancia == nullptr) {
		unicaInstancia = new LogDebug();
	}

	return unicaInstancia;

}


LogDebug::~LogDebug(){

	destruirLog();
	delete unicaInstancia;

}
#include "stdafx.h"
#include "LogWarning.h"

LogWarning* LogWarning::unicaInstancia = nullptr;


LogWarning::LogWarning(){

	tipoDeLog = "WARNING";

}


LogWarning* LogWarning::obtenerUnicaInstancia(){

	if (unicaInstancia == nullptr) {
		unicaInstancia = new LogWarning();
	}

	return unicaInstancia;

}


LogWarning::~LogWarning(){

	delete &pathDelArchivo;
	delete &tipoDeLog;
	delete unicaInstancia;

}
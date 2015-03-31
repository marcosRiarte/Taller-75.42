#include "stdafx.h"
#include "Log.h"
#include <fstream>

void Log::inicializarLog() {

	pathDelArchivo = "log.txt";
	fechaYhoraActual = new FechayHora();

}


void Log::logear(std::string mensaje){

	std::ofstream archivoLog(pathDelArchivo, std::ios::out | std::ios::app);
	if (archivoLog.is_open()){
		archivoLog << fechaYhoraActual->obtenerFechayHoraActual() << " [" << tipoDeLog << "] " << mensaje << "\n";
		archivoLog.close();
	}

}


void Log::destruirLog(){

	delete fechaYhoraActual;
	delete &pathDelArchivo;
	delete &tipoDeLog;

}


Log::~Log(){

	destruirLog();

}
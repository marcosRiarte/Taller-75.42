#include "stdafx.h"
#include "Log.h"
#include <fstream>
#include "FechayHora.h"

 std::string Log::pathDelArchivo = "log.txt";


 Log::Log(){
 
	 modoActual = MODO_DEBUG;

	 //ABRO EL ARCHIVO. SI NO EXISTE LO CREO.
	 std::ofstream archivoLog(pathDelArchivo, std::ios::out | std::ios::app);
	 if (archivoLog.is_open()){
		 archivoLog << "---------------------------------------------------------------------------------" << "\n" <<"\n";
		 archivoLog.close();
	 }

 }


 void Log::setModoDeLog(ModoDeLog unModoDeLog){

	 modoActual = unModoDeLog;

 }


 void Log::logearMensajeEnModo(std::string unMensaje, ModoDeLog unModoDeLog){

	 if (unModoDeLog >= modoActual){
		 //ABRO EL ARCHIVO. SI NO EXISTE LO CREO.
		 std::ofstream archivoLog(pathDelArchivo, std::ios::out | std::ios::app);

		 if (archivoLog.is_open()){
			 archivoLog << FechayHora::obtenerUnicaInstancia()->obtenerFechayHoraActual() << " [" << toString(unModoDeLog) << "] " << unMensaje << "\n";
			 archivoLog.close();
		 }

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


Log::~Log(){

	//ABRO EL ARCHIVO. SI NO EXISTE LO CREO.
	std::ofstream archivoLog(pathDelArchivo, std::ios::out | std::ios::app);
	if (archivoLog.is_open()){
		archivoLog << "\n";
		archivoLog.close();
	}

}
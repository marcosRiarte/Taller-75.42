#include "stdafx.h"
#include "Log.h"
#include <fstream>
#include "FechayHora.h"
#include "MortalFigther.h"




 std::string Log::pathDelArchivo = "log.txt";


 Log::Log(){
 
	 modoActual = MODO_DEBUG;

	 //ABRO EL ARCHIVO. SI NO EXISTE LO CREO.
	 std::ofstream archivoLog(pathDelArchivo, std::ios::out | std::ios::app);
	 if (archivoLog.is_open()){

		#ifndef DEBUGENVENTANA
			archivoLog << "---------------------------------------------------------------------------------" << "\n" <<"\n";
		#endif
		 //si esta definido lo imprimo por pantalla
		#ifdef DEBUGENVENTANA
			 cout << "---------------------------------------------------------------------------" << "\n" << "\n";
		#endif
		 
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

			 
			#ifndef DEBUGENVENTANA
			 archivoLog << FechayHora::obtenerUnicaInstancia()->obtenerFechayHoraActual() << " [" << toString(unModoDeLog) << "] " << unMensaje << "\n";
			 #endif
			//si esta definido lo imprimo por pantalla
			#ifdef DEBUGENVENTANA
			 cout << FechayHora::obtenerUnicaInstancia()->obtenerFechayHoraActual()  << " [" << toString(unModoDeLog) << "] " << unMensaje << "\n";
		 	#endif

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

 Log& Log::getInstancia() {

	 static Log instancia;
	 // Se garantiza que ser� destruido.
	 // Se instancia en el primer uso.
	 return instancia;

 }


Log::~Log(){

	//ABRO EL ARCHIVO. SI NO EXISTE LO CREO.
	std::ofstream archivoLog(pathDelArchivo, std::ios::out | std::ios::app);
	if (archivoLog.is_open()){
		archivoLog << "\n";
		archivoLog.close();
	}
	FechayHora::obtenerUnicaInstancia()->borrarUnicaInstacia();

}
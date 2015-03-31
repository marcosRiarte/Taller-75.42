#pragma once
#include <string>
#include "FechayHora.h"

class Log {

	protected:
		std::string pathDelArchivo;
		FechayHora* fechaYhoraActual;
		std::string tipoDeLog;
		
	public:
		void logear(std::string mensaje);
		void inicializarLog();
		void destruirLog();
		~Log();

};
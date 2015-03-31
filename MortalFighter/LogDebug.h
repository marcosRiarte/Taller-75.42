#pragma once
#include "Log.h"

class LogDebug : public Log {

	public:
		static LogDebug* obtenerUnicaInstancia();
		~LogDebug();

	private:
		static LogDebug* unicaInstancia;

		LogDebug();

};


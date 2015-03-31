#pragma once
#include "Log.h"

class LogError : public Log {

	public:
		static LogError* obtenerUnicaInstancia();
		~LogError();

	private:
		static LogError* unicaInstancia;

		LogError();

};
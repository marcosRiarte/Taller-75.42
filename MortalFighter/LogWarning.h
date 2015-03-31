#pragma once
#include "Log.h"

class LogWarning : public Log{

	public:
		static LogWarning* obtenerUnicaInstancia();
		~LogWarning();

	private:
		static LogWarning* unicaInstancia;

		LogWarning();

};


#pragma once

#include <string>
#include <time.h>

class FechayHora {

	private:
		static FechayHora* unicaInstancia;

		FechayHora();

	public:
		static FechayHora* obtenerUnicaInstancia();
		const std::string obtenerFechayHoraActual();
		~FechayHora();

};
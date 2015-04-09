#pragma once

#include <string>
#include <time.h>

class FechayHora {

	private:
		static FechayHora* unicaInstancia;

		FechayHora();
		~FechayHora();

	public:
		static FechayHora* obtenerUnicaInstancia();
		const std::string obtenerFechayHoraActual();
		void borrarUnicaInstacia();

};
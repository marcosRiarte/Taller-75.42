#pragma once
#include <string>

class Log {

	protected:
		static std::string pathDelArchivo;

		void logearMensaje(std::string unMensaje);
		
	public:
		enum ModoDeLog{ MODO_DEBUG, MODO_WARNING, MODO_ERROR };

		static Log& getInstancia();

		
		void setModoDeLog(ModoDeLog unModoDeLog);
		void logearMensajeEnModo(std::string unMensaje, ModoDeLog unModoDeLog);
		~Log();

	private:
		std::string toString(ModoDeLog unModoDeLog);
		//Constructor privado
		explicit Log();
		ModoDeLog modoActual;

};
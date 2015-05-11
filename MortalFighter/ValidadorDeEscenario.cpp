#include "stdafx.h"
#include "ValidadorDeEscenario.h"


ValidadorDeEscenario::ValidadorDeEscenario()
{
	escenario = new Escenario(ANCHO_ESCENARIO, ALTO_ESCENARIO, Y_PISO_ESCENARIO);
}


void ValidadorDeEscenario::validarEscenarioDesde(Json::Value unEscenario){
	float anchoEscenario;
	float altoEscenario;
	float yPisoEscenario;

	if (!unEscenario){
		Log::getInstancia().logearMensajeEnModo("  [BAD] Fallo el parseo del escenario", Log::MODO_WARNING);
		Log::getInstancia().logearMensajeEnModo("Se cargaron valores del escenario por defecto", Log::MODO_WARNING);
		return;
	}
	else{
		if (unEscenario.isMember("ancho") && unEscenario.get("ancho", ANCHO_ESCENARIO).isNumeric() && unEscenario.get("ancho", ANCHO_ESCENARIO) < MAX_ANCHO_ESCENARIO){
			anchoEscenario = (unEscenario.get("ancho", ANCHO_ESCENARIO).asFloat());
			if (!(anchoEscenario > 0)) {
				std::string mensaje = "ancho del Escenario fuera de rango, se toma ancho por defecto";
				Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
			}
			else{
				escenario->setAncho(anchoEscenario);
			}

		}
		else {
			Log::getInstancia().logearMensajeEnModo("Se carga ancho del escenario por defecto", Log::MODO_WARNING);
		}

		if (unEscenario.isMember("alto") && unEscenario.get("alto", ALTO_ESCENARIO).isNumeric() && unEscenario.get("alto", ALTO_ESCENARIO) < MAX_ALTO_ESCENARIO){
			altoEscenario = (unEscenario.get("alto", ALTO_ESCENARIO).asFloat());
			if (!(altoEscenario > 0)) {
				std::string mensaje = "alto del Escenario fuera de rango, se toma alto por defecto";
				Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
			}
			else{
				escenario->setAlto(altoEscenario);
			}
		}
		else {
			Log::getInstancia().logearMensajeEnModo("Se carga alto del escenario por defecto", Log::MODO_WARNING);
		}

		if (unEscenario.isMember("ypiso") && unEscenario.get("ypiso", Y_PISO_ESCENARIO).isNumeric() && unEscenario.get("ypiso", Y_PISO_ESCENARIO) < MAX_ALTO_ESCENARIO){
			yPisoEscenario = (unEscenario.get("ypiso", Y_PISO_ESCENARIO).asFloat());
			escenario->setYPiso(yPisoEscenario);
		}
		else {
			Log::getInstancia().logearMensajeEnModo("Se carga piso del escenario por defecto", Log::MODO_WARNING);
		}

	}

}

void ValidadorDeEscenario::validaryPisoCon(float altoPersonaje){
	if ((escenario->getYPiso() < 0) || (escenario->getYPiso() > (escenario->getAlto() - altoPersonaje))) {
		std::string mensaje = "yPiso del Escenario fuera de rango, se yPiso por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		escenario->setYPiso(Y_PISO_ESCENARIO);
	}
	Log::getInstancia().logearMensajeEnModo("Se cargaron valores del escenario correctamente", Log::MODO_DEBUG);
}


Escenario* ValidadorDeEscenario::getEscenario(){
	return escenario;
}


ValidadorDeEscenario::~ValidadorDeEscenario()
{
	delete escenario;
}

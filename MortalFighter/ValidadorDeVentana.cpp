#include "stdafx.h"
#include "wtypes.h"
#include "ValidadorDeVentana.h"


ValidadorDeVentana::ValidadorDeVentana()
{
	ventana = new Ventana(ANCHO_PX_VENTANA, ALTO_PX_VENTANA, ANCHO_VENTANA);
}


void ValidadorDeVentana::validarVentanaDesde(Json::Value unaVentana){
	int anchoPxVentana;
	int altoPxVentana;
	float anchoVentana;

	RECT escritorio;
	// Un manejador 
	const HWND tam = GetDesktopWindow();
	// tomar el tamanio
	GetWindowRect(tam, &escritorio);
	int horizontal = escritorio.right;
	int vertical = escritorio.bottom;

	if (!unaVentana){
		Log::getInstancia().logearMensajeEnModo("  [BAD] Fallo el parseo de la ventana", Log::MODO_WARNING);
		Log::getInstancia().logearMensajeEnModo("Se cargaron valores de la ventana por defecto", Log::MODO_WARNING);
		return;
	}
	else{
		//3 comprobaciones, que exista el campo, que sea un numero y que no exceda el maximo
		if (unaVentana.isMember("anchopx") && unaVentana.get("anchopx", ANCHO_PX_VENTANA).isNumeric() && ((unaVentana.get("anchopx", ANCHO_PX_VENTANA) < INT_MAX) && (unaVentana.get("anchopx", ANCHO_PX_VENTANA) >= ANCHO_MIN))){
			anchoPxVentana = (unaVentana.get("anchopx", ANCHO_PX_VENTANA).asInt());

			if (!((anchoPxVentana > 0) && (anchoPxVentana < horizontal))) {
				std::string mensaje = "ancho de Ventana fuera de rango, se toma ancho Px ventana por defecto";
				Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
			}
			else{
				ventana->setAnchoPx(anchoPxVentana);
			}

		}
		else {
			Log::getInstancia().logearMensajeEnModo("Se carga anchopx de la ventana por defecto", Log::MODO_WARNING);
		}

		if (unaVentana.isMember("altopx") && unaVentana.get("altopx", ALTO_PX_VENTANA).isNumeric() && ((unaVentana.get("altopx", ALTO_PX_VENTANA) < INT_MAX) && (unaVentana.get("altopx", ALTO_PX_VENTANA) >= ALTO_MIN))){
			altoPxVentana = (unaVentana.get("altopx", ALTO_PX_VENTANA).asInt());

			if (!((altoPxVentana > 0) && (altoPxVentana < vertical))) {
				std::string mensaje = "alto de Ventana fuera de rango, se toma alto Px ventana por defecto";
				Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
			}
			else{
				ventana->setAltoPx(altoPxVentana);
			}

		}
		else {
			Log::getInstancia().logearMensajeEnModo("Se carga altopx de la ventana por defecto", Log::MODO_WARNING);
		}

		if (unaVentana.isMember("ancho") && unaVentana.get("ancho", ANCHO_VENTANA).isNumeric() && unaVentana.get("ancho", ANCHO_VENTANA) < INT_MAX){
			anchoVentana = (unaVentana.get("ancho", ANCHO_VENTANA).asFloat());

			if (!(anchoVentana > 0)) {
				std::string mensaje = "anchoUn de Ventana fuera de rango, se toma ancho en unidades por defecto";
				Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
			}

			else{
				ventana->setAncho(anchoVentana);
			}
		}
		else {
			Log::getInstancia().logearMensajeEnModo("Se carga ancho de la ventana por defecto", Log::MODO_WARNING);
		}

	}
	Log::getInstancia().logearMensajeEnModo("Se cargaron valores de la ventana correctamente", Log::MODO_DEBUG);
}


Ventana* ValidadorDeVentana::getVentana(){
	return ventana;
}


ValidadorDeVentana::~ValidadorDeVentana()
{
	delete ventana;
}

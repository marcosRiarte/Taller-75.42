#include "stdafx.h"
#include "Validador.h"
#include "wtypes.h"
#include <iostream>

void Validador::ValidarVentana(int* anchoPxVentana, int* altoPxVentana, float* anchoVentana) {
	RECT escritorio;
	// Un manejador 
	const HWND tam = GetDesktopWindow();
	// tomar el tamanio
	GetWindowRect(tam, &escritorio);
	int horizontal = escritorio.right;
	int vertical = escritorio.bottom;

	if (!((*anchoPxVentana > 0) && (*anchoPxVentana < horizontal))) {
		std::string mensaje = "ancho de Ventana fuera de rango, se toma ancho Px ventana por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*anchoPxVentana = 800;
	}

	if (!((*altoPxVentana > 0) && (*altoPxVentana < vertical))) {
		std::string mensaje = "alto de Ventana fuera de rango, se toma alto Px ventana por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*altoPxVentana = 600;
	}

	if (!(*anchoVentana > 0)) {
		std::string mensaje = "anchoUn de Ventana fuera de rango, se toma ancho en unidades por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*anchoVentana = 200;
	}
}

void Validador::ValidarCapas(float *anchoCapa){
	if (!(*anchoCapa > 0)){
		std::string mensaje = "ancho de Capa fuera de rango, se toma ancho por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*anchoCapa = 500;
	}
		
}

void Validador::ValidarEscenario(float *anchoEscenario, float *altoEscenario, float* yPisoEscenario){
	if (!(*anchoEscenario > 0)) {
		std::string mensaje = "ancho del Escenario fuera de rango, se toma ancho por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*anchoEscenario = 1000.5;
	}
	if (!(*altoEscenario > 0)) {
		std::string mensaje = "alto del Escenario fuera de rango, se toma alto por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*anchoEscenario = 150;
	}
	if (!((*yPisoEscenario > 0) && (*yPisoEscenario < *altoEscenario))) {
		std::string mensaje = "yPiso del Escenario fuera de rango, se yPiso por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*yPisoEscenario = 20;
	}
}

void Validador::ValidarPersonaje(float *ancho, float* alto, int* zindex, std::string* orientacion, std::string* sprites){
	if (!(*ancho > 0)) {
		std::string mensaje = "ancho del Personaje fuera de rango, se toma ancho por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*ancho = 23.5;
	}
	if (!(*alto > 0)) {
		std::string mensaje = "alto del Personaje fuera de rango, se toma alto por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*alto = 49;
	}
	if (!(*zindex >= 0)) {
		std::string mensaje = "zindex del Personaje fuera de rango, se toma zindex por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*zindex = 1;
	}
	if ((*orientacion != "DER") && (*orientacion != "IZQ")) {
		std::string mensaje = "orientacion invalida, se toma orientacion derecha";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*orientacion = "DER";
	}
	if ((*sprites == "")) {
		std::string mensaje = "string de sprites vacio, se toma sprites por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*sprites = "mario2.png";
	}
}
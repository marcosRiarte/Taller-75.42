#include "stdafx.h"
#include "Validador.h"
#include <iostream>

bool Validador::ValidarPersonaje(float *ancho, float* alto, int* zindex, std::string* orientacion, std::string* sprites, std::string* CaminarParaAdelante, std::string* CaminarParaAtras, std::string* Quieto, std::string* Salto, std::string* SaltoDiagonal, std::string* Caida){
	if (!(*ancho > 0) || *ancho > MAX_ANCHO_PERSONAJE) {
		std::string mensaje = "ancho del Personaje fuera de rango, se toma ancho por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*ancho = ANCHO_PERSONAJE;
	}
	if (!(*alto > 0) || *alto > MAX_ALTO_PERSONAJE) {
		std::string mensaje = "alto del Personaje fuera de rango, se toma alto por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*alto = ALTO_PERSONAJE;
	}	
	if ((*orientacion != "DER") && (*orientacion != "IZQ")) {
		std::string mensaje = "orientacion invalida, se toma orientacion derecha";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*orientacion = ORIENTACION_PERSONAJE;
	}

	const char * archivoPersonaje = sprites->c_str(); //casteo
	FILE * pFile;
	fopen_s(&pFile, archivoPersonaje, "r");

	if (pFile != NULL) //si me devolvio puntero existe, cerralo!!!!!
	{
		fclose(pFile);
	}
	else // el archivo no existe!
	{	
		std::string mensaje = "sprites no existentes, se toman sprites por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*sprites = SPRITE_DEFAULT;
		const char * archivoPersonaje = sprites->c_str(); //casteo
		FILE * pFile;
		fopen_s(&pFile, archivoPersonaje, "r");

		if (pFile == NULL) //si me devolvio puntero existe, cerralo!!!!!
		{
			Log::getInstancia().logearMensajeEnModo("sprites por defecto no existentes, se cerrara el programa...", Log::MODO_ERROR);
			return true;
			
		}
		else fclose(pFile);
	}
	
	if ((*CaminarParaAdelante != "CaminarParaAdelante") && (*CaminarParaAdelante != "CaminarParaAtras") && (*CaminarParaAdelante != "Quieto") && (*CaminarParaAdelante != "Salto") && (*CaminarParaAdelante != "SaltoDiagonal") && (*CaminarParaAdelante != "Caida")) {
		std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto Caminar Para Adelante";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		
		*CaminarParaAdelante = CAMINARPARAADELANTE_DEFAULT;
	}
	if ((*CaminarParaAtras != "CaminarParaAdelante") && (*CaminarParaAtras != "CaminarParaAtras") && (*CaminarParaAtras != "Quieto") && (*CaminarParaAtras != "Salto") && (*CaminarParaAtras != "SaltoDiagonal") && (*CaminarParaAtras != "Caida")) {
		std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto Caminar Para Atras";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		
		*CaminarParaAtras = CAMINARPARAATRAS_DEFAULT;
	}
	if ((*Quieto != "CaminarParaAdelante") && (*Quieto != "CaminarParaAtras") && (*Quieto != "Quieto") && (*Quieto != "Salto") && (*Quieto != "SaltoDiagonal") && (*Quieto != "Caida")) {
		std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto Quieto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		
		*Quieto = QUIETO_DEFAULT;
	}
	if ((*Salto != "CaminarParaAdelante") && (*Salto != "CaminarParaAtras") && (*Salto != "Quieto") && (*Salto != "Salto") && (*Salto != "SaltoDiagonal") && (*Salto != "Caida")) {
		std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto Salto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		
		*Salto = SALTO_DEFAULT;
	}
	if ((*SaltoDiagonal != "CaminarParaAdelante") && (*SaltoDiagonal != "CaminarParaAtras") && (*SaltoDiagonal != "Quieto") && (*SaltoDiagonal != "Salto") && (*SaltoDiagonal != "SaltoDiagonal") && (*SaltoDiagonal != "Caida")) {
		std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto Salto Diagonal";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		
		*SaltoDiagonal = SALTODIAGONAL_DEFAULT;
	}
	if ((*Caida != "CaminarParaAdelante") && (*Caida != "CaminarParaAtras") && (*Caida != "Quieto") && (*Caida != "Salto") && (*Caida != "SaltoDiagonal") && (*Caida != "Caida")) {
		std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto Caida";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		
		*Caida = CAIDA_DEFAULT;
	}
	return false;
}

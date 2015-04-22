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
		*anchoPxVentana = ANCHO_PX_VENTANA;
	}

	if (!((*altoPxVentana > 0) && (*altoPxVentana < vertical))) {
		std::string mensaje = "alto de Ventana fuera de rango, se toma alto Px ventana por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*altoPxVentana = ALTO_PX_VENTANA;
	}

	if (!(*anchoVentana > 0)) {
		std::string mensaje = "anchoUn de Ventana fuera de rango, se toma ancho en unidades por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*anchoVentana = ANCHO_VENTANA;
	}
}

bool Validador::ValidarCapas(float *anchoCapa, std::string *fondo, size_t numerocapa){
	if (!(*anchoCapa > 0)){
		
		std::string mensaje = "ancho de Capa " + std::to_string(numerocapa) + " fuera de rango, se toma ancho por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*anchoCapa = ANCHO_CAPA;
	}

	
	//  intento abrir el archivo, si el puntero devuelto es NULL NO EXISTE EL ARCHIVO  
	const char * archivofondo = fondo->c_str(); //casteo
	FILE * pFile; 
	fopen_s(&pFile, archivofondo, "r");

	if (pFile != NULL) //si me devolvio puntero existe, cerralo!!!!!
	{
		fclose(pFile);
	}
	else // el archivo no existe!
	{
		std::string mensaje = "No existe la capa " + std::to_string(numerocapa) + " , se usa capa por defecto";
	    Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		
		*fondo = FONDO_DEFAULT;
		const char * archivofondo = fondo->c_str(); //casteo
		FILE * pFile;
		fopen_s(&pFile, archivofondo, "r");

		if (pFile == NULL) //si me devolvio puntero existe, cerralo!!!!!
		{
			Log::getInstancia().logearMensajeEnModo("no existe el fondo por defecto, el juego se cargara sin fondo", Log::MODO_ERROR);
			return false;
		}
		else fclose(pFile);
	}
	return true;
}

		


void Validador::ValidarEscenario(float *anchoEscenario, float *altoEscenario, float *altoPersonaje, float* yPisoEscenario){
	if (!(*anchoEscenario > 0)) {
		std::string mensaje = "ancho del Escenario fuera de rango, se toma ancho por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*anchoEscenario = ANCHO_ESCENARIO;
	}
	if (!(*altoEscenario > 0)) {
		std::string mensaje = "alto del Escenario fuera de rango, se toma alto por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*altoEscenario = ALTO_ESCENARIO;
	}
	if (((*yPisoEscenario < 0) || (*yPisoEscenario > *altoEscenario - *altoPersonaje))) {
		std::string mensaje = "yPiso del Escenario fuera de rango, se yPiso por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*yPisoEscenario = Y_PISO_ESCENARIO;
	}
}


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
			Log::getInstancia().logearMensajeEnModo("sprites por defecto no existentes, no se mostrara el personaje", Log::MODO_ERROR);
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

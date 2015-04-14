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
//xjose 1000 1001 agrego el parametro fondo para validad que exista

void Validador::ValidarCapas(float *anchoCapa, std::string *fondo){
	if (!(*anchoCapa > 0)){
		std::string mensaje = "ancho de Capa fuera de rango, se toma ancho por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*anchoCapa = 500;
	}
	//xjose 1001 WARNING WARNING WARNIG..... Recodificar mas elegante
	
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
		std::string mensaje = "No existe la capa, se usa capa por defecto";
	    Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		//xjose1000 esto esta muy mal harcodeado tiene que decirmelo una constante en un #define cual es la defecto
		//xjose 1000 HARDCODEO HARCODEO WARNING WARNING ESTA MAL!!!!!!!!!!!!!! CAMBIAR LUNA POR UN DEFINE
		*fondo = FONDO_DEFAULT;
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

//Xjose aca el validador, en caso de fallar esta poniendole un dato valido... esto no se hacia en otra parte ya?? en la parte de parser??? revisar
void Validador::ValidarPersonaje(float *ancho, float* alto, int* zindex, std::string* orientacion, std::string* sprites, std::string* CaminarParaAdelante, std::string* CaminarParaAtras, std::string* Quieto, std::string* Salto, std::string* SaltoDiagonal, std::string* Caida){
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
	//Xjose 7 modifico validador... uff!!!!! OK si me pongo en hincha p.... tendria que cambiar el orden de los && seguen sea
	if ((*CaminarParaAdelante != "CaminarParaAdelante") && (*CaminarParaAdelante != "CaminarParaAtras") && (*CaminarParaAdelante != "Quieto") && (*CaminarParaAdelante != "Salto") && (*CaminarParaAdelante != "SaltoDiagonal") && (*CaminarParaAdelante != "Caida")) {
		std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		//Xjose mmmm si harcodeo aca para que use el #define CAMINARPARAADELANTE_DEFAULT ??????????
		*CaminarParaAdelante = "CaminarParaAdelante";
	}
	if ((*CaminarParaAtras != "CaminarParaAdelante") && (*CaminarParaAtras != "CaminarParaAtras") && (*CaminarParaAtras != "Quieto") && (*CaminarParaAtras != "Salto") && (*CaminarParaAtras != "SaltoDiagonal") && (*CaminarParaAtras != "Caida")) {
		std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		//Xjose mmmm si harcodeo aca para que use el #define CAMINARPARAADELANTE_DEFAULT ??????????
		*CaminarParaAtras = "CaminarParaAtras";
	}
	if ((*Quieto != "CaminarParaAdelante") && (*Quieto != "CaminarParaAtras") && (*Quieto != "Quieto") && (*Quieto != "Salto") && (*Quieto != "SaltoDiagonal") && (*Quieto != "Caida")) {
		std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		//Xjose mmmm si harcodeo aca para que use el #define CAMINARPARAADELANTE_DEFAULT ??????????
		*Quieto = "Quieto";
	}
	if ((*Salto != "CaminarParaAdelante") && (*Salto != "CaminarParaAtras") && (*Salto != "Quieto") && (*Salto != "Salto") && (*Salto != "SaltoDiagonal") && (*Salto != "Caida")) {
		std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		//Xjose mmmm si harcodeo aca para que use el #define CAMINARPARAADELANTE_DEFAULT ??????????
		*Salto = "Salto";
	}
	if ((*SaltoDiagonal != "CaminarParaAdelante") && (*SaltoDiagonal != "CaminarParaAtras") && (*SaltoDiagonal != "Quieto") && (*SaltoDiagonal != "Salto") && (*SaltoDiagonal != "SaltoDiagonal") && (*SaltoDiagonal != "Caida")) {
		std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		//Xjose mmmm si harcodeo aca para que use el #define CAMINARPARAADELANTE_DEFAULT ??????????
		*SaltoDiagonal = "SaltoDiagonal"; 
	}
	if ((*Caida != "CaminarParaAdelante") && (*Caida != "CaminarParaAtras") && (*Caida != "Quieto") && (*Caida != "Salto") && (*Caida != "SaltoDiagonal") && (*Caida != "Caida")) {
		std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		//Xjose mmmm si harcodeo aca para que use el #define CAMINARPARAADELANTE_DEFAULT ??????????
		*Caida = "Caida";
	}
}
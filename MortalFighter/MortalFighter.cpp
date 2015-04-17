// MortalFighter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parser.h"
#include "Vista.h"
#include "Mundo.h"
#include <windows.h>
#include "Controlador.h"
#include "MortalFigther.h"




//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
int _tmain(int argc, _TCHAR* argv[])
{	

	#ifdef DEBUGENVENTANA
			cout << "Esta activado el modo DEBUG EN VENTANA, se registra solo por consola" << "\n";
	#endif


	MOV_TIPO movimiento = RECARGAR;
	while (movimiento == RECARGAR){
		std::string nombreArchivo(PRUEBA_JSON);
		bool ParseoExitoso= Parser::getInstancia().parsear(nombreArchivo);
		
		if (!ParseoExitoso) return 1; //si el json por defecto fallo, el programa termina

		vector2D vecGravedad(0.0f, GRAVEDAD_Y);

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
			const char* msg = ((std::string)"Error iniciando SDL: ").append(SDL_GetError()).c_str();
		}
		//Parte de creación inicial.
		Vista* unaVista = new Vista();
		Mundo* unMundo = new Mundo(vecGravedad);
		Cuerpo *unCuerpo = new Cuerpo(defCuerpo());
		unMundo->agregarCuerpo(unCuerpo);

		//Gameloop
		while (true) {
			movimiento = Controlador::cambiar();
			if ((movimiento == CERRAR) || (movimiento == RECARGAR))
				break;

			unMundo->Paso(0.13f, movimiento);

			unaVista->actualizar(movimiento, Parser::getInstancia().getPersonaje().getEstado()); //Nescesita pasarle el personaje y su estado

			SDL_Delay(10);

		}
		delete unaVista;
		delete unMundo;
		delete unCuerpo;
		Parser::FreeInstancia();
		
		SDL_Quit();
		
	}



	return 0;
}


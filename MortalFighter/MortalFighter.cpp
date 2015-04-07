// MortalFighter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parser.h"
#include "Vista.h"
#include "Mundo.h"
//#include <windows.h>
#include "Controlador.h"


//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
int _tmain(int argc, _TCHAR* argv[])
{
	std::string nombreArchivo("prueba.json");
	Parser::getInstancia().parsear(nombreArchivo);
	vector2D vecGravedad(0.0f, GRAVEDAD_Y);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		const char* msg = ((std::string)"Error iniciando SDL: ").append(SDL_GetError()).c_str();
	}
	//Parte de creaci�n inicial.
	Vista* unaVista = new Vista();
	Mundo* unMundo = new Mundo(vecGravedad);
	Cuerpo *unCuerpo = new Cuerpo(defCuerpo());
	unMundo->agregarCuerpo(unCuerpo);
	
	//Gameloop
	while (true) {
		MOV_TIPO movimiento = Controlador::cambiar();
		if (movimiento == CERRAR)
			break;

		unMundo->Paso(0.35f, movimiento);

		unaVista->actualizar();
		
		SDL_Delay(30);
			
	}

	return 0;
}


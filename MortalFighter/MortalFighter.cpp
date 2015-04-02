// MortalFighter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parser.h"
#include "Vista.h"
#include "Mundo.h"
#include <windows.h>
#include "Controlador.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{

	std::string nombreArchivo("prueba.json");
	Parser::getInstancia().parsear(nombreArchivo);
	vector2D vecGravedad(0.0f, GRAVEDAD_Y);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		const char* msg = ((std::string)"Error iniciando SDL: ").append(SDL_GetError()).c_str();
	}
	//Parte de creación inicial.
	Vista* unaVista = new Vista();
	Mundo* unMundo = new Mundo(vecGravedad);
	unMundo->agregarCuerpo(Cuerpo(&defCuerpo()));
	
	//Gameloop
	while (true) {
		unMundo->Paso(0.001f, Controlador::cambiar());

		unaVista->actualizar(Controlador::cambiar());
		
		SDL_Delay(100);
		break;
	}

	return 0;
}


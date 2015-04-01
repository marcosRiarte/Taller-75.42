// MortalFighter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parser.h"
#include "Vista.h"
#include "Mundo.h"
#include <windows.h>

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{

	std::string nombreArchivo("prueba.json");
	Parser::getInstancia().parsear(nombreArchivo);
	vector2D vecGravedad(0.0f, GRAVEDAD_Y);

	Vista* unaVista = new Vista();
	Mundo* unMundo = new Mundo(vecGravedad);
	unMundo->agregarCuerpo(Cuerpo(&defCuerpo()));


	// Prueba Parser, imprimir ancho de escenario
	std::ostringstream entradaCadena;
	entradaCadena << Parser::getInstancia().getEscenario().getAncho();
	std::string ancho(entradaCadena.str());	
	std::cout << "Ancho de Escenario: " << ancho << std::endl;

	return 0;
}


// MortalFighter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parser.h"
#include "Vista.h"
#include <windows.h>

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{

	std::string nombreArchivo("prueba.json");
	Parser::getInstancia().parsear(nombreArchivo);

	Vista* unaVista = new Vista(&Parser::getInstancia());

	// Prueba Parser, imprimir ancho de escenario
	std::ostringstream entradaCadena;
	entradaCadena << Parser::getInstancia().getEscenario().getAncho();
	std::string ancho(entradaCadena.str());	
	std::cout << "Ancho de Escenario: " << ancho << std::endl;

	return 0;
}


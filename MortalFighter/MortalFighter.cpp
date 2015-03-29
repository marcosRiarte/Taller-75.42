// MortalFighter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parser.h"
#include "Vista.h"


int _tmain(int argc, _TCHAR* argv[])
{

	Parser* unParser = new Parser("prueba.json");
	Vista* unaVista = new Vista(unParser);


	return 0;
}


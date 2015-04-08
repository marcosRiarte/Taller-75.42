#include "stdafx.h"
#include "FechayHora.h"

FechayHora* FechayHora::unicaInstancia = nullptr;


FechayHora::FechayHora(){}


FechayHora* FechayHora::obtenerUnicaInstancia(){

	if (unicaInstancia == nullptr){
		unicaInstancia = new FechayHora();
	}

	return unicaInstancia;

}


const std::string FechayHora::obtenerFechayHoraActual(){

	time_t horaActual;
	struct tm structHorayFechaActual;
	char horayFechaActualComoCadena[80];
	time(&horaActual);
	localtime_s(&structHorayFechaActual, &horaActual);
	strftime(horayFechaActualComoCadena, 80, "%Y-%m-%d.%X", &structHorayFechaActual);
	std::string horayFechaActualFinal(horayFechaActualComoCadena);
	return horayFechaActualFinal;

}

FechayHora::~FechayHora()
{
	delete unicaInstancia;
}
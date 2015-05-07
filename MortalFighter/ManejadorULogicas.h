#pragma once
#include "stdafx.h"
#include "Parser.h"

struct ManejadorULogicas
{
	ManejadorULogicas()
	{
		int longPx = Parser::getInstancia().getVentana().getAnchoPx();
		float longLog = Parser::getInstancia().getVentana().getAncho();

		relacion = longPx / longLog;
	}

	ManejadorULogicas(int longPx, float longLog)
	{
		relacion = longPx / longLog;
	}
	
	float darRelacion(int longPx, float longLog)
	{
		float relacionParticular = longPx / longLog;
		return relacionParticular;
	}

	std::pair<int, int>  obtenerPosicionPx(float xLog, float yLog)
	{
		int altoPx = Parser::getInstancia().getVentana().getAltoPx();
		float altoLog = Parser::getInstancia().getEscenario().getAlto();
		int yPx = altoPx - (int)round(darLongPixels(yLog, altoPx, altoLog));

		return std::make_pair((int)round(xLog * relacion), yPx);
	}

	int darLongPixels(float uLogicas)
	{
		return (int)round(uLogicas*relacion);
	}

	int darLongUnidades(int pixeles)
	{
		return (float)(pixeles/relacion);
	}

	
	int darLongPixels(float uLogicas, int longPx, float longLog)
	{
		float relacionParticular = darRelacion(longPx, longLog);
		return (int)round(uLogicas*relacionParticular);
	}


	float relacion;
};
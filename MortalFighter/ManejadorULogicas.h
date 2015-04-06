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
	
	std::pair<int, int>  obtenerPosicionPx(float xLog, float yLog)
	{
		int altoPx = Parser::getInstancia().getVentana().getAltoPx();
		int yPx = altoPx - (int)trunc(yLog * relacion);

		return std::make_pair((int)trunc(xLog * relacion), yPx);
	}

	int darLongPixels(float uLogicas)
	{
		return uLogicas*relacion;
	}
		

	float relacion;
};
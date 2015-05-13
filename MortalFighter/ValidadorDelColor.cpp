#include "stdafx.h"
#include "ValidadorDelColor.h"
#include "ControlDeColor.h"

ValidadorDelColor::ValidadorDelColor()
{
}

void ValidadorDelColor::validarColorDesde(Json::Value color_alternativo){
	int h_inicial = H_INICIAL;
	int h_final = H_FINAL;
	int desplazamiento = DESPLAZAMIENTO;
	ControlDeColor control = ControlDeColor();

	if (!color_alternativo)
	{
		Log::getInstancia().logearMensajeEnModo("[BAD] Fallo el parseo del color", Log::MODO_WARNING);
		Log::getInstancia().logearMensajeEnModo("se toman valores por defecto para el color", Log::MODO_WARNING);
	}

	else{
		if (color_alternativo.isMember("h_inicial") && color_alternativo.get("h_inicial", H_INICIAL).isNumeric() && color_alternativo.get("h_inicial", H_INICIAL) < INT_MAX && color_alternativo.get("h_inicial", H_INICIAL) > -INT_MAX)
			h_inicial = color_alternativo.get("h_inicial", H_INICIAL).asInt();
		else {
			Log::getInstancia().logearMensajeEnModo("Se carga HUE INICIAL por defecto", Log::MODO_WARNING);
		}
		if (color_alternativo.isMember("h_final") && color_alternativo.get("h_final", H_FINAL).isNumeric() && color_alternativo.get("h_final", H_FINAL) < INT_MAX && color_alternativo.get("h_final", H_FINAL) > -INT_MAX)
			h_final = color_alternativo.get("h_final", H_FINAL).asInt();
		else {
			Log::getInstancia().logearMensajeEnModo("Se carga HUE FINAL por defecto", Log::MODO_WARNING);
		}
		if (color_alternativo.isMember("desplazamiento") && color_alternativo.get("desplazamiento", DESPLAZAMIENTO).isNumeric() && color_alternativo.get("desplazamiento", DESPLAZAMIENTO) < INT_MAX && color_alternativo.get("desplazamiento", DESPLAZAMIENTO) > -INT_MAX)
			desplazamiento = color_alternativo.get("desplazamiento", DESPLAZAMIENTO).asInt();
		else {
			Log::getInstancia().logearMensajeEnModo("Se carga desplazamiento por defecto", Log::MODO_WARNING);
		}
		//Repara la h_inicial ,h_final y el desplazamiento de entrada si estos superan 360
		if (h_inicial > 360)
		{
			h_inicial = control.reductorDeVueltas(h_inicial);
			Log::getInstancia().logearMensajeEnModo("HUE Inicial MAYOR A 360 ,se corrije ", Log::MODO_WARNING);
		}
		if (h_final > 360)
		{
			h_final = control.reductorDeVueltas(h_final);
			Log::getInstancia().logearMensajeEnModo("HUE Final MAYOR A 360 ,se corrije ", Log::MODO_WARNING);
		}

		if (desplazamiento > 360)
		{
			desplazamiento = control.reductorDeVueltas(desplazamiento);
			Log::getInstancia().logearMensajeEnModo("DESPLAZAMIENTO MAYOR A 360 ,se corrije ", Log::MODO_WARNING);
		}

		//Si el dato de entrada tiene un valor negativo , toma el angulo en el sentido opuesto.

		if (h_inicial < 0)
		{
			h_inicial = 360 + (h_inicial);
			std::string mensaje = "H inicial negativo, se corrige 360 + el valor";
			Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		}
		if (h_final < 0)
		{
			h_final = 360 + (h_final);
			std::string mensaje = "H final negativo, se corrige 360 + el valor";
			Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		}

		if (h_final < h_inicial)
		{
			std::string mensaje = "Hue final menor que el inicial, se toma el modulo del intervalo";
			Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
			int aux = h_final;
			h_final = h_inicial;
			h_inicial = aux;
		}
		if (h_final == h_inicial)
		{
			Log::getInstancia().logearMensajeEnModo("Intervalo nulo de hue nulo, se toman valores por defecto", Log::MODO_WARNING);
			h_final = 0;
			h_inicial = 0;

		}
	}
	colorAlternativo.push_back(h_inicial);
	colorAlternativo.push_back(h_final);
	colorAlternativo.push_back(desplazamiento);
	Log::getInstancia().logearMensajeEnModo("Se cargaron valores del color correctamente", Log::MODO_DEBUG);
}

std::vector<int> ValidadorDelColor::getColorAlternativo(){
	return colorAlternativo;
}

ValidadorDelColor::~ValidadorDelColor()
{
	colorAlternativo.clear();
}

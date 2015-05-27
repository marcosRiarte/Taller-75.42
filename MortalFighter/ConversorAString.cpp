#include "stdafx.h"
#include "ConversorAString.h"


ConversorAString::ConversorAString()
{
}


std::string ConversorAString::getTeclaComoStringDelMovimientoParaElConversorDeEventos(MOV_TIPO unMovimiento, ConversorDeEventos* conversorDeEventos){
	if (unMovimiento != QUIETO){
		if (unMovimiento == SALTODER){
			return (conversorDeEventos->getSimboloDeLaAccion(ConversorDeEventos::UP) + "+" + conversorDeEventos->getSimboloDeLaAccion(ConversorDeEventos::RIGHT));
		}
		if (unMovimiento == SALTOIZQ){
			return (conversorDeEventos->getSimboloDeLaAccion(ConversorDeEventos::UP) + "+" + conversorDeEventos->getSimboloDeLaAccion(ConversorDeEventos::LEFT));
		}
		if (unMovimiento == G_ABAJO){
			return conversorDeEventos->getSimboloDeLaAccion(ConversorDeEventos::LOW_PUNCH);
		}
		if (unMovimiento == G_GANCHO){
			return conversorDeEventos->getSimboloDeLaAccion(ConversorDeEventos::HIGH_PUNCH);
		}
		if (unMovimiento == P_BAJA_ABAJO){
			return conversorDeEventos->getSimboloDeLaAccion(ConversorDeEventos::LOW_KICK);
		}
		if (unMovimiento == P_ALTA_ABAJO){
			return conversorDeEventos->getSimboloDeLaAccion(ConversorDeEventos::HIGH_KICK);
		}
		return conversorDeEventos->getSimboloDeLaAccion((ConversorDeEventos::Acciones)unMovimiento);
	}
	return "";
}


MOV_TIPO ConversorAString::getMovimientoParaElString(std::string unMovimiento){
	if (unMovimiento == "derecha" || unMovimiento == "Derecha"){
		return DER;
	}
	if (unMovimiento == "izquierda" || unMovimiento == "Izquierda"){
		return IZQ;
	}
	if (unMovimiento == "arriba" || unMovimiento == "Arriba"){
		return ARRIBA;
	}
	if (unMovimiento == "abajo" || unMovimiento == "Abajo"){
		return ABAJO;
	}
	if (unMovimiento == "GB" || unMovimiento == "gb"){
		return G_BAJO;
	}
	if (unMovimiento == "GA" || unMovimiento == "ga"){
		return G_ALTO;
	}
	if (unMovimiento == "PA" || unMovimiento == "pa"){
		return P_ALTA;
	}
	if (unMovimiento == "PB" || unMovimiento == "pb"){
		return P_BAJA;
	}
	if (unMovimiento == "Arma" || unMovimiento == "arma"){
		return ARMA;
	}
	if (unMovimiento == "Defensa" || unMovimiento == "defensa"){
		return DEFENSA;
	}
	return QUIETO;
}


ConversorAString::~ConversorAString()
{
}

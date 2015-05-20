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


ConversorAString::~ConversorAString()
{
}

#include "stdafx.h"
#include "ValidadorDeTomas.h"
#include "ConversorAString.h"

ValidadorDeTomas::ValidadorDeTomas()
{
	vecMovimientos = std::vector<MOV_TIPO>();
	vecMovimientos.push_back(DER);
	vecMovimientos.push_back(IZQ);
	vecMovimientos.push_back(G_ALTO);
}


void ValidadorDeTomas::validarTomasDeseParaControladorDeTomas(Json::Value tomas, ControladorDeTomas* controladorDeTomas){
	if (!tomas || (tomas.size() == 0)){
		Log::getInstancia().logearMensajeEnModo("  [BAD] Fallo el parseo de las tomas", Log::MODO_WARNING);
		Log::getInstancia().logearMensajeEnModo("Se cargan tomas por defecto", Log::MODO_WARNING);
		return;
	}
	
	Toma* unaToma = new Toma();
	std::stringstream stream;

	for (size_t i = 0; i < tomas.size(); i++){
		stream << i;
		unaToma->setNombre("Toma " + stream.str());
		
		//NOMBRE
		if (tomas[i].isMember("nombre") && tomas[i].get("nombre", "Toma 1").isString()){
			unaToma->setNombre(tomas[i].get("nombre", "Toma 1").asString());
		}
		else Log::getInstancia().logearMensajeEnModo("Se carga nombre de la toma por defecto", Log::MODO_WARNING);
		
		//ERROR
		if (tomas[i].isMember("error") && tomas[i].get("error", 0).isNumeric()){
			unaToma->setError(tomas[i].get("error", 0).asInt());
		}
		else Log::getInstancia().logearMensajeEnModo("Se carga error de la toma por defecto", Log::MODO_WARNING);
		
		//TIEMPO
		if (tomas[i].isMember("tiempo") && tomas[i].get("tiempo", 2000).isNumeric()){
			unaToma->setTiempo(tomas[i].get("tiempo", 2000).asInt());
		}
		else Log::getInstancia().logearMensajeEnModo("Se carga tiempo de la toma por defecto", Log::MODO_WARNING);
		
		//MOVIMIENTOS
		if (tomas[i].isMember("movimientos")){
			
			Json::Value movimientos = tomas[i].get("movimientos", NULL);
			
			if (!movimientos || movimientos.empty()){
				Log::getInstancia().logearMensajeEnModo("  [BAD] Fallo el parseo de los movimientos de la toma", Log::MODO_WARNING);
				Log::getInstancia().logearMensajeEnModo("Se cargan movimientos de la toma por defecto", Log::MODO_WARNING);
				return;
			}

			MOV_TIPO unMovimiento;
			ConversorAString* conversor = new ConversorAString();
			for (size_t j = 0; j < movimientos.size(); j++){
				if (movimientos[j].isMember("movimiento") && movimientos[j].get("movimiento", "").isString()){
					unMovimiento = conversor->getMovimientoParaElString(movimientos[j].get("movimiento", "").asString());
					if (unMovimiento != QUIETO)	unaToma->setMovimiento(unMovimiento);
				}
			}
			delete conversor;
			if (unaToma->getMovimientos()->empty()){
				for (size_t k = 0; k < vecMovimientos.size(); k++){
					unaToma->setMovimiento(vecMovimientos.at(k));
				}
			}

			controladorDeTomas->setToma(unaToma);
			Log::getInstancia().logearMensajeEnModo("Se cargo la toma correctamente", Log::MODO_DEBUG);
		}
	}
	Log::getInstancia().logearMensajeEnModo("Se cargaron las tomas correctamente", Log::MODO_DEBUG);
}


ValidadorDeTomas::~ValidadorDeTomas()
{
	vecMovimientos.clear();
}

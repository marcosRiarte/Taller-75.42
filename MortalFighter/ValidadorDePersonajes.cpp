#include "stdafx.h"
#include "ValidadorDePersonajes.h"


ValidadorDePersonajes::ValidadorDePersonajes()
{
	personajes = new std::vector<Personaje*>();
}


bool ValidadorDePersonajes::validarPersonajesDesdeConEscenarioYventana(Json::Value personajesParseados, Escenario* unEscenario, Ventana* unaVentana){
	float ancho;
	float alto;
	int zIndex;
	std::string orientacion;
	std::string sprites;
	std::string CaminarParaAdelante;
	std::string CaminarParaAtras;
	std::string Quieto;
	std::string Salto;
	std::string SaltoDiagonal;
	std::string Golpeado;
	std::string PatadaAlta;
	std::string Agacharse;
	std::string Caida;
	std::string nombre;
	bool errorPersonaje = false;
	float anchoMaximoDelPersonaje = unaVentana->getAncho();
	float altoMaximoDelPersonaje = (unEscenario->getAlto() + unEscenario->getYPiso()); //este el alto maximo
	const char * archivoPersonaje;
	FILE * pFile;

	if (!personajesParseados || personajesParseados.size() == 0){
		Log::getInstancia().logearMensajeEnModo("  [BAD] Fallo el parseo del personaje", Log::MODO_WARNING);
		Log::getInstancia().logearMensajeEnModo("Se cargaron personajes por defecto", Log::MODO_WARNING);
		personajes->push_back(new Personaje(ANCHO_PERSONAJE, ALTO_PERSONAJE, ZINDEX, ORIENTACION_PERSONAJE, SPRITE_DEFAULT, LIU_KANG));
		personajes->push_back(new Personaje(ANCHO_PERSONAJE, ALTO_PERSONAJE, ZINDEX, ORIENTACION_PERSONAJE, SPRITE_DEFAULT, LIU_KANG));
		return true;
	}
	else{
		if (personajesParseados.size() == 1){
			personajes->push_back(new Personaje(ANCHO_PERSONAJE, ALTO_PERSONAJE, ZINDEX, ORIENTACION_PERSONAJE, SPRITE_DEFAULT, LIU_KANG));
		}

		for (size_t i = 0; i < personajesParseados.size(); i++) {

			Personaje* unPersonaje = new Personaje(ANCHO_PERSONAJE, ALTO_PERSONAJE, ZINDEX, ORIENTACION_PERSONAJE, SPRITE_DEFAULT, LIU_KANG);
			
			//NOMBRE
			if (personajesParseados[i].isMember("nombre") && personajesParseados[i].get("nombre", LIU_KANG).isString()){
				unPersonaje->setNombre(personajesParseados[i].get("nombre", LIU_KANG).asString());
			}
			else Log::getInstancia().logearMensajeEnModo("Se carga nombre del personaje por defecto", Log::MODO_WARNING);

			//ANCHO
			if (personajesParseados[i].isMember("ancho") && personajesParseados[i].get("ancho", ANCHO_PERSONAJE).isNumeric() && ((personajesParseados[i].get("ancho", ANCHO_PERSONAJE) < anchoMaximoDelPersonaje) && (anchoMaximoDelPersonaje <= unEscenario->getAncho()))){
				ancho = (personajesParseados[i].get("ancho", ANCHO_PERSONAJE).asFloat());
				if (!(ancho > 0) || ancho > MAX_ANCHO_PERSONAJE) {
					std::string mensaje = "ancho del Personaje fuera de rango, se toma ancho por defecto";
					Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
				}
				else unPersonaje->setAncho(ancho);
			}
			else {
				Log::getInstancia().logearMensajeEnModo("Se carga ancho del personaje por defecto", Log::MODO_WARNING);
			}

			//ALTO
			if (personajesParseados[i].isMember("alto") && personajesParseados[i].get("alto", ALTO_PERSONAJE).isNumeric() && personajesParseados[i].get("alto", ALTO_PERSONAJE) < altoMaximoDelPersonaje){
				alto = (personajesParseados[i].get("alto", ALTO_PERSONAJE).asFloat());
				if (!(alto > 0) || alto > MAX_ALTO_PERSONAJE) {
					std::string mensaje = "alto del Personaje fuera de rango, se toma alto por defecto";
					Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
				}
				else unPersonaje->setAlto(alto);
			}
			else {
				Log::getInstancia().logearMensajeEnModo("Se carga alto del personaje por defecto", Log::MODO_WARNING);
			}

			//ZINDEX
			if (personajesParseados[i].isMember("zindex") && personajesParseados[i].get("zindex", ZINDEX).isNumeric() && personajesParseados[i].get("zindex", ZINDEX) < INT_MAX && personajesParseados[i].get("zindex", ZINDEX) > -INT_MAX){
				zIndex = (personajesParseados[i].get("zindex", ZINDEX).asInt());
				unPersonaje->setZIndex(zIndex);
			}
			else {
				Log::getInstancia().logearMensajeEnModo("Se carga z-index del personaje por defecto", Log::MODO_WARNING);
			}

			//SPRITES
			if (personajesParseados[i].isMember("sprites") && personajesParseados[i].get("sprites", SPRITE_DEFAULT).isString()){
				sprites = (personajesParseados[i].get("sprites", SPRITE_DEFAULT).asString());

				archivoPersonaje = sprites.c_str();
				fopen_s(&pFile, archivoPersonaje, "r");

				if (pFile != NULL) //si me devolvio puntero existe, cerralo!!!!!
				{
					fclose(pFile);
					unPersonaje->setSprites(sprites);
				}
				else // el archivo no existe!
				{
					std::string mensaje = "sprites no existentes";
					Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
					sprites = SPRITE_DEFAULT;
					archivoPersonaje = sprites.c_str();			
					fopen_s(&pFile, archivoPersonaje, "r");

					if (pFile == NULL) //si me devolvio puntero existe, cerralo!!!!!
					{
						Log::getInstancia().logearMensajeEnModo("sprites por defecto no existentes, se cerrara el programa...", Log::MODO_ERROR);
						return false;

					}
					else fclose(pFile);
				}
			}
			else {
				Log::getInstancia().logearMensajeEnModo("Se carga sprite del personaje por defecto", Log::MODO_WARNING);
			}

			//ORIENTACION
			if (personajesParseados[i].isMember("orientacion") && personajesParseados[i].get("orientacion", ORIENTACION_PERSONAJE).isString()){
				orientacion = (personajesParseados[i].get("orientacion", ORIENTACION_PERSONAJE).asString());
				if ((orientacion != "DER") && (orientacion != "IZQ")) {
					std::string mensaje = "orientacion invalida, se toma orientacion derecha";
					Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
				}
				else unPersonaje->setOrientacion(orientacion);
			}
			else {
				Log::getInstancia().logearMensajeEnModo("Se carga orientacion del personaje por defecto", Log::MODO_WARNING);
			}


			personajes->push_back(unPersonaje);
		}
	}

	Log::getInstancia().logearMensajeEnModo("Se cargaron valores del personaje correctamente", Log::MODO_DEBUG);

	return true;
}


std::vector<Personaje*>* ValidadorDePersonajes::getPersonajes(){
	return personajes;
}


ValidadorDePersonajes::~ValidadorDePersonajes()
{
	for (size_t i = 0; i < personajes->size(); i++){
		delete personajes->at(i);
	}
	personajes->clear();
	delete personajes;
}

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
		personajes->push_back(new Personaje(ANCHO_PERSONAJE, ALTO_PERSONAJE, ZINDEX, ORIENTACION_PERSONAJE, SPRITE_DEFAULT, CAMINARPARAADELANTE_DEFAULT, CAMINARPARAATRAS_DEFAULT, QUIETO_DEFAULT, SALTO_DEFAULT, SALTODIAGONAL_DEFAULT, CAIDA_DEFAULT, PATADAALTA_DEFAULT, GOLPEADO_DEFAULT, AGACHARSE_DEFAULT, LIU_KANG));
		personajes->push_back(new Personaje(ANCHO_PERSONAJE, ALTO_PERSONAJE, ZINDEX, ORIENTACION_PERSONAJE, SPRITE_DEFAULT, CAMINARPARAADELANTE_DEFAULT, CAMINARPARAATRAS_DEFAULT, QUIETO_DEFAULT, SALTO_DEFAULT, SALTODIAGONAL_DEFAULT, CAIDA_DEFAULT, PATADAALTA_DEFAULT, GOLPEADO_DEFAULT, AGACHARSE_DEFAULT, LIU_KANG));
		return true;
	}
	else{
		if (personajesParseados.size() == 1){
			personajes->push_back(new Personaje(ANCHO_PERSONAJE, ALTO_PERSONAJE, ZINDEX, ORIENTACION_PERSONAJE, SPRITE_DEFAULT, CAMINARPARAADELANTE_DEFAULT, CAMINARPARAATRAS_DEFAULT, QUIETO_DEFAULT, SALTO_DEFAULT, SALTODIAGONAL_DEFAULT, CAIDA_DEFAULT, PATADAALTA_DEFAULT, GOLPEADO_DEFAULT, AGACHARSE_DEFAULT, LIU_KANG));
		}

		for (size_t i = 0; i < personajesParseados.size(); i++) {

			Personaje* unPersonaje = new Personaje(ANCHO_PERSONAJE, ALTO_PERSONAJE, ZINDEX, ORIENTACION_PERSONAJE, SPRITE_DEFAULT, CAMINARPARAADELANTE_DEFAULT, CAMINARPARAATRAS_DEFAULT, QUIETO_DEFAULT, SALTO_DEFAULT, SALTODIAGONAL_DEFAULT, CAIDA_DEFAULT, PATADAALTA_DEFAULT, GOLPEADO_DEFAULT, AGACHARSE_DEFAULT, LIU_KANG);

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

			//CAMINAR HACIA ADELANTE
			if (personajesParseados[i].isMember("CaminarParaAdelante") && personajesParseados[i].get("CaminarParaAdelante", CAMINARPARAADELANTE_DEFAULT).isString()){
				CaminarParaAdelante = (personajesParseados[i].get("CaminarParaAdelante", CAMINARPARAADELANTE_DEFAULT).asString());
				if ((CaminarParaAdelante != "CaminarParaAdelante") && (CaminarParaAdelante != "CaminarParaAtras") && (CaminarParaAdelante != "Quieto") && (CaminarParaAdelante != "Salto") && (CaminarParaAdelante != "SaltoDiagonal") && (CaminarParaAdelante != "Caida")) {
					std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto Caminar Para Adelante";
					Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
				}
				else unPersonaje->setCaminarParaAdelante(CaminarParaAdelante);
			}
			else {
				Log::getInstancia().logearMensajeEnModo("Se carga sprite CaminarParaAdelante del personaje por defecto", Log::MODO_WARNING);
			}

			//CAMINAR HACIA ATRAS
			if (personajesParseados[i].isMember("CaminarParaAtras") && personajesParseados[i].get("CaminarParaAtras", CAMINARPARAATRAS_DEFAULT).isString()){
				CaminarParaAtras = (personajesParseados[i].get("CaminarParaAtras", CAMINARPARAATRAS_DEFAULT).asString());
				if ((CaminarParaAtras != "CaminarParaAdelante") && (CaminarParaAtras != "CaminarParaAtras") && (CaminarParaAtras != "Quieto") && (CaminarParaAtras != "Salto") && (CaminarParaAtras != "SaltoDiagonal") && (CaminarParaAtras != "Caida")) {
					std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto Caminar Para Atras";
					Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
				}
				else unPersonaje->setCaminarParaAtras(CaminarParaAtras);
			}
			else {
				Log::getInstancia().logearMensajeEnModo("Se carga sprite CaminarParaAtras del personaje por defecto", Log::MODO_WARNING);
			}

			//QUIETO
			if (personajesParseados[i].isMember("Quieto") && personajesParseados[i].get("Quieto", QUIETO_DEFAULT).isString()){
				Quieto = (personajesParseados[i].get("Quieto", QUIETO_DEFAULT).asString());
				if ((Quieto != "CaminarParaAdelante") && (Quieto != "CaminarParaAtras") && (Quieto != "Quieto") && (Quieto != "Salto") && (Quieto != "SaltoDiagonal") && (Quieto != "Caida")) {
					std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto Quieto";
				}
				else unPersonaje->setQuieto(Quieto);
			}
			else {
				Log::getInstancia().logearMensajeEnModo("Se carga sprite Quieto del personaje por defecto", Log::MODO_WARNING);
			}

			//SALTO
			if (personajesParseados[i].isMember("Salto") && personajesParseados[i].get("Salto", SALTO_DEFAULT).isString()){
				Salto = (personajesParseados[i].get("Salto", SALTO_DEFAULT).asString());
				if ((Salto != "CaminarParaAdelante") && (Salto != "CaminarParaAtras") && (Salto != "Quieto") && (Salto != "Salto") && (Salto != "SaltoDiagonal") && (Salto != "Caida")) {
					std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto Salto";
					Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
				}
				else unPersonaje->setSalto(Salto);
			}
			else {
				Log::getInstancia().logearMensajeEnModo("Se carga sprite Salto del personaje por defecto", Log::MODO_WARNING);
			}

			//SALTO DIAGONAL
			if (personajesParseados[i].isMember("SaltoDiagonal") && personajesParseados[i].get("SaltoDiagonal", SALTODIAGONAL_DEFAULT).isString()){
				SaltoDiagonal = (personajesParseados[i].get("SaltoDiagonal", SALTODIAGONAL_DEFAULT).asString());

				if ((SaltoDiagonal != "CaminarParaAdelante") && (SaltoDiagonal != "CaminarParaAtras") && (SaltoDiagonal != "Quieto") && (SaltoDiagonal != "Salto") && (SaltoDiagonal != "SaltoDiagonal") && (SaltoDiagonal != "Caida")) {
					std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto Salto Diagonal";
					Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
				}
				else unPersonaje->setSaltoDiagonal(SaltoDiagonal);
			}
			else {
				Log::getInstancia().logearMensajeEnModo("Se carga sprite SaltoDiagonal del personaje por defecto", Log::MODO_WARNING);
			}
			
			//PATADA ALTA
			if (personajesParseados[i].isMember("PatadaAlta") && personajesParseados[i].get("PatadaAlta", PATADAALTA_DEFAULT).isString()){
				PatadaAlta = (personajesParseados[i].get("PatadaAlta", PATADAALTA_DEFAULT).asString());
				if ((PatadaAlta != "CaminarParaAdelante") && (PatadaAlta != "CaminarParaAtras") && (PatadaAlta != "Quieto") && (PatadaAlta != "Salto") && (PatadaAlta != "SaltoDiagonal") && (PatadaAlta != "Caida")) {
					std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto Patada Alta";
					Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
				}
				unPersonaje->setPatadaAlta(PatadaAlta);
			}
			else {
				Log::getInstancia().logearMensajeEnModo("Se carga sprite PatadaAlta del personaje por defecto", Log::MODO_WARNING);
			}

			//AGACHARSE
			if (personajesParseados[i].isMember("Agacharse") && personajesParseados[i].get("Agacharse", AGACHARSE_DEFAULT).isString()){
				Agacharse = (personajesParseados[i].get("Agacharse", AGACHARSE_DEFAULT).asString());
				if ((Agacharse != "CaminarParaAdelante") && (Agacharse != "CaminarParaAtras") && (Agacharse != "Quieto") && (Agacharse != "Salto") && (Agacharse != "SaltoDiagonal") && (Agacharse != "Caida")) {
					std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto Agacharse";
					Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
				}
				unPersonaje->setAgacharse(Agacharse);
			}
			else {
				Log::getInstancia().logearMensajeEnModo("Se carga sprite Agacharse del personaje por defecto", Log::MODO_WARNING);
			}

			//GOLPEADO
			if (personajesParseados[i].isMember("Golpeado") && personajesParseados[i].get("Golpeado", GOLPEADO_DEFAULT).isString()){
				Golpeado = (personajesParseados[i].get("Golpeado", GOLPEADO_DEFAULT).asString());
				if ((Golpeado != "CaminarParaAdelante") && (Golpeado != "CaminarParaAtras") && (Golpeado != "Quieto") && (Golpeado != "Salto") && (Golpeado != "SaltoDiagonal") && (Golpeado != "Caida")) {
					std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto Golpeado";
					Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
				}
				unPersonaje->setGolpeado(Golpeado);
			}
			else {
				Log::getInstancia().logearMensajeEnModo("Se carga sprite Golpeado del personaje por defecto", Log::MODO_WARNING);
			}

			//CAIDA
			if (personajesParseados[i].isMember("Caida") && personajesParseados[i].get("Caida", CAIDA_DEFAULT).isString()){
				Caida = (personajesParseados[i].get("Caida", CAIDA_DEFAULT).asString());
				if ((Caida != "CaminarParaAdelante") && (Caida != "CaminarParaAtras") && (Caida != "Quieto") && (Caida != "Salto") && (Caida != "SaltoDiagonal") && (Caida != "Caida")) {
					std::string mensaje = "Funcion del personaje invalida, se toma funcion por defecto Caida";
					Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
				}
				else unPersonaje->setCaida(Caida);
			}
			else {
				Log::getInstancia().logearMensajeEnModo("Se carga sprite Caida del personaje por defecto", Log::MODO_WARNING);
			}

			//xjose  TODO falta validar agacharse, golpeado, patadaalta
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

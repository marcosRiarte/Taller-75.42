#include "stdafx.h"
#include "ValidadorDeCapas.h"


ValidadorDeCapas::ValidadorDeCapas()
{
	capas = new std::vector<Capa*>();
}


bool ValidadorDeCapas::validarCapas(float *anchoCapa, std::string *fondo, size_t numerocapa){
	if (!(*anchoCapa > 0)){

		std::string mensaje = "ancho de Capa " + std::to_string(numerocapa) + " fuera de rango, se toma ancho por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		*anchoCapa = ANCHO_CAPA;
	}


	//  intento abrir el archivo, si el puntero devuelto es NULL NO EXISTE EL ARCHIVO  
	const char * archivofondo = fondo->c_str(); //casteo
	FILE * pFile;
	fopen_s(&pFile, archivofondo, "r");

	if (pFile != NULL) //si me devolvio puntero existe, cerralo!!!!!
	{
		fclose(pFile);
	}
	else // el archivo no existe!
	{
		std::string mensaje = "No existe la capa " + std::to_string(numerocapa) + " , se usa capa por defecto";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);

		*fondo = FONDO_DEFAULT;
		const char * archivofondo = fondo->c_str(); //casteo
		FILE * pFile;
		fopen_s(&pFile, archivofondo, "r");

		if (pFile == NULL)
		{
			Log::getInstancia().logearMensajeEnModo("no existe el fondo por defecto, se cerrara el programa...", Log::MODO_ERROR);
			return true;
		}
		else fclose(pFile);
	}
	return false;
}


bool ValidadorDeCapas::validarCapasDesde(Json::Value capasParseadas){
	float anchoCapas;
	std::string fondo;
	bool errorCapa = false;

	if (!capasParseadas || capasParseadas.size() == 0){
		Log::getInstancia().logearMensajeEnModo("  [BAD] Fallo el parseo de las capas", Log::MODO_WARNING);
		fondo = FONDO_DEFAULT;
		anchoCapas = ANCHO_CAPA;

		errorCapa = validarCapas(&anchoCapas, &fondo, 0);
		if (errorCapa){
			return false;
		}
		capas->push_back(new Capa(fondo, anchoCapas, 0));
		Log::getInstancia().logearMensajeEnModo("Se cargaron capas y ancho por defecto", Log::MODO_WARNING);
	}
	else{//se valida que exista el campo, que sea un tipo dedato correcto. De los rangos y existencia de archivo se encarga el validador
		for (size_t i = 0; i < capasParseadas.size(); i++) {

			std::string fondo(FONDO_DEFAULT);//asigno fondo por defecto

			//valido que exista el campo y que tenga un string
			if (capasParseadas[i].isMember("imagen_fondo") && capasParseadas[i].get("imagen_fondo", FONDO_DEFAULT).isString())
				fondo = (capasParseadas[i].get("imagen_fondo", FONDO_DEFAULT).asString());
			else
				Log::getInstancia().logearMensajeEnModo("Campo Imagen_fondo incorrecto en capa " + std::to_string(i) + " , se usa capa por defecto", Log::MODO_WARNING);
			//la capa por defecto se asigno arriba

			if (capasParseadas[i].isMember("ancho") && capasParseadas[i].get("ancho", ANCHO_CAPA).isNumeric() && capasParseadas[i].get("ancho", ANCHO_CAPA) < MAX_ANCHO_ESCENARIO)
				anchoCapas = (capasParseadas[i].get("ancho", ANCHO_CAPA).asFloat());
			else {
				anchoCapas = ANCHO_CAPA;
				Log::getInstancia().logearMensajeEnModo("Se carga ancho de capa " + std::to_string(i) + " , por defecto", Log::MODO_WARNING);
			}

			int zIndexCapa = ZINDEX_CAPA;
			if (!capasParseadas[i].isMember("zindex"))
				Log::getInstancia().logearMensajeEnModo("Se carga z-index de capa " + std::to_string(i) + "  por defecto ->" + std::to_string(ZINDEX_CAPA), Log::MODO_DEBUG);
			else {
				if (capasParseadas[i].get("zindex", ZINDEX_CAPA).isNumeric() && capasParseadas[i].get("zindex", ZINDEX_CAPA) < INT_MAX && capasParseadas[i].get("zindex", ZINDEX_CAPA) > -INT_MAX)
					zIndexCapa = (capasParseadas[i].get("zindex", ZINDEX_CAPA).asInt());
				else
					Log::getInstancia().logearMensajeEnModo("Se carga z-index de capa " + std::to_string(i) + "  por defecto ->" + std::to_string(ZINDEX_CAPA), Log::MODO_WARNING);
			}

			errorCapa = validarCapas(&anchoCapas, &fondo, i);
			if (errorCapa){
				return false;
			}
			capas->push_back(new Capa(fondo, anchoCapas, zIndexCapa));
		}
		Log::getInstancia().logearMensajeEnModo("Se cargaron capas correctamente", Log::MODO_DEBUG);
	}

	return true;
}


std::vector<Capa*>* ValidadorDeCapas::getCapas(){
	return capas;
}


ValidadorDeCapas::~ValidadorDeCapas()
{
	for (size_t i = 0; i < capas->size(); i++){
		delete capas->at(i);
	}
	capas->clear();
	delete capas;
}

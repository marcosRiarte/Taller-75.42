#include "Parser.h"

Parser& Parser::getInstancia() {

	static Parser instancia;
	// Se garantiza que será destruido.
	// Se instancia en el primer uso.
	return instancia;
}

Parser::Parser() { }


bool Parser::parsear(std::string nombreDelArchivo)
{	
	Json::Value raiz;
	//Se coloca al lector de Json en modo estricto para que loguee todos los mensajes de errores sintácticos
	Json::Reader lector(Json::Features::strictMode());
	std::ifstream prueba(nombreDelArchivo, std::ifstream::binary);

	bool parseoExitoso;

	//chequea que exista el archivo prueba.json y se pudeda abrir
	if (!prueba.is_open()){
		Log::getInstancia().logearMensajeEnModo("  [BAD] No se pudo abrir el json de prueba o no existe", Log::MODO_WARNING);
		parseoExitoso = false;
	}
	else //el archivo existe, lo parseo
	{
		parseoExitoso = lector.parse(prueba, raiz, true);
	}

	

	if (!parseoExitoso) {
		std::string mensaje = "  [BAD]  Fallo el parseo, se carga json por defecto" + lector.getFormattedErrorMessages();
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		std::ifstream prueba(PRUEBA_JSON_DEFECTO, std::ifstream::binary);
		if (!prueba.is_open()){
			Log::getInstancia().logearMensajeEnModo("  [BAD] No se pudo abrir el json por defecto, se cerrara el programa...", Log::MODO_ERROR);
			return false;
		}
		bool parseoExitoso = lector.parse(prueba, raiz, true);
		if (!parseoExitoso) {
			Log::getInstancia().logearMensajeEnModo("  [BAD] Fallo el parseo del json por defecto, se cerrara el programa...", Log::MODO_ERROR);
			return false;
		}
		Log::getInstancia().logearMensajeEnModo("Parseo del archivo json por defecto correcto", Log::MODO_DEBUG);
	}else Log::getInstancia().logearMensajeEnModo("Parseo del archivo json correcto", Log::MODO_DEBUG);



	Json::Value ventana;
	ventana = raiz["ventana"];
	int anchoPxVentana;
	int altoPxVentana;
	float anchoVentana;

	if (!ventana){
		Log::getInstancia().logearMensajeEnModo("  [BAD] Fallo el parseo de la ventana", Log::MODO_WARNING);
		anchoPxVentana = ANCHO_PX_VENTANA;
		altoPxVentana = ALTO_PX_VENTANA;
		anchoVentana = ANCHO_VENTANA;
		Log::getInstancia().logearMensajeEnModo("Se cargaron valores de la ventana por defecto", Log::MODO_WARNING);
	}
	else{
		//3 comprobaciones, que exista el campo, que sea un numero y que no exceda el maximo
		if (ventana.isMember("anchopx") && ventana.get("anchopx", ANCHO_PX_VENTANA).isNumeric() && ((ventana.get("anchopx", ANCHO_PX_VENTANA) < INT_MAX) && (ventana.get("anchopx", ANCHO_PX_VENTANA) >= ANCHO_MIN)))
				anchoPxVentana = (ventana.get("anchopx", ANCHO_PX_VENTANA).asInt());			
		else {
			anchoPxVentana = ANCHO_PX_VENTANA;
			Log::getInstancia().logearMensajeEnModo("Se carga anchopx de la ventana por defecto", Log::MODO_WARNING);
		}

		if (ventana.isMember("altopx") && ventana.get("altopx", ALTO_PX_VENTANA).isNumeric() && ((ventana.get("altopx", ALTO_PX_VENTANA) < INT_MAX) && (ventana.get("altopx", ALTO_PX_VENTANA) >= ALTO_MIN)))
			altoPxVentana = (ventana.get("altopx", ALTO_PX_VENTANA).asInt());			
		else {
			altoPxVentana = ALTO_PX_VENTANA;
			Log::getInstancia().logearMensajeEnModo("Se carga altopx de la ventana por defecto", Log::MODO_WARNING);
		}

		if (ventana.isMember("ancho") && ventana.get("ancho", ANCHO_VENTANA).isNumeric() && ventana.get("ancho", ANCHO_VENTANA) < INT_MAX)
				anchoVentana = (ventana.get("ancho", ANCHO_VENTANA).asFloat());			
		else {
			anchoVentana = ANCHO_VENTANA;
			Log::getInstancia().logearMensajeEnModo("Se carga ancho de la ventana por defecto", Log::MODO_WARNING);
		}
		
	}

	Validador::ValidarVentana(&anchoPxVentana, &altoPxVentana, &anchoVentana);
	unaVentana = new Ventana(anchoPxVentana, altoPxVentana, anchoVentana);
	Log::getInstancia().logearMensajeEnModo("Se cargaron valores de la ventana correctamente", Log::MODO_DEBUG);

	Json::Value escenario;
	escenario = raiz["escenario"];
	float anchoEscenario;
	float altoEscenario;
	float yPisoEscenario;

	if (!escenario){
		Log::getInstancia().logearMensajeEnModo("  [BAD] Fallo el parseo del escenario", Log::MODO_WARNING);
		anchoEscenario = ANCHO_ESCENARIO;
		altoEscenario = ALTO_ESCENARIO;
		yPisoEscenario = Y_PISO_ESCENARIO;
		Log::getInstancia().logearMensajeEnModo("Se cargaron valores del escenario por defecto", Log::MODO_WARNING);
	}
	else{
		if (escenario.isMember("ancho") && escenario.get("ancho", ANCHO_ESCENARIO).isNumeric() && escenario.get("ancho", ANCHO_ESCENARIO) < MAX_ANCHO_ESCENARIO)
				anchoEscenario = (escenario.get("ancho", ANCHO_ESCENARIO).asFloat());				
		else {
			anchoEscenario = ANCHO_ESCENARIO;
			Log::getInstancia().logearMensajeEnModo("Se carga ancho del escenario por defecto", Log::MODO_WARNING);
		}

		if (escenario.isMember("alto") && escenario.get("alto", ALTO_ESCENARIO).isNumeric() && escenario.get("alto", ALTO_ESCENARIO) < MAX_ALTO_ESCENARIO)
				altoEscenario = (escenario.get("alto", ALTO_ESCENARIO).asFloat());			
		else {
			altoEscenario = ALTO_ESCENARIO;
			Log::getInstancia().logearMensajeEnModo("Se carga alto del escenario por defecto", Log::MODO_WARNING);
		}

		if (escenario.isMember("ypiso") && escenario.get("ypiso", Y_PISO_ESCENARIO).isNumeric() && escenario.get("ypiso", Y_PISO_ESCENARIO) < MAX_ALTO_ESCENARIO)
				yPisoEscenario = (escenario.get("ypiso", Y_PISO_ESCENARIO).asFloat());			
		else {
			yPisoEscenario = Y_PISO_ESCENARIO;
			Log::getInstancia().logearMensajeEnModo("Se carga piso del escenario por defecto", Log::MODO_WARNING);
		}
		
	}

	

	Json::Value capas;
	capas = raiz["capas"];
	float anchoCapas;
	std::string fondo;
	bool errorCapa = false;
	
	
	if (!capas || capas.size() == 0){
		Log::getInstancia().logearMensajeEnModo("  [BAD] Fallo el parseo de las capas", Log::MODO_WARNING);
		fondo = FONDO_DEFAULT;
		anchoCapas = ANCHO_CAPA;
		
		errorCapa = Validador::ValidarCapas(&anchoCapas, &fondo, 0);
		if (errorCapa){
			return false;
		}
		Capas.push_back(new Capa(fondo, anchoCapas, 0));
		Log::getInstancia().logearMensajeEnModo("Se cargaron capas y ancho por defecto", Log::MODO_WARNING);
	}
	else{//se valida que exista el campo, que sea un tipo dedato correcto. De los rangos y existencia de archivo se encarga el validador
		for (size_t i = 0; i < capas.size(); i++) {
			
			std::string fondo(FONDO_DEFAULT);//asigno fondo por defecto
			
			//valido que exista el campo y que tenga un string
			if (capas[i].isMember("imagen_fondo") && capas[i].get("imagen_fondo", FONDO_DEFAULT).isString())
				fondo = (capas[i].get("imagen_fondo", FONDO_DEFAULT).asString());
			else
				Log::getInstancia().logearMensajeEnModo("Campo Imagen_fondo incorrecto en capa " + std::to_string(i) + " , se usa capa por defecto", Log::MODO_WARNING);
			    //la capa por defecto se asigno arriba



			if (capas[i].isMember("ancho") && capas[i].get("ancho", ANCHO_CAPA).isNumeric() && capas[i].get("ancho", ANCHO_CAPA) < MAX_ANCHO_ESCENARIO)
					anchoCapas = (capas[i].get("ancho", ANCHO_CAPA).asFloat());				
			else {
				anchoCapas = ANCHO_CAPA;
				Log::getInstancia().logearMensajeEnModo("Se carga ancho de capa " + std::to_string(i) + " , por defecto", Log::MODO_WARNING);
			}



			int zIndexCapa = ZINDEX_CAPA;
			if (!capas[i].isMember("zindex"))
				Log::getInstancia().logearMensajeEnModo("Se carga z-index de capa " + std::to_string(i) + "  por defecto ->" + std::to_string(ZINDEX_CAPA), Log::MODO_DEBUG);
			else {
				if (capas[i].get("zindex", ZINDEX_CAPA).isNumeric() && capas[i].get("zindex", ZINDEX_CAPA) < INT_MAX && capas[i].get("zindex", ZINDEX_CAPA) > -INT_MAX)
					zIndexCapa = (capas[i].get("zindex", ZINDEX_CAPA).asInt());
				else
					Log::getInstancia().logearMensajeEnModo("Se carga z-index de capa " + std::to_string(i) + "  por defecto ->" + std::to_string(ZINDEX_CAPA), Log::MODO_WARNING);
			}
				


			errorCapa = Validador::ValidarCapas(&anchoCapas, &fondo, i);
			if (errorCapa){
				return false;
			}
			Capas.push_back(new Capa(fondo, anchoCapas, zIndexCapa));
		}
		Log::getInstancia().logearMensajeEnModo("Se cargaron capas correctamente", Log::MODO_DEBUG);
	}


	Json::Value personajes;
	personajes = raiz["personajes"];
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
	std::string Caida;
	bool errorPersonaje = false;
	int anchoMaximoDelPersonaje = (int)round((anchoPxVentana * altoEscenario) / altoPxVentana); //el resultado de este calculo deberia ser el ancho maximo de la ventana en uninades logicas.
	int altoMaximoDelPersonaje = (int)round(altoEscenario + yPisoEscenario); //este el alto maximo

	if (!personajes || personajes.size() == 0){
		Log::getInstancia().logearMensajeEnModo("  [BAD] Fallo el parseo del personaje", Log::MODO_WARNING);
		ancho = ANCHO_PERSONAJE;
		alto = ALTO_PERSONAJE;
		zIndex = ZINDEX;
		orientacion = ORIENTACION_PERSONAJE;
		sprites = SPRITE_DEFAULT;
		
		CaminarParaAdelante = CAMINARPARAADELANTE_DEFAULT;
		CaminarParaAtras = CAMINARPARAATRAS_DEFAULT;
		Quieto = QUIETO_DEFAULT;
		Salto = SALTO_DEFAULT;
		SaltoDiagonal = SALTODIAGONAL_DEFAULT;
		Caida = CAIDA_DEFAULT;
		Log::getInstancia().logearMensajeEnModo("Se cargaron valores del personaje por defecto", Log::MODO_WARNING);
		
	}
	else{
		for (size_t i = 0; i < personajes.size(); i++) {

			if (personajes[i].isMember("ancho") && personajes[i].get("ancho", ANCHO_PERSONAJE).isNumeric() && ((personajes[i].get("ancho", ANCHO_PERSONAJE) < anchoMaximoDelPersonaje) && (anchoMaximoDelPersonaje <= anchoEscenario)))
				ancho = (personajes[i].get("ancho", ANCHO_PERSONAJE).asFloat());
			else {
				ancho = ANCHO_PERSONAJE;
				Log::getInstancia().logearMensajeEnModo("Se carga ancho del personaje por defecto", Log::MODO_WARNING);
			}

			if (personajes[i].isMember("alto") && personajes[i].get("alto", ALTO_PERSONAJE).isNumeric() && personajes[i].get("alto", ALTO_PERSONAJE) < altoMaximoDelPersonaje)
				alto = (personajes[i].get("alto", ALTO_PERSONAJE).asFloat());
			else {
				alto = ALTO_PERSONAJE;
				Log::getInstancia().logearMensajeEnModo("Se carga alto del personaje por defecto", Log::MODO_WARNING);
			}

			if (personajes[i].isMember("zindex") && personajes[i].get("zindex", ZINDEX).isNumeric() && personajes[i].get("zindex", ZINDEX) < INT_MAX && personajes[i].get("zindex", ZINDEX) > -INT_MAX)
				zIndex = (personajes[i].get("zindex", ZINDEX).asInt());
			else {
				zIndex = ZINDEX;
				Log::getInstancia().logearMensajeEnModo("Se carga z-index del personaje por defecto", Log::MODO_WARNING);
			}

			if (personajes[i].isMember("sprites") && personajes[i].get("sprites", SPRITE_DEFAULT).isString())
				sprites = (personajes[i].get("sprites", SPRITE_DEFAULT).asString());
			else {
				sprites = SPRITE_DEFAULT;
				Log::getInstancia().logearMensajeEnModo("Se carga sprite del personaje por defecto", Log::MODO_WARNING);
			}

			if (personajes[i].isMember("orientacion") && personajes[i].get("orientacion", ORIENTACION_PERSONAJE).isString())
				orientacion = (personajes[i].get("orientacion", ORIENTACION_PERSONAJE).asString());
			else {
				orientacion = ORIENTACION_PERSONAJE;
				Log::getInstancia().logearMensajeEnModo("Se carga orientacion del personaje por defecto", Log::MODO_WARNING);
			}

			if (personajes[i].isMember("CaminarParaAdelante") && personajes[i].get("CaminarParaAdelante", CAMINARPARAADELANTE_DEFAULT).isString())
				CaminarParaAdelante = (personajes[i].get("CaminarParaAdelante", CAMINARPARAADELANTE_DEFAULT).asString());
			else {
				CaminarParaAdelante = CAMINARPARAADELANTE_DEFAULT;
				Log::getInstancia().logearMensajeEnModo("Se carga sprite CaminarParaAdelante del personaje por defecto", Log::MODO_WARNING);
			}

			if (personajes[i].isMember("CaminarParaAtras") && personajes[i].get("CaminarParaAtras", CAMINARPARAATRAS_DEFAULT).isString())
				CaminarParaAtras = (personajes[i].get("CaminarParaAtras", CAMINARPARAATRAS_DEFAULT).asString());
			else {
				CaminarParaAtras = CAMINARPARAATRAS_DEFAULT;
				Log::getInstancia().logearMensajeEnModo("Se carga sprite CaminarParaAtras del personaje por defecto", Log::MODO_WARNING);
			}

			if (personajes[i].isMember("Quieto") && personajes[i].get("Quieto", QUIETO_DEFAULT).isString())
				Quieto = (personajes[i].get("Quieto", QUIETO_DEFAULT).asString());
			else {
				Quieto = QUIETO_DEFAULT;
				Log::getInstancia().logearMensajeEnModo("Se carga sprite Quieto del personaje por defecto", Log::MODO_WARNING);
			}

			if (personajes[i].isMember("Salto") && personajes[i].get("Salto", SALTO_DEFAULT).isString())
				Salto = (personajes[i].get("Salto", SALTO_DEFAULT).asString());
			else {
				Salto = SALTO_DEFAULT;
				Log::getInstancia().logearMensajeEnModo("Se carga sprite Salto del personaje por defecto", Log::MODO_WARNING);
			}

			if (personajes[i].isMember("SaltoDiagonal") && personajes[i].get("SaltoDiagonal", SALTODIAGONAL_DEFAULT).isString())
				SaltoDiagonal = (personajes[i].get("SaltoDiagonal", SALTODIAGONAL_DEFAULT).asString());
			else {
				SaltoDiagonal = SALTODIAGONAL_DEFAULT;
				Log::getInstancia().logearMensajeEnModo("Se carga sprite SaltoDiagonal del personaje por defecto", Log::MODO_WARNING);
			}

			if (personajes[i].isMember("Caida") && personajes[i].get("Caida", CAIDA_DEFAULT).isString())
				Caida = (personajes[i].get("Caida", CAIDA_DEFAULT).asString());
			else {
				Caida = CAIDA_DEFAULT;
				Log::getInstancia().logearMensajeEnModo("Se carga sprite Caida del personaje por defecto", Log::MODO_WARNING);
			}


			errorPersonaje = Validador::ValidarPersonaje(&ancho, &alto, &zIndex, &orientacion, &sprites, &CaminarParaAdelante, &CaminarParaAtras, &Quieto, &Salto, &SaltoDiagonal, &Caida);
			if (errorPersonaje){
				return false;
			}
			Personajes.push_back(new Personaje(ancho, alto, zIndex, orientacion, sprites, CaminarParaAdelante, CaminarParaAtras, Quieto, Salto, SaltoDiagonal, Caida));
		}
	}
	

	Log::getInstancia().logearMensajeEnModo("Se cargaron valores del personaje correctamente", Log::MODO_DEBUG);
	Validador::ValidarEscenario(&anchoEscenario, &altoEscenario, &alto, &yPisoEscenario);
	unEscenario = new Escenario(anchoEscenario, altoEscenario, yPisoEscenario);
	Log::getInstancia().logearMensajeEnModo("Se cargaron valores del escenario correctamente", Log::MODO_DEBUG);

	// en esta parte se desarma todo......
	//
	//
	//
	//

	Json::Value color_alternativo ;
	color_alternativo = raiz["color_alternativo"];
	int h_inicial;
	int h_final ;
	int desplazamiento;
	
	
	return true;
}

Escenario& Parser::getEscenario() const
{
	return *unEscenario;
}

Ventana& Parser::getVentana() const
{
	return *unaVentana;
}

std::vector<Personaje*> Parser::getPersonajes() const
{
	return Personajes;
}

std::vector<Capa*> Parser::getCapas() const
{
	return Capas;

}

void Parser::FreeInstancia()
{
	delete getInstancia().unaVentana;
	delete  getInstancia().unEscenario;
	for (size_t j = 0; j < getInstancia().Personajes.size(); j++) {
		delete getInstancia().Personajes.at(j);
	}
	getInstancia().Personajes.clear();
	for (size_t i = 0; i < getInstancia().Capas.size(); i++) {
		delete getInstancia().Capas.at(i);		
	}
	getInstancia().Capas.clear();
}

Parser::~Parser()
{
}

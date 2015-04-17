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

	//chequea que exista el archivo y se pudo abrir
	if (!prueba.is_open()){
		Log::getInstancia().logearMensajeEnModo("No se pudo abrir el archivo", Log::MODO_WARNING);
		return false;
	}

	bool parseoExitoso = lector.parse(prueba, raiz, true);

	if (!parseoExitoso) {
		std::string mensaje = "Fallo el parseo, se carga json por defecto" + lector.getFormattedErrorMessages();
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		std::ifstream prueba("pruebaDefecto.json", std::ifstream::binary);
		if (!prueba.is_open()){
			Log::getInstancia().logearMensajeEnModo("No se pudo abrir el archivo por defecto, se cerrara el programa...", Log::MODO_ERROR);
			return false;
		}
		bool parseoExitoso = lector.parse(prueba, raiz, true);
		if (!parseoExitoso) {
			Log::getInstancia().logearMensajeEnModo("Fallo el parseo del json por defecto, se cerrara el programa...", Log::MODO_ERROR);
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
		Log::getInstancia().logearMensajeEnModo("Fallo el parseo de la ventana", Log::MODO_WARNING);
		anchoPxVentana = ANCHO_PX_VENTANA;
		altoPxVentana = ALTO_PX_VENTANA;
		anchoVentana = ANCHO_VENTANA;
		Log::getInstancia().logearMensajeEnModo("Se cargaron valores de la ventana por defecto", Log::MODO_WARNING);
	}
	else{
		if (ventana.get("anchopx", ANCHO_PX_VENTANA).isNumeric())
			anchoPxVentana = (ventana.get("anchopx", ANCHO_PX_VENTANA).asInt());
		else anchoPxVentana = ANCHO_PX_VENTANA;

		if (ventana.get("altopx", ALTO_PX_VENTANA).isNumeric())
			altoPxVentana = (ventana.get("altopx", ALTO_PX_VENTANA).asInt());
		else altoPxVentana = ALTO_PX_VENTANA;

		if (ventana.get("ancho", ANCHO_VENTANA).isNumeric())
			anchoVentana = (ventana.get("ancho", ANCHO_VENTANA).asFloat());
		else anchoVentana = ANCHO_VENTANA;
		
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
		Log::getInstancia().logearMensajeEnModo("Fallo el parseo del escenario", Log::MODO_WARNING);
		anchoEscenario = ANCHO_ESCENARIO;
		altoEscenario = ALTO_ESCENARIO;
		yPisoEscenario = Y_PISO_ESCENARIO;
		Log::getInstancia().logearMensajeEnModo("Se cargaron valores del escenario por defecto", Log::MODO_WARNING);
	}
	else{
		if (escenario.get("ancho", ANCHO_ESCENARIO).isNumeric())
			anchoEscenario = (escenario.get("ancho", ANCHO_ESCENARIO).asFloat());
		else anchoEscenario = ANCHO_ESCENARIO;

		if (escenario.get("alto", ALTO_ESCENARIO).isNumeric())
			altoEscenario = (escenario.get("alto", ALTO_ESCENARIO).asFloat());
		else altoEscenario = ALTO_ESCENARIO;

		if (escenario.get("ypiso", Y_PISO_ESCENARIO).isNumeric())
			yPisoEscenario = (escenario.get("ypiso", Y_PISO_ESCENARIO).asFloat());
		else yPisoEscenario = Y_PISO_ESCENARIO;
		
	}

	Validador::ValidarEscenario(&anchoEscenario, &altoEscenario, &yPisoEscenario);
	unEscenario = new Escenario(anchoEscenario, altoEscenario, yPisoEscenario);
	Log::getInstancia().logearMensajeEnModo("Se cargaron valores del escenario correctamente", Log::MODO_DEBUG);

	Json::Value capas;
	capas = raiz["capas"];
	float anchoCapas;
	std::string fondo;

	if (!capas || capas.size() == 0){
		Log::getInstancia().logearMensajeEnModo("Fallo el parseo de las capas", Log::MODO_WARNING);
		fondo = FONDO_DEFAULT;
		anchoCapas = ANCHO_CAPA;
		
		Validador::ValidarCapas(&anchoCapas, &fondo);
		Capas.push_back(new Capa(fondo, anchoCapas, 0));
		Log::getInstancia().logearMensajeEnModo("Se cargaron capas por defecto", Log::MODO_WARNING);
	}
	else{
		for (size_t i = 0; i < capas.size(); i++) {
			
			std::string fondo(FONDO_DEFAULT);
			if (capas[i].get("imagen_fondo", FONDO_DEFAULT).isString())
				fondo = (capas[i].get("imagen_fondo", FONDO_DEFAULT).asString());			

			if (capas[i].get("ancho", ANCHO_CAPA).isNumeric())
				anchoCapas = (capas[i].get("ancho", ANCHO_CAPA).asFloat());
			else anchoCapas = ANCHO_CAPA;

			int zIndexCapa = ZINDEX_CAPA;
			if (capas[i].get("zindex", ZINDEX_CAPA).isNumeric())
				zIndexCapa = (capas[i].get("zindex", ZINDEX_CAPA).asInt());			
									
			Validador::ValidarCapas(&anchoCapas, &fondo);
			Capas.push_back(new Capa(fondo, anchoCapas, zIndexCapa));
		}
		Log::getInstancia().logearMensajeEnModo("Se cargaron capas correctamente", Log::MODO_DEBUG);
	}


	Json::Value personaje;
	personaje = raiz["personaje"];
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

	if (!personaje){
		Log::getInstancia().logearMensajeEnModo("Fallo el parseo del personaje", Log::MODO_WARNING);
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
		if (personaje.get("ancho", ANCHO_PERSONAJE).isNumeric())
			ancho = (personaje.get("ancho", ANCHO_PERSONAJE).asFloat());
		else ancho = ANCHO_PERSONAJE;

		if (personaje.get("alto", ALTO_PERSONAJE).isNumeric())
			alto = (personaje.get("alto", ALTO_PERSONAJE).asFloat());
		else alto = ALTO_PERSONAJE;

		if (personaje.get("zindex", ZINDEX).isNumeric())
			zIndex = (personaje.get("zindex", ZINDEX).asInt());
		else zIndex = ZINDEX;

		if (personaje.get("sprites", SPRITE_DEFAULT).isString())
			sprites = (personaje.get("sprites", SPRITE_DEFAULT).asString());
		else sprites = SPRITE_DEFAULT;

		if (personaje.get("orientacion", ORIENTACION_PERSONAJE).isString())
			orientacion = (personaje.get("orientacion", ORIENTACION_PERSONAJE).asString());
		else orientacion = ORIENTACION_PERSONAJE;
		
		if (personaje.get("CaminarParaAdelante", CAMINARPARAADELANTE_DEFAULT).isString())
			CaminarParaAdelante = (personaje.get("CaminarParaAdelante", CAMINARPARAADELANTE_DEFAULT).asString());
		else CaminarParaAdelante = CAMINARPARAADELANTE_DEFAULT;

		if (personaje.get("CaminarParaAtras", CAMINARPARAATRAS_DEFAULT).isString())
			CaminarParaAtras = (personaje.get("CaminarParaAtras", CAMINARPARAATRAS_DEFAULT).asString());
		else CaminarParaAtras = CAMINARPARAATRAS_DEFAULT;

		if (personaje.get("Quieto", QUIETO_DEFAULT).isString())
			Quieto = (personaje.get("Quieto", QUIETO_DEFAULT).asString());
		else Quieto = QUIETO_DEFAULT;

		if (personaje.get("Salto", SALTO_DEFAULT).isString())
			Salto = (personaje.get("Salto", SALTO_DEFAULT).asString());
		else Salto = SALTO_DEFAULT;

		if (personaje.get("SaltoDiagonal", SALTODIAGONAL_DEFAULT).isString())
			SaltoDiagonal = (personaje.get("SaltoDiagonal", SALTODIAGONAL_DEFAULT).asString());
		else SaltoDiagonal = SALTODIAGONAL_DEFAULT;

		if (personaje.get("Caida", CAIDA_DEFAULT).isString())
			Caida = (personaje.get("Caida", CAIDA_DEFAULT).asString());
		else Caida = CAIDA_DEFAULT;
		
	}
	
	Validador::ValidarPersonaje(&ancho, &alto, &zIndex, &orientacion, &sprites, &CaminarParaAdelante, &CaminarParaAtras, &Quieto, &Salto, &SaltoDiagonal, &Caida);
	
	unPersonaje = new Personaje(ancho, alto, zIndex, orientacion, sprites, CaminarParaAdelante, CaminarParaAtras, Quieto, Salto, SaltoDiagonal, Caida);
	Log::getInstancia().logearMensajeEnModo("Se cargaron valores del personaje correctamente", Log::MODO_DEBUG);
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

Personaje& Parser::getPersonaje() const
{
	return *unPersonaje;
}

std::vector<Capa*> Parser::getCapas() const
{
	return Capas;

}

void Parser::FreeInstancia()
{
	delete getInstancia().unaVentana;
	delete  getInstancia().unEscenario;
	delete getInstancia().unPersonaje;
	for (size_t i = 0; i < getInstancia().Capas.size(); i++) {
		delete getInstancia().Capas.at(i);		
	}
	getInstancia().Capas.clear();
}

Parser::~Parser()
{
}

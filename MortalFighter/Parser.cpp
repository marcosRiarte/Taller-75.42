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
		if (ventana.get("anchopx", ANCHO_PX_VENTANA).isNumeric()) 
			try {
				anchoPxVentana = (ventana.get("anchopx", ANCHO_PX_VENTANA).asInt());
			} catch (...) {
				anchoPxVentana = ANCHO_PX_VENTANA;
				Log::getInstancia().logearMensajeEnModo("Se carga anchopx de la ventana por defecto", Log::MODO_WARNING);
			}
		else {
			anchoPxVentana = ANCHO_PX_VENTANA;
			Log::getInstancia().logearMensajeEnModo("Se carga anchopx de la ventana por defecto", Log::MODO_WARNING);
		}

		if (ventana.get("altopx", ALTO_PX_VENTANA).isNumeric())
			try {
				altoPxVentana = (ventana.get("altopx", ALTO_PX_VENTANA).asInt());
			} catch (...) {
				altoPxVentana = ALTO_PX_VENTANA;
				Log::getInstancia().logearMensajeEnModo("Se carga altopx de la ventana por defecto", Log::MODO_WARNING);
			}
		else {
			altoPxVentana = ALTO_PX_VENTANA;
			Log::getInstancia().logearMensajeEnModo("Se carga altopx de la ventana por defecto", Log::MODO_WARNING);
		}

		if (ventana.get("ancho", ANCHO_VENTANA).isNumeric())
			try {
				anchoVentana = (ventana.get("ancho", ANCHO_VENTANA).asFloat());
			}
			catch (...) {
				anchoVentana = ANCHO_VENTANA;
				Log::getInstancia().logearMensajeEnModo("Se carga ancho de la ventana por defecto", Log::MODO_WARNING);
			}
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
		if (escenario.get("ancho", ANCHO_ESCENARIO).isNumeric())
			try {
				anchoEscenario = (escenario.get("ancho", ANCHO_ESCENARIO).asFloat());
				}
			catch (...) {
				anchoEscenario = ANCHO_ESCENARIO;
				Log::getInstancia().logearMensajeEnModo("Se carga ancho del escenario por defecto", Log::MODO_WARNING);
			}
		else {
			anchoEscenario = ANCHO_ESCENARIO;
			Log::getInstancia().logearMensajeEnModo("Se carga ancho del escenario por defecto", Log::MODO_WARNING);
		}

		if (escenario.get("alto", ALTO_ESCENARIO).isNumeric())
			try {
				altoEscenario = (escenario.get("alto", ALTO_ESCENARIO).asFloat());
			}
			catch (...) {
				altoEscenario = ALTO_ESCENARIO;
				Log::getInstancia().logearMensajeEnModo("Se carga alto del escenario por defecto", Log::MODO_WARNING);
			}
		else {
			altoEscenario = ALTO_ESCENARIO;
			Log::getInstancia().logearMensajeEnModo("Se carga alto del escenario por defecto", Log::MODO_WARNING);
		}

		if (escenario.get("ypiso", Y_PISO_ESCENARIO).isNumeric())
			try {
				yPisoEscenario = (escenario.get("ypiso", Y_PISO_ESCENARIO).asFloat());
			}
			catch (...) {
				yPisoEscenario = Y_PISO_ESCENARIO;
				Log::getInstancia().logearMensajeEnModo("Se carga piso del escenario por defecto", Log::MODO_WARNING);
			}
		else {
			yPisoEscenario = Y_PISO_ESCENARIO;
			Log::getInstancia().logearMensajeEnModo("Se carga piso del escenario por defecto", Log::MODO_WARNING);
		}
		
	}

	Validador::ValidarEscenario(&anchoEscenario, &altoEscenario, &yPisoEscenario);
	unEscenario = new Escenario(anchoEscenario, altoEscenario, yPisoEscenario);
	Log::getInstancia().logearMensajeEnModo("Se cargaron valores del escenario correctamente", Log::MODO_DEBUG);

	Json::Value capas;
	capas = raiz["capas"];
	float anchoCapas;
	std::string fondo;

	if (!capas || capas.size() == 0){
		Log::getInstancia().logearMensajeEnModo("  [BAD] Fallo el parseo de las capas", Log::MODO_WARNING);
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
			else
				Log::getInstancia().logearMensajeEnModo("Se carga capa por defecto", Log::MODO_WARNING);

			if (capas[i].get("ancho", ANCHO_CAPA).isNumeric())
				try {
					anchoCapas = (capas[i].get("ancho", ANCHO_CAPA).asFloat());
				}
				catch (...) {
					anchoCapas = ANCHO_CAPA;
					Log::getInstancia().logearMensajeEnModo("Se carga ancho de capa por defecto", Log::MODO_WARNING);
				}
			else {
				anchoCapas = ANCHO_CAPA;
				Log::getInstancia().logearMensajeEnModo("Se carga ancho de capa por defecto", Log::MODO_WARNING);
			}

			int zIndexCapa = ZINDEX_CAPA;
			if (capas[i].get("zindex", ZINDEX_CAPA).isNumeric())
				try {
					zIndexCapa = (capas[i].get("zindex", ZINDEX_CAPA).asInt());
				}
				catch (...) {
					Log::getInstancia().logearMensajeEnModo("Se carga z-index de capa por defecto", Log::MODO_WARNING);
				}
			else
				Log::getInstancia().logearMensajeEnModo("Se carga z-index de capa por defecto", Log::MODO_WARNING);
									
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
		if (personaje.get("ancho", ANCHO_PERSONAJE).isNumeric())
			try {
				ancho = (personaje.get("ancho", ANCHO_PERSONAJE).asFloat());
			}
			catch (...) {
				ancho = ANCHO_PERSONAJE;
				Log::getInstancia().logearMensajeEnModo("Se carga ancho del personaje por defecto", Log::MODO_WARNING);
			}
		else {
			ancho = ANCHO_PERSONAJE;
			Log::getInstancia().logearMensajeEnModo("Se carga ancho del personaje por defecto", Log::MODO_WARNING);
		}

		if (personaje.get("alto", ALTO_PERSONAJE).isNumeric())
			try {
				alto = (personaje.get("alto", ALTO_PERSONAJE).asFloat());
			}
			catch (...) {
				alto = ALTO_PERSONAJE;
				Log::getInstancia().logearMensajeEnModo("Se carga alto del personaje por defecto", Log::MODO_WARNING);
			}
		else {
			alto = ALTO_PERSONAJE;
			Log::getInstancia().logearMensajeEnModo("Se carga alto del personaje por defecto", Log::MODO_WARNING);
		}

		if (personaje.get("zindex", ZINDEX).isNumeric())
			try {
				zIndex = (personaje.get("zindex", ZINDEX).asInt());
			}
			catch (...) {
				zIndex = ZINDEX;
				Log::getInstancia().logearMensajeEnModo("Se carga z-index del personaje por defecto", Log::MODO_WARNING);
			}
		else {
			zIndex = ZINDEX;
			Log::getInstancia().logearMensajeEnModo("Se carga z-index del personaje por defecto", Log::MODO_WARNING);
		}

		if (personaje.get("sprites", SPRITE_DEFAULT).isString())
			sprites = (personaje.get("sprites", SPRITE_DEFAULT).asString());
		else {
			sprites = SPRITE_DEFAULT;
			Log::getInstancia().logearMensajeEnModo("Se carga sprite del personaje por defecto", Log::MODO_WARNING);
		}

		if (personaje.get("orientacion", ORIENTACION_PERSONAJE).isString())
			orientacion = (personaje.get("orientacion", ORIENTACION_PERSONAJE).asString());
		else {
			orientacion = ORIENTACION_PERSONAJE;
			Log::getInstancia().logearMensajeEnModo("Se carga orientación del personaje por defecto", Log::MODO_WARNING);
		}
		
		if (personaje.get("CaminarParaAdelante", CAMINARPARAADELANTE_DEFAULT).isString())
			CaminarParaAdelante = (personaje.get("CaminarParaAdelante", CAMINARPARAADELANTE_DEFAULT).asString());
		else {
			CaminarParaAdelante = CAMINARPARAADELANTE_DEFAULT;
			Log::getInstancia().logearMensajeEnModo("Se carga sprite CaminarParaAdelante del personaje por defecto", Log::MODO_WARNING);
		}

		if (personaje.get("CaminarParaAtras", CAMINARPARAATRAS_DEFAULT).isString())
			CaminarParaAtras = (personaje.get("CaminarParaAtras", CAMINARPARAATRAS_DEFAULT).asString());
		else {
			CaminarParaAtras = CAMINARPARAATRAS_DEFAULT;
			Log::getInstancia().logearMensajeEnModo("Se carga sprite CaminarParaAtras del personaje por defecto", Log::MODO_WARNING);
		}

		if (personaje.get("Quieto", QUIETO_DEFAULT).isString())
			Quieto = (personaje.get("Quieto", QUIETO_DEFAULT).asString());
		else {
			Quieto = QUIETO_DEFAULT;
			Log::getInstancia().logearMensajeEnModo("Se carga sprite Quieto del personaje por defecto", Log::MODO_WARNING);
		}

		if (personaje.get("Salto", SALTO_DEFAULT).isString())
			Salto = (personaje.get("Salto", SALTO_DEFAULT).asString());
		else {
			Salto = SALTO_DEFAULT;
			Log::getInstancia().logearMensajeEnModo("Se carga sprite Salto del personaje por defecto", Log::MODO_WARNING);
		}

		if (personaje.get("SaltoDiagonal", SALTODIAGONAL_DEFAULT).isString())
			SaltoDiagonal = (personaje.get("SaltoDiagonal", SALTODIAGONAL_DEFAULT).asString());
		else {
			SaltoDiagonal = SALTODIAGONAL_DEFAULT;
			Log::getInstancia().logearMensajeEnModo("Se carga sprite SaltoDiagonal del personaje por defecto", Log::MODO_WARNING);
		}

		if (personaje.get("Caida", CAIDA_DEFAULT).isString())
			Caida = (personaje.get("Caida", CAIDA_DEFAULT).asString());
		else {
			Caida = CAIDA_DEFAULT;
			Log::getInstancia().logearMensajeEnModo("Se carga sprite Caida del personaje por defecto", Log::MODO_WARNING);
		}
		
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

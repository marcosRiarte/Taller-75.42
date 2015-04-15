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
		anchoPxVentana = (ventana.get("anchopx", ANCHO_PX_VENTANA).asInt());
		altoPxVentana = (ventana.get("altopx", ALTO_PX_VENTANA).asInt());
		anchoVentana = (ventana.get("ancho", ANCHO_VENTANA).asFloat());
		Log::getInstancia().logearMensajeEnModo("Se cargaron valores de la ventana correctamente", Log::MODO_DEBUG);
	}

	Validador::ValidarVentana(&anchoPxVentana, &altoPxVentana, &anchoVentana);
	unaVentana = new Ventana(anchoPxVentana, altoPxVentana, anchoVentana);

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
		anchoEscenario = (escenario.get("ancho", ANCHO_ESCENARIO).asFloat());
		altoEscenario = (escenario.get("alto", ALTO_ESCENARIO).asFloat());
		yPisoEscenario = (escenario.get("ypiso", Y_PISO_ESCENARIO).asFloat());
		Log::getInstancia().logearMensajeEnModo("Se cargaron valores del escenario correctamente", Log::MODO_DEBUG);
	}

	Validador::ValidarEscenario(&anchoEscenario, &altoEscenario, &yPisoEscenario);
	unEscenario = new Escenario(anchoEscenario, altoEscenario, yPisoEscenario);

	Json::Value capas;
	capas = raiz["capas"];
	float anchoCapas;
	std::string fondo;

	if (!capas){
		Log::getInstancia().logearMensajeEnModo("Fallo el parseo de las capas", Log::MODO_WARNING);
		fondo = FONDO_DEFAULT;
		anchoCapas = ANCHO_CAPA;
		//xjose 1000 modifico el validador agregando 1 argumento
		Validador::ValidarCapas(&anchoCapas, &fondo);
		Capas.push_back(new Capa(fondo, anchoCapas, 0));
		Log::getInstancia().logearMensajeEnModo("Se cargaron capas por defecto", Log::MODO_WARNING);
	}
	else{
		for (size_t i = 0; i < capas.size(); i++) {
			//xjose 1001 aca si pusiste asdlkaslkd.png te lo toma, hay que validar
			std::string fondo(capas[i].get("imagen_fondo", FONDO_DEFAULT).asString());
			anchoCapas = (capas[i].get("ancho", ANCHO_CAPA).asFloat());
			int zIndexCapa = (capas[i].get("zindex", 0).asInt());			
			//Xjose 1000 valido que exista el archivo de capas
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
	//Xjose 1 agrego los string
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
		//xjose 2 agrego los default y tengo que definir los define....
		CaminarParaAdelante = CAMINARPARAADELANTE_DEFAULT;
		CaminarParaAtras = CAMINARPARAATRAS_DEFAULT;
		Quieto = QUIETO_DEFAULT;
		Salto = SALTO_DEFAULT;
		SaltoDiagonal = SALTODIAGONAL_DEFAULT;
		Caida = CAIDA_DEFAULT;
		//XJOSE HAY QUE REVISAR SI ESTE LOG TIENE QUE LOGUEAR ESPECIFICAMENTE QUE FALLO???
		Log::getInstancia().logearMensajeEnModo("Se cargaron valores del personaje por defecto", Log::MODO_WARNING);
	}
	else{
		ancho = (personaje.get("ancho", 20).asFloat());
		alto = (personaje.get("alto", 35).asFloat());
		zIndex = (personaje.get("zindex", 1).asInt());
		sprites = (personaje.get("sprites", SPRITE_DEFAULT).asString());
		orientacion = (personaje.get("orientacion", ORIENTACION_PERSONAJE).asString());
		//Xjose 4 obtengo los datos y los asigno
		CaminarParaAdelante = (personaje.get("CaminarParaAdelante", CAMINARPARAADELANTE_DEFAULT).asString());
		CaminarParaAtras = (personaje.get("CaminarParaAtras", CAMINARPARAATRAS_DEFAULT).asString());
		Quieto = (personaje.get("Quieto", QUIETO_DEFAULT).asString());
		Salto = (personaje.get("Salto", SALTO_DEFAULT).asString());
		SaltoDiagonal = (personaje.get("SaltoDiagonal", SALTODIAGONAL_DEFAULT).asString());
		Caida = (personaje.get("Caida", CAIDA_DEFAULT).asString());
		//XJOSE HAY QUE REVISAR SI ESTE LOG TIENE QUE LOGUEAR ESPECIFICAMENTE QUE FALLO???
		Log::getInstancia().logearMensajeEnModo("Se cargaron valores del personaje correctamente", Log::MODO_DEBUG);
	}
	//XJOSE 5 METO LOS DATOS EN EL VALIDADOR, 6 MODIFICAR FIRMA VALIDADOR, 7 MODIFICAR VALIDADOR
	Validador::ValidarPersonaje(&ancho, &alto, &zIndex, &orientacion, &sprites, &CaminarParaAdelante, &CaminarParaAtras, &Quieto, &Salto, &SaltoDiagonal, &Caida);
	//XJOSE8 MODIFICAR ATRIBUTOS Y CONSTRUCTORES DE PERSONAJE Y LOS DESTRUCTORES
	unPersonaje = new Personaje(ancho, alto, zIndex, orientacion, sprites, CaminarParaAdelante, CaminarParaAtras, Quieto, Salto, SaltoDiagonal, Caida);

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

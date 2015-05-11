#include "Parser.h"
#include "ConversorDeEventos.h"
#include "stdafx.h"

Parser& Parser::getInstancia() {

	static Parser instancia;
	// Se garantiza que será destruido.
	// Se instancia en el primer uso.
	return instancia;
}

Parser::Parser() { 
}


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


	//VENTANA
	Json::Value ventana;
	ventana = raiz["ventana"];

	validadorDeVentana = new ValidadorDeVentana();
	validadorDeVentana->validarVentanaDesde(ventana);

	//ESCENARIO
	Json::Value escenario;
	escenario = raiz["escenario"];

	validadorDeEscenario = new ValidadorDeEscenario();
	validadorDeEscenario->validarEscenarioDesde(escenario);

	//CAPAS
	Json::Value capas;
	capas = raiz["capas"];

	validadorDeCapas = new ValidadorDeCapas();
	if (!validadorDeCapas->validarCapasDesde(capas)) return false;

	//PERSONAJES
	Json::Value personajes;
	personajes = raiz["personajes"];
	
	validadorDePersonajes = new ValidadorDePersonajes();
	if (!validadorDePersonajes->validarPersonajesDesdeConEscenarioYventana(personajes, validadorDeEscenario->getEscenario(), validadorDeVentana->getVentana()))
		return false;
	
	validadorDeEscenario->validaryPisoCon(validadorDePersonajes->getPersonajes()->at(0)->getAlto());

	//PELEA
	Json::Value pelea;
	pelea = raiz["pelea"];

	validadorDePelea = new ValidadorDePelea();
	validadorDePelea->validarPeleaDesdeParaLosPeronajes(pelea, validadorDePersonajes->getPersonajes());

	//Parseo del color    
	Json::Value color_alternativo;
	color_alternativo = raiz["color_alternativo"];
	int h_inicial;
	int h_final;
	int desplazamiento;

	if (!color_alternativo)
	{
		Log::getInstancia().logearMensajeEnModo("[BAD] Fallo el parseo del color", Log::MODO_WARNING);
	}
	//Valida los campos

	if (color_alternativo.isMember("h_inicial") && color_alternativo.get("h_inicial", H_INICIAL).isNumeric() && color_alternativo.get("h_inicial", H_INICIAL) < INT_MAX && color_alternativo.get("h_inicial", H_INICIAL) > -INT_MAX)
		h_inicial = color_alternativo.get("h_inicial", H_INICIAL).asInt();
	else {
		h_inicial = H_INICIAL;
		Log::getInstancia().logearMensajeEnModo("Se carga HUE INICIAL por defecto", Log::MODO_WARNING);
	}
	if (color_alternativo.isMember("h_final") && color_alternativo.get("h_final", H_FINAL).isNumeric() && color_alternativo.get("h_final", H_FINAL) < INT_MAX && color_alternativo.get("h_final", H_FINAL) > -INT_MAX)
		h_final = color_alternativo.get("h_final", H_FINAL).asInt();
	else {
		h_final = H_FINAL;
		Log::getInstancia().logearMensajeEnModo("Se carga HUE FINAL por defecto", Log::MODO_WARNING);
	}
	if (color_alternativo.isMember("desplazamiento") && color_alternativo.get("desplazamiento", DESPLAZAMIENTO).isNumeric() && color_alternativo.get("desplazamiento", DESPLAZAMIENTO) < INT_MAX && color_alternativo.get("desplazamiento", DESPLAZAMIENTO) > -INT_MAX)
		desplazamiento = color_alternativo.get("desplazamiento", DESPLAZAMIENTO).asInt();
	else {
		desplazamiento = DESPLAZAMIENTO;
		Log::getInstancia().logearMensajeEnModo("Se carga HUE FINAL por defecto", Log::MODO_WARNING);
	}

	if (h_final < h_inicial)
	{
		std::string mensaje = "Hue final mayor que el inicial, se toma el modulo del intervalo";
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_WARNING);
		int aux = h_final;
		h_final = h_inicial;
		h_inicial = aux;
	}
	if (h_final == h_inicial)
	{
		Log::getInstancia().logearMensajeEnModo("Intervalo nulo de hue nulo,tomo valores por default", Log::MODO_WARNING);
		h_final = 0;
		h_inicial = 0;

	}
	this->colorAlternativo.push_back(h_inicial);
	this->colorAlternativo.push_back(h_final);
	this->colorAlternativo.push_back(desplazamiento);
	Log::getInstancia().logearMensajeEnModo("HUE y desplazamiento de rango valido", Log::MODO_DEBUG);
		
	//PARSEO DE LOS CONTROLES
	validadorDelControlador = new ValidadorDelControlador();

	//CONTROL 1
	Json::Value control_1;
	control_1 = raiz["control_1"];

	validadorDelControlador->validarControladorDesde(control_1);

	//CONTROL 2
	Json::Value control_2;
	control_2 = raiz["control_2"];

	validadorDelControlador->validarControladorDesde(control_2);
	
	return true;
}

Escenario& Parser::getEscenario() const
{
	return *(validadorDeEscenario->getEscenario());
}

Ventana& Parser::getVentana() const
{
	return *(validadorDeVentana->getVentana());
}

Controlador* Parser::getControlador1(){
	return validadorDelControlador->getControlador1();
}

Controlador* Parser::getControlador2(){
	return validadorDelControlador->getControlador2();
}

std::string Parser::getPelea()const
{
	return validadorDePelea->getPelea();
}

std::vector<Personaje*> Parser::getPersonajes() const
{
	return *(validadorDePersonajes->getPersonajes());
}

std::vector<Capa*> Parser::getCapas() const
{
	return *(validadorDeCapas->getCapas());

}
std::vector<int> Parser::getColorAlternativo()
{
	return this->colorAlternativo;
}


void Parser::FreeInstancia()
{
	delete getInstancia().validadorDeVentana;
	delete  getInstancia().validadorDeEscenario;
	delete getInstancia().validadorDePersonajes;
	delete getInstancia().validadorDeCapas;
}

Parser::~Parser()
{
}

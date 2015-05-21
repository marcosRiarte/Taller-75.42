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

	//COLOR  
	Json::Value color_alternativo;
	color_alternativo = raiz["color_alternativo"];

	validadorDelColor = new ValidadorDelColor();
	validadorDelColor->validarColorDesde(color_alternativo);

		
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
std::vector<double> Parser::getColorAlternativo()
{
	return validadorDelColor->getColorAlternativo();
}


void Parser::FreeInstancia()
{
	delete getInstancia().validadorDeVentana;
	delete  getInstancia().validadorDeEscenario;
	delete getInstancia().validadorDePersonajes;
	delete getInstancia().validadorDeCapas;
	delete getInstancia().validadorDelColor;
	delete getInstancia().validadorDePelea;
}

Parser::~Parser()
{
}

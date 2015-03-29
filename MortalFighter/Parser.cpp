#include "stdafx.h"
#include "Parser.h"


Parser &Parser::getInstancia() {

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
	if (!prueba.is_open())
		return false;

	bool parseoExitoso = lector.parse(prueba, raiz, true);

	if (!parseoExitoso) {
		std::string mensaje = "Fallo el parseo, se carga json por defecto" + lector.getFormattedErrorMessages();
		const char * c = mensaje.c_str();
		std::ifstream prueba("pruebaDefecto.json", std::ifstream::binary);
		bool parseoExitoso = lector.parse(prueba, raiz, true);
	}

	Json::Value ventana;
	ventana = raiz["ventana"];
	int anchoPxVentana(ventana.get("anchoPx",800).asInt());
	int altoPxVentana(ventana.get("altoPx", 600).asInt());
	float anchoVentana(ventana.get("ancho", 500).asFloat());

	unaVentana = new Ventana(anchoPxVentana, altoPxVentana, anchoVentana);

	Json::Value escenario;
	escenario = raiz["escenario"];
	float anchoEscenario(escenario.get("ancho", 1000.5).asFloat());
	float altoEscenario(escenario.get("alto", 150).asFloat());
	float yPisoEscenario(escenario.get("y­piso", 20).asFloat());

	unEscenario = new Escenario(anchoEscenario, altoEscenario, yPisoEscenario);

	Json::Value capas;
	capas = raiz["capas"];

	for (size_t i = 0; i < capas.size(); i++) {
		std::string fondo(capas[i].get("imagen_fondo", "fondo1.png").asString());
		float anchoCapas(capas[i].get("ancho", 500).asFloat());
		Capas.push_back(new Capa(fondo, anchoCapas));
	}

	Json::Value personaje;
	personaje = raiz["personaje"];
	float ancho(personaje.get("ancho", 20).asFloat());
	float alto(personaje.get("alto", 35).asFloat());
	int zIndex(personaje.get("­z­index", 1).asInt());
	std::string sprites(personaje.get("sprites", "SpriteSheet.png").asString());

	unPersonaje = new Personaje(ancho, alto, zIndex, sprites);

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

Parser::~Parser()
{
}

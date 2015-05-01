#pragma once
#include "Capa.h"
#include "Ventana.h"
#include "Escenario.h"
#include "Personaje.h"
#include "Controlador.h"
#include "Log.h"
#include "Validador.h"

#define PRUEBA_JSON "prueba.json"
#define PRUEBA_JSON_DEFECTO "pruebaDefecto.json"

#define ANCHO_MIN 640
#define ALTO_MIN 480
#define ANCHO_PX_VENTANA 80
#define ALTO_PX_VENTANA 60
#define ANCHO_VENTANA 200.0f

#define FPS 60.0f
const float MSxCUADRO = 1000.0f / FPS;

#define ANCHO_ESCENARIO 1000.5f
#define MAX_ANCHO_ESCENARIO 4000.0f
#define ALTO_ESCENARIO 150.0f
#define MAX_ALTO_ESCENARIO 2000.0f
#define Y_PISO_ESCENARIO 20.0f

#define ANCHO_CAPA 500.0f
#define ZINDEX_CAPA 0

#define ANCHO_PERSONAJE 50.0f
#define MAX_ANCHO_PERSONAJE 1000.0f
#define ALTO_PERSONAJE 70.0f
#define MAX_ALTO_PERSONAJE 1000.0f

#define ZINDEX 1
#define ORIENTACION_PERSONAJE "DER"
#define SPRITE_DEFAULT "ima/sprites/player_default.png"
#define FONDO_DEFAULT "ima/bkg/default_capa.png" // al ser varias capas la idea esa usar esta por que va a permitir que se vean el resto de las que si estan
#define CAMINARPARAADELANTE_DEFAULT "CaminarParaAdelante"
#define CAMINARPARAATRAS_DEFAULT "CaminarParaAtras"
#define QUIETO_DEFAULT "Quieto"
#define SALTO_DEFAULT "Salto"
#define SALTODIAGONAL_DEFAULT "SaltoDiagonal"
#define CAIDA_DEFAULT "Caida"
#define LIU_KANG "LiuKang"

#define ARRIBA_DEFAULT_1 "up"
#define ABAJO_DEFAULT_1 "down"
#define IZQUIERDA_DEFAULT_1 "left"
#define DERECHA_DEFAULT_1 "right"
#define DEFENSA_DEFAULT_1 "z"
#define ARMA_DEFAULT_1 "x"
#define G_BAJO_DEFAULT_1 "c"
#define G_ALTO_DEFAULT_1 "v"
#define P_BAJA_DEFAULT_1 "b"
#define P_ALTA_DEFAULT_1 "n"
#define ARRIBA_DEFAULT_2 "w"
#define ABAJO_DEFAULT_2 "s"
#define IZQUIERDA_DEFAULT_2 "a"
#define DERECHA_DEFAULT_2 "d"
#define DEFENSA_DEFAULT_2 "j"
#define ARMA_DEFAULT_2 "u"
#define G_BAJO_DEFAULT_2 "k"
#define G_ALTO_DEFAULT_2 "l"
#define P_BAJA_DEFAULT_2 "i"
#define P_ALTA_DEFAULT_2 "o"
#define REINICIAR_DEFAULT "r"
#define SALIR_DEFAULT "esc"

class Parser
{
public:	
	static Parser& getInstancia();
	bool parsear(std::string nombreDelArchivo);

	Escenario& getEscenario() const;
	Ventana& getVentana() const;
	Controlador* getControlador1();
	Controlador* getControlador2();
	std::vector<Personaje*> getPersonajes() const;
	std::vector<Capa*> getCapas() const;

	static void FreeInstancia();

private:	
	//Constructor privado
	explicit Parser();
	
	std::vector<Capa*> Capas;
	std::vector<Personaje*> Personajes;
	Ventana* unaVentana;
	Escenario* unEscenario;
	Controlador* controlador1;
	Controlador* controlador2;

	virtual ~Parser();

	Parser(Parser const&) = delete;
	void operator =(Parser const&) = delete;	
};

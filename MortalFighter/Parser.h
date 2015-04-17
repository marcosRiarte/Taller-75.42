#pragma once
#include "Capa.h"
#include "Ventana.h"
#include "Escenario.h"
#include "Personaje.h"
#include "Log.h"
#include "Validador.h"

#define ANCHO_PX_VENTANA 800
#define ALTO_PX_VENTANA 600
#define ANCHO_VENTANA 200.0f

#define ANCHO_ESCENARIO 1000.5f
#define ALTO_ESCENARIO 150.0f
#define Y_PISO_ESCENARIO 20.0f

#define ANCHO_CAPA 500.0f
#define ZINDEX_CAPA 0

#define ANCHO_PERSONAJE 50.0f
#define MAX_ANCHO_PERSONAJE 1000.0f
#define ALTO_PERSONAJE 70.0f
#define MAX_ALTO_PERSONAJE 1000.0f

#define ZINDEX 4
#define ORIENTACION_PERSONAJE "DER"
#define SPRITE_DEFAULT "ima/sprites/player_default.png"
#define FONDO_DEFAULT "ima/bkg/default_capa.png" // al ser varias capas la idea esa usar esta por que va a permitir que se vean el resto de las que si estan
#define CAMINARPARAADELANTE_DEFAULT "CaminarParaAdelante"
#define CAMINARPARAATRAS_DEFAULT "CaminarParaAtras"
#define QUIETO_DEFAULT "Quieto"
#define SALTO_DEFAULT "Salto"
#define SALTODIAGONAL_DEFAULT "SaltoDiagonal"
#define CAIDA_DEFAULT "Caida"
class Parser
{
public:	
	static Parser& getInstancia();
	bool parsear(std::string nombreDelArchivo);

	Escenario& getEscenario() const;
	Ventana& getVentana() const;
	Personaje& getPersonaje() const;
	std::vector<Capa*> getCapas() const;

	static void FreeInstancia();

private:	
	//Constructor privado
	explicit Parser();
	
	std::vector<Capa*> Capas;
	Personaje* unPersonaje;
	Ventana* unaVentana;
	Escenario* unEscenario;

	virtual ~Parser();

	Parser(Parser const&) = delete;
	void operator =(Parser const&) = delete;	
};

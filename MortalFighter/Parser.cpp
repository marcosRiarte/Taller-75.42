#include "Parser.h"
#include "ConversorDeEventos.h"
#include "stdafx.h"

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

	std::string Golpeado;
	std::string PatadaAlta;
	std::string Agacharse;

	std::string Caida;
	std::string nombre;
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
		nombre = LIU_KANG;

		Golpeado = GOLPEADO_DEFAULT;
		Agacharse = AGACHARSE_DEFAULT;
		PatadaAlta = PATADAALTA_DEFAULT;

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
			//xjose
			if (personajes[i].isMember("PatadaAlta") && personajes[i].get("PatadaAlta", PATADAALTA_DEFAULT).isString())
				PatadaAlta = (personajes[i].get("PatadaAlta", PATADAALTA_DEFAULT).asString());
			else {
				PatadaAlta = PATADAALTA_DEFAULT;
				Log::getInstancia().logearMensajeEnModo("Se carga sprite PatadaAlta del personaje por defecto", Log::MODO_WARNING);
			}
			if (personajes[i].isMember("Agacharse") && personajes[i].get("Agacharse", AGACHARSE_DEFAULT).isString())
				Agacharse = (personajes[i].get("Agacharse", AGACHARSE_DEFAULT).asString());
			else {
				Agacharse = AGACHARSE_DEFAULT;
				Log::getInstancia().logearMensajeEnModo("Se carga sprite Agacharse del personaje por defecto", Log::MODO_WARNING);
			}
			if (personajes[i].isMember("Golpeado") && personajes[i].get("Golpeado", GOLPEADO_DEFAULT).isString())
				Golpeado = (personajes[i].get("Golpeado", GOLPEADO_DEFAULT).asString());
			else {
				Golpeado = GOLPEADO_DEFAULT;
				Log::getInstancia().logearMensajeEnModo("Se carga sprite Golpeado del personaje por defecto", Log::MODO_WARNING);
			}

			//xjose

			if (personajes[i].isMember("Caida") && personajes[i].get("Caida", CAIDA_DEFAULT).isString())
				Caida = (personajes[i].get("Caida", CAIDA_DEFAULT).asString());
			else {
				Caida = CAIDA_DEFAULT;
				Log::getInstancia().logearMensajeEnModo("Se carga sprite Caida del personaje por defecto", Log::MODO_WARNING);
			}

			//xjose  TODO falta validar agacharse, golpeado, patadaalta
			errorPersonaje = Validador::ValidarPersonaje(&ancho, &alto, &zIndex, &orientacion, &sprites, &CaminarParaAdelante, &CaminarParaAtras, &Quieto, &Salto, &SaltoDiagonal, &Caida);//, &nombre
			if (errorPersonaje){
				return false;
			}
			Personajes.push_back(new Personaje(ancho, alto, zIndex, orientacion, sprites, CaminarParaAdelante, CaminarParaAtras, Quieto, Salto, SaltoDiagonal, Caida, PatadaAlta, Golpeado, Agacharse, nombre));
		}
	}
	

	Log::getInstancia().logearMensajeEnModo("Se cargaron valores del personaje correctamente", Log::MODO_DEBUG);
	Validador::ValidarEscenario(&anchoEscenario, &altoEscenario, &alto, &yPisoEscenario);
	unEscenario = new Escenario(anchoEscenario, altoEscenario, yPisoEscenario);
	Log::getInstancia().logearMensajeEnModo("Se cargaron valores del escenario correctamente", Log::MODO_DEBUG);

	// en esta parte se desarma todo......
	
	//Parseo de la pelea
	Json::Value pelea;
	pelea = raiz["pelea"];
	std::string fighters;
	if (!pelea)
	{
		Log::getInstancia().logearMensajeEnModo("[BAD] Fallo el parseo de la pelea", Log::MODO_WARNING);
	}
	//Valida los campos

	if (pelea.isMember("fighters") && pelea.get("fighters", PELEA_INICIAL).isString())
		this->pelea = pelea.get("fighters", PELEA_INICIAL).asString();
	else {
		this->pelea = PELEA_INICIAL;
		Log::getInstancia().logearMensajeEnModo("Se carga el combate por defecto", Log::MODO_WARNING);
	}
	Log::getInstancia().logearMensajeEnModo("Se cargo el combate con exito", Log::MODO_DEBUG);
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
	std::string arriba, abajo, izquierda, derecha, golpe_bajo, golpe_alto;
	std::string patada_baja, patada_alta, defensa, arma, reiniciar, salir;

	//CONTROL 1
	Json::Value control_1;
	control_1 = raiz["control_1"];

	ConversorDeEventos* unConversorDeEventos = new ConversorDeEventos();
	controlador1 = new Controlador();

	arriba = ARRIBA_DEFAULT_1;
	abajo = ABAJO_DEFAULT_1;
	izquierda = IZQUIERDA_DEFAULT_1;
	derecha = DERECHA_DEFAULT_1;
	defensa = DEFENSA_DEFAULT_1;
	arma = ARMA_DEFAULT_1;
	reiniciar = REINICIAR_DEFAULT;
	salir = SALIR_DEFAULT;
	golpe_bajo = G_BAJO_DEFAULT_1;
	golpe_alto = G_ALTO_DEFAULT_1;
	patada_baja = P_BAJA_DEFAULT_1;
	patada_alta = P_ALTA_DEFAULT_1;
	
	if (!control_1){
		Log::getInstancia().logearMensajeEnModo("Fallo el parseo del Control 1, se cargara por defecto", Log::MODO_WARNING);
	}
	else{
		if ((control_1.isMember("arriba") && control_1.get("arriba", ARRIBA_DEFAULT_1).isString())){
			arriba = control_1.get("arriba", ARRIBA_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton arriba por defecto", Log::MODO_WARNING);
		}

		if ((control_1.isMember("abajo") && control_1.get("abajo", ABAJO_DEFAULT_1).isString())){
			abajo = control_1.get("abajo", ABAJO_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton abajo por defecto", Log::MODO_WARNING);
		}

		if ((control_1.isMember("izquierda") && control_1.get("izquierda", IZQUIERDA_DEFAULT_1).isString())){
			izquierda = control_1.get("izquierda", IZQUIERDA_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton izquierda por defecto", Log::MODO_WARNING);
		}

		if ((control_1.isMember("derecha") && control_1.get("derecha", DERECHA_DEFAULT_1).isString())){
			derecha = control_1.get("derecha", DERECHA_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton derecha por defecto", Log::MODO_WARNING);
		}

		if ((control_1.isMember("defensa") && control_1.get("defensa", DEFENSA_DEFAULT_1).isString())){
			defensa = control_1.get("defensa", DEFENSA_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton defensa por defecto", Log::MODO_WARNING);
		}

		if ((control_1.isMember("arma") && control_1.get("arma", ARMA_DEFAULT_1).isString())){
			arma = control_1.get("arma", ARMA_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton arma por defecto", Log::MODO_WARNING);
		}

		if ((control_1.isMember("reiniciar") && control_1.get("reiniciar", REINICIAR_DEFAULT).isString())){
			reiniciar = control_1.get("reiniciar", REINICIAR_DEFAULT).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton reiniciar por defecto", Log::MODO_WARNING);
		}

		if ((control_1.isMember("salir") && control_1.get("salir", SALIR_DEFAULT).isString())){
			salir = control_1.get("salir", SALIR_DEFAULT).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton salir por defecto", Log::MODO_WARNING);
		}

		if ((control_1.isMember("golpe_bajo") && control_1.get("golpe_bajo", G_BAJO_DEFAULT_1).isString())){
			golpe_bajo = control_1.get("golpe_bajo", G_BAJO_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton golpe_bajo por defecto", Log::MODO_WARNING);
		}

		if ((control_1.isMember("golpe_alto") && control_1.get("golpe_alto", G_ALTO_DEFAULT_1).isString())){
			golpe_alto = control_1.get("golpe_alto", G_ALTO_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton golpe_alto por defecto", Log::MODO_WARNING);
		}

		if ((control_1.isMember("patada_baja") && control_1.get("patada_baja", P_BAJA_DEFAULT_1).isString())){
			patada_baja = control_1.get("patada_baja", P_BAJA_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton patada_baja por defecto", Log::MODO_WARNING);
		}

		if ((control_1.isMember("patada_alta") && control_1.get("patada_alta", P_ALTA_DEFAULT_1).isString())){
			patada_alta = control_1.get("patada_alta", P_ALTA_DEFAULT_1).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton patada_alta por defecto", Log::MODO_WARNING);
		}
	}

	unConversorDeEventos->setAccion(ConversorDeEventos::UP, arriba);
	unConversorDeEventos->setAccion(ConversorDeEventos::DOWN, abajo);
	unConversorDeEventos->setAccion(ConversorDeEventos::RIGHT, derecha);
	unConversorDeEventos->setAccion(ConversorDeEventos::LEFT, izquierda);
	unConversorDeEventos->setAccion(ConversorDeEventos::HOLD, defensa);
	unConversorDeEventos->setAccion(ConversorDeEventos::REBOOT, reiniciar);
	unConversorDeEventos->setAccion(ConversorDeEventos::QUIT, salir);
	unConversorDeEventos->setAccion(ConversorDeEventos::LOW_PUNCH, golpe_bajo);
	unConversorDeEventos->setAccion(ConversorDeEventos::HIGH_PUNCH, golpe_alto);
	unConversorDeEventos->setAccion(ConversorDeEventos::LOW_KICK, patada_baja);
	unConversorDeEventos->setAccion(ConversorDeEventos::HIGH_KICK, patada_alta);

	controlador1->setConversorDeEventos(unConversorDeEventos);

	//CONTROL 2
	Json::Value control_2;
	control_2 = raiz["control_2"];

	ConversorDeEventos* otroConversorDeEventos = new ConversorDeEventos();
	controlador2 = new Controlador();

	arriba = ARRIBA_DEFAULT_2;
	abajo = ABAJO_DEFAULT_2;
	izquierda = IZQUIERDA_DEFAULT_2;
	derecha = DERECHA_DEFAULT_2;
	defensa = DEFENSA_DEFAULT_2;
	arma = ARMA_DEFAULT_2;
	reiniciar = REINICIAR_DEFAULT;
	salir = SALIR_DEFAULT;
	golpe_bajo = G_BAJO_DEFAULT_2;
	golpe_alto = G_ALTO_DEFAULT_2;
	patada_baja = P_BAJA_DEFAULT_2;
	patada_alta = P_ALTA_DEFAULT_2;

	if (!control_2){
		Log::getInstancia().logearMensajeEnModo("Fallo el parseo del Control 2, se cargara por defecto", Log::MODO_WARNING);
	}
	else{
		if ((control_2.isMember("arriba") && control_2.get("arriba", ARRIBA_DEFAULT_2).isString())){
			arriba = control_2.get("arriba", ARRIBA_DEFAULT_2).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton arriba por defecto", Log::MODO_WARNING);
		}

		if ((control_2.isMember("abajo") && control_2.get("abajo", ABAJO_DEFAULT_2).isString())){
			abajo = control_2.get("abajo", ABAJO_DEFAULT_2).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton abajo por defecto", Log::MODO_WARNING);
		}

		if ((control_2.isMember("izquierda") && control_2.get("izquierda", IZQUIERDA_DEFAULT_2).isString())){
			izquierda = control_2.get("izquierda", IZQUIERDA_DEFAULT_2).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton izquierda por defecto", Log::MODO_WARNING);
		}

		if ((control_2.isMember("derecha") && control_2.get("derecha", DERECHA_DEFAULT_2).isString())){
			derecha = control_2.get("derecha", DERECHA_DEFAULT_2).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton derecha por defecto", Log::MODO_WARNING);
		}

		if ((control_2.isMember("defensa") && control_2.get("defensa", DEFENSA_DEFAULT_2).isString())){
			defensa = control_2.get("defensa", DEFENSA_DEFAULT_2).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton defensa por defecto", Log::MODO_WARNING);
		}

		if ((control_2.isMember("arma") && control_2.get("arma", ARMA_DEFAULT_2).isString())){
			arma = control_2.get("arma", ARMA_DEFAULT_2).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton arma por defecto", Log::MODO_WARNING);
		}

		if ((control_2.isMember("reiniciar") && control_2.get("reiniciar", REINICIAR_DEFAULT).isString())){
			reiniciar = control_2.get("reiniciar", REINICIAR_DEFAULT).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton reiniciar por defecto", Log::MODO_WARNING);
		}

		if ((control_2.isMember("salir") && control_2.get("salir", SALIR_DEFAULT).isString())){
			salir = control_2.get("salir", SALIR_DEFAULT).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton salir por defecto", Log::MODO_WARNING);
		}

		if ((control_2.isMember("golpe_bajo") && control_2.get("golpe_bajo", G_BAJO_DEFAULT_2).isString())){
			golpe_bajo = control_2.get("golpe_bajo", G_BAJO_DEFAULT_2).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton golpe_bajo por defecto", Log::MODO_WARNING);
		}

		if ((control_2.isMember("golpe_alto") && control_2.get("golpe_alto", G_ALTO_DEFAULT_2).isString())){
			golpe_alto = control_2.get("golpe_alto", G_ALTO_DEFAULT_2).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton golpe_alto por defecto", Log::MODO_WARNING);
		}

		if ((control_2.isMember("patada_baja") && control_2.get("patada_baja", P_BAJA_DEFAULT_2).isString())){
			patada_baja = control_2.get("patada_baja", P_BAJA_DEFAULT_2).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton patada_baja por defecto", Log::MODO_WARNING);;
		}

		if ((control_2.isMember("patada_alta") && control_2.get("patada_alta", P_ALTA_DEFAULT_2).isString())){
			patada_alta = control_2.get("patada_alta", P_ALTA_DEFAULT_2).asString();
		}
		else{
			Log::getInstancia().logearMensajeEnModo("Se carga boton patada_alta por defecto", Log::MODO_WARNING);
		}
	}
	otroConversorDeEventos->setAccion(ConversorDeEventos::UP, arriba);
	otroConversorDeEventos->setAccion(ConversorDeEventos::DOWN, abajo);
	otroConversorDeEventos->setAccion(ConversorDeEventos::RIGHT, derecha);
	otroConversorDeEventos->setAccion(ConversorDeEventos::LEFT, izquierda);
	otroConversorDeEventos->setAccion(ConversorDeEventos::HOLD, defensa);
	otroConversorDeEventos->setAccion(ConversorDeEventos::REBOOT, reiniciar);
	otroConversorDeEventos->setAccion(ConversorDeEventos::QUIT, salir);
	otroConversorDeEventos->setAccion(ConversorDeEventos::LOW_PUNCH, golpe_bajo);
	otroConversorDeEventos->setAccion(ConversorDeEventos::HIGH_PUNCH, golpe_alto);
	otroConversorDeEventos->setAccion(ConversorDeEventos::LOW_KICK, patada_baja);
	otroConversorDeEventos->setAccion(ConversorDeEventos::HIGH_KICK, patada_alta);

	controlador2->setConversorDeEventos(otroConversorDeEventos);
	
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

Controlador* Parser::getControlador1(){
	return controlador1;
}

Controlador* Parser::getControlador2(){
	return controlador2;
}

std::string Parser::getPelea()const
{
	return this->pelea;
}

std::vector<Personaje*> Parser::getPersonajes() const
{
	return Personajes;
}

std::vector<Capa*> Parser::getCapas() const
{
	return Capas;

}
std::vector<int> Parser::getColorAlternativo()
{
	return this->colorAlternativo;
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

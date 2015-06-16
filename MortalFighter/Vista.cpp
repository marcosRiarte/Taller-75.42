#include "stdafx.h"
#include "SDL_ttf.h"
#include "Vista.h"
#include "Mundo.h"
#include "Log.h"
#include "MatizColor.h"
#include "Timer.h"
#include "Sonidos.h"


Vista::Vista(Mundo* unMundo, bool* error, bool habilitarAceleracionDeHardware)
{
	*error = false;
	//VIBRACION
	vibraciones = 0;
	retraso = VIBRACIONES;
	vibracion = false;
	estaVibrando = false;

	//Se inicializa SDLttf
	int TTF_Init(void);
	if (TTF_Init() == 0) {

		atexit(TTF_Quit);
		std::cout << "TTF inicializada" << std::endl;
	}
	this->fuente = TTF_OpenFont("./ima/ttf/mkx.ttf", 40);

	// Usa filtro anisotropico
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
	// Se inicia SDL_image
	IMG_Init(IMG_INIT_PNG);
	ventana = SDL_CreateWindow(TITULO_VENTANA, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Parser::getInstancia().getVentana().getAnchoPx(), Parser::getInstancia().getVentana().getAltoPx(), SDL_WINDOW_SHOWN);
	if (ventana == nullptr){
		std::string mensaje = "SDL_CreateWindow Error: ";
		const char* elError = SDL_GetError();
		mensaje += elError;
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_ERROR);
		SDL_Quit();
		*error = true;
		return;
	}

	std::string icono(ICONO);
	SDL_Surface* iconoSurf = IMG_Load(icono.c_str());
	SDL_SetWindowIcon(ventana, iconoSurf);

	if (habilitarAceleracionDeHardware)
		renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	else
		renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_TARGETTEXTURE);

	if (renderer == nullptr){
		SDL_DestroyWindow(ventana);
		std::string mensaje = "SDL_CreateRenderer Error: ";
		const char* elError = SDL_GetError();
		mensaje += elError;
		Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_ERROR);
		SDL_Quit();
		*error = true;
		return;
	}

	for (size_t i = 0; i < Parser::getInstancia().getCapas().size(); i++)
	{
		std::string imgFondo(Parser::getInstancia().getCapas().at(i)->getImagenFondo());
		SDL_Surface* superficieCapa = cargarSuperficieOptimizada(imgFondo);
		SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, superficieCapa);
		// se queda con la textura libero la superficie
		SDL_FreeSurface(superficieCapa);

		if (tex == nullptr){
			std::string mensaje = "SDL_CreateTextureFromSurface Error: ";
			const char* elError = SDL_GetError();
			mensaje += elError;
			Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_ERROR);
			*error = true;
			return;
		}

		Parser::getInstancia().getCapas().at(i)->setTexturaSDL(tex);
	}

	// inicializo la camara en el centro del escenario
	camaraXLog = -Parser::getInstancia().getEscenario().getAncho() / 2
		+ Parser::getInstancia().getVentana().getAncho() / 2;

	//Creo el número de cuadros en 0,
	numeroDeCuadroUno = 0;
	//y la lista de cuadros puntero a null
	listaDeCuadrosUno = nullptr;

	//Creo el número de cuadros en 0,
	numeroDeCuadroDos = 0;
	//y la lista de cuadros puntero a null
	listaDeCuadrosDos = nullptr;

	//****************************************************************
	// Texturas de Pantalla
	//****************************************************************

	//Se carga la textura del menu Princpial
	SDL_Surface* menu = cargarSuperficieOptimizada("ima/bkg/mainmenu.gif");
	this->texturaMenu = SDL_CreateTextureFromSurface(renderer, menu);
	//dos jugadores 
	SDL_Surface* botonPlayMode = cargarSuperficieOptimizada("ima/bkg/arcadeMode.png");
	this->texturaPlayMode = SDL_CreateTextureFromSurface(renderer, botonPlayMode);

	//Un jugador
	SDL_Surface* botonUnJugador = cargarSuperficieOptimizada("ima/bkg/modoCpu.png");
	this->texturaUnjugador = SDL_CreateTextureFromSurface(renderer, botonUnJugador);
	//Modo practica
	SDL_Surface* botonPractica = cargarSuperficieOptimizada("ima/bkg/trainingMode.png");
	this->texturaTrainig = SDL_CreateTextureFromSurface(renderer, botonPractica);

	//Recuadro de seleccion
	SDL_Surface* seleccion = cargarSuperficieOptimizada("ima/bkg/RecuadroMenu.png");
	SDL_SetColorKey(seleccion, SDL_TRUE, SDL_MapRGB(seleccion->format, 255, 255, 255));
	this->texturaRecuadro = SDL_CreateTextureFromSurface(renderer, seleccion);

	//Se cargan las texturas para el menu de seleccion de personajes
	//Fondo
	SDL_Surface* seleccionPersonajes = cargarSuperficieOptimizada("ima/bkg/the_Portal.png");
	this->texturaSeleccionPersonajes = SDL_CreateTextureFromSurface(renderer, seleccionPersonajes);
	//Grilla de personajes
	SDL_Surface* grillaPersonajes = cargarSuperficieOptimizada("ima/bkg/personajesEleccion.png");
	this->texturaGrillaPersonajes = SDL_CreateTextureFromSurface(renderer, grillaPersonajes);

	//Recuadro de seleccion de personajes
	SDL_Surface* recuadroPersonajes = cargarSuperficieOptimizada("ima/bkg/rectangulo.png");
	SDL_SetColorKey(recuadroPersonajes, SDL_TRUE, SDL_MapRGB(recuadroPersonajes->format, 255, 255,255));
	this->texturaRecuadroPersonajes = SDL_CreateTextureFromSurface(renderer, recuadroPersonajes);

	//Fondo luego de eleccion
	SDL_Surface* seleccionPersonajes2 = cargarSuperficieOptimizada("ima/bkg/the_Portal2.png");
	this->texturaSeleccionPersonajes2 = SDL_CreateTextureFromSurface(renderer, seleccionPersonajes2);
	
	//Se cargan los sprites:		

	//Dirección de la imagen de Sprites
	std::string dirImgPersonajeUno = Parser::getInstancia().getPelea()->getPersonaje1()->getSpriteDir();
	std::string dirImgPersonajeDos = Parser::getInstancia().getPelea()->getPersonaje2()->getSpriteDir();

	//Carga la imagen desde la ruta especificada
	SDL_Surface* SuperficieUno = cargarSuperficieOptimizada(dirImgPersonajeUno);
	SDL_Surface* SuperficieDos = cargarSuperficieOptimizada(dirImgPersonajeDos);

	//Seteo del color		
	std::string pelea = Parser::getInstancia().getPeleaComoString();
	double h_inicio = Parser::getInstancia().getColorAlternativo().at(0);
	double h_final = Parser::getInstancia().getColorAlternativo().at(1);;
	double deplazamiento = Parser::getInstancia().getColorAlternativo().at(2);

	AlfaVida = 200;

	if (MODO_COLOR){
		//Si ambos personajes son iguales,modifico la superficie
		if (Parser::getInstancia().getPelea()->getPersonaje1()->getSpriteDir() == Parser::getInstancia().getPelea()->getPersonaje2()->getSpriteDir())
		{
			MatizColor matiz(SuperficieDos);
			matiz.desplazarMatiz(h_inicio, h_final, deplazamiento);
		}
	}

	//Creación de la textura sobre la superficie
	texturaSpriteUno = SDL_CreateTextureFromSurface(renderer, SuperficieUno);
	texturaSpriteDos = SDL_CreateTextureFromSurface(renderer, SuperficieDos);
	SDL_FreeSurface(SuperficieUno);
	SDL_FreeSurface(SuperficieDos);

	capasVista = Parser::getInstancia().getCapas();
	//Ordeno las capas por su zindex para ser dibujadas
	OrdenarCapas();

	// Se crea textura para dibujar sensores
	SDL_Surface* sup = cargarSuperficieOptimizada("ima/bkg/texturaVerde.png");
	texturaVerde = SDL_CreateTextureFromSurface(renderer, sup);
	SDL_FreeSurface(sup);

	//Textura para la barra de vida
	superficieBarraDeVida = cargarSuperficieOptimizada("ima/bkg/barraDeVida.png");
	texturaBarraDeVida = SDL_CreateTextureFromSurface(renderer, superficieBarraDeVida);

	//Textura para la barra de vida roja
	superficieBarraDeVidaRoja = cargarSuperficieOptimizada("ima/bkg/barraDeVidaRoja.png");
	texturaBarraDeVidaRoja = SDL_CreateTextureFromSurface(renderer, superficieBarraDeVidaRoja);

	int anchoBarraDeVida = Parser::getInstancia().getVentana().getAnchoPx() / 2.2;
	int altoBarraDeVida = 12;

	int posXBarraDeVida1 = (Parser::getInstancia().getVentana().getAnchoPx() / 2) - anchoBarraDeVida - 10;
	int posXBarraDeVida2 = Parser::getInstancia().getVentana().getAnchoPx() / 2 + 10;

	int posYBarraDeVida = 10;
	int posYBarraDeVidaRoja = 40;

	barraDeVidaImagen1.x = 0;
	barraDeVidaImagen1.y = 0;
	barraDeVidaImagen1.w = superficieBarraDeVida->w;
	barraDeVidaImagen1.h = superficieBarraDeVida->h;

	barraRojaDeVidaImagen1.x = 0;
	barraRojaDeVidaImagen1.y = 0;
	barraRojaDeVidaImagen1.w = superficieBarraDeVidaRoja->w;
	barraRojaDeVidaImagen1.h = superficieBarraDeVidaRoja->h;

	SDL_FreeSurface(superficieBarraDeVida);
	SDL_FreeSurface(superficieBarraDeVidaRoja);

	barraDeVidaImagen2 = barraDeVidaImagen1;
	barraRojaDeVidaImagen2 = barraRojaDeVidaImagen1;

	anchoBarraDeVida1 = anchoBarraDeVida;
	anchoBarraDeVida2 = anchoBarraDeVida;

	anchoImagenBarraDeVida = barraDeVidaImagen1.w;

	anchoAnteriorBarra1 = anchoBarraDeVida;
	anchoAnteriorBarra2 = anchoBarraDeVida;

	anchoAnteriorBarraImagen1 = anchoImagenBarraDeVida;
	anchoAnteriorBarraImagen2 = anchoImagenBarraDeVida;

	posBarraDeVida1 = posXBarraDeVida1;
	//Carga de barras de vida
	barraDeVida1 = { posXBarraDeVida1, posYBarraDeVida, anchoBarraDeVida, altoBarraDeVida };
	barraDeVida2 = { posXBarraDeVida2, posYBarraDeVida, anchoBarraDeVida, altoBarraDeVida };

	barraRojaDeVida1 = { posXBarraDeVida1, posYBarraDeVida, anchoBarraDeVida, altoBarraDeVida };
	barraRojaDeVida2 = { posXBarraDeVida2, posYBarraDeVida, anchoBarraDeVida, altoBarraDeVida };

	AlfaInicial = 200;
	AlfaAnterior = 1;
	estadoAnteriorPj1.movimiento = PARADO;
	estadoAnteriorPj2.movimiento = PARADO;
	refMundo = unMundo;

	//Carga efectos de fight (luego reloj)
	SDL_Surface* fight = cargarSuperficieOptimizada("ima/bkg/fight Hd.png");
	this->texturaFight = SDL_CreateTextureFromSurface(renderer, fight);
	SDL_FreeSurface(fight);

	//Carga  textura de round
	SDL_Surface* round = cargarSuperficieOptimizada("ima/bkg/round1.png");
	SDL_SetColorKey(round, SDL_TRUE, SDL_MapRGB(round->format, 255, 255, 255));
	this->texturaRound = SDL_CreateTextureFromSurface(renderer, round);
	SDL_FreeSurface(round);

	//Carga textura para efecto toasty
	SDL_Surface* toasty = cargarSuperficieOptimizada("ima/bkg/toasty.gif");
	SDL_SetColorKey(toasty, SDL_TRUE, SDL_MapRGB(toasty->format, 255, 255, 255));
	this->texturaToasty1 = SDL_CreateTextureFromSurface(renderer, toasty);
	SDL_FreeSurface(toasty);

	//Carga textura para efecto toasty2
	SDL_Surface* toasty2 = cargarSuperficieOptimizada("ima/bkg/toasty2.gif");
	SDL_SetColorKey(toasty2, SDL_TRUE, SDL_MapRGB(toasty2->format, 255, 255, 255));
	this->texturaToasty2 = SDL_CreateTextureFromSurface(renderer, toasty2);
	SDL_FreeSurface(toasty2);

	//Tiempo de permanecia en pantalla de efectos
	this->efectosTimer.start();
	//Menu timer
	this->menuTimer.start();
	//Variables booleanas
	this->enterMenu = 0;
	this->enterSeleccionPersonaje = 0;
	this->y = 30;// y del modo
	this->x = 150;
	this->yPersonaje = 20;

	this->xPersonaje2 = 525;
	this->yPersonaje2 = 20;
	
	this->roundYaReproducido = false;
	this->fightYaReproducido = false;
	this->oneYaReproducido = false;
	this->seleccionYaReproducida = false;

	//Seteo de personajes
	this->jugador1 = Parser::getInstancia().getPelea()->getPersonaje1(); //Scorpion
	this->jugador2 = Parser::getInstancia().getPelea()->getPersonaje2(); //Liu kang

}


void Vista::actualizar(){

	// referencias más utilizadas al actualizar la vista
	std::vector<Personaje*> personajesVista = std::vector<Personaje*>();
	if (!personajesVista.empty()) personajesVista.clear();
	personajesVista.push_back(Parser::getInstancia().getPelea()->getPersonaje1());
	personajesVista.push_back(Parser::getInstancia().getPelea()->getPersonaje2());
	Ventana ventanaVista = Parser::getInstancia().getVentana();

	//Parametros de la ventana

	float anchoVentana = ventanaVista.getAncho();
	int altoVentanaPx = ventanaVista.getAltoPx();

	Personaje* personajeUno = personajesVista[0];
	Personaje* personajeDos = personajesVista[1];

	//Parametros del personaje	
	xPjUno = personajeUno->getPosicionUn().first;
	float anchoPjUno = personajesVista[0]->getAncho();
	xPjDos = personajeDos->getPosicionUn().first;
	float anchoPjDos = personajesVista[1]->getAncho();

	float anchoEscenario = Parser::getInstancia().getEscenario().getAncho();
//-------------------------------------------------------------------------FUERA DE LUGAR
	//Carga  imagenes de los personajes en barra de vida
	SDL_Surface* liuKangBarra = cargarSuperficieOptimizada("ima/bkg/liukang.png");
	//SDL_SetColorKey(round, SDL_TRUE, SDL_MapRGB(round->format, 255, 255, 255));
	this->texturaLiuKang = SDL_CreateTextureFromSurface(renderer, liuKangBarra);
	SDL_FreeSurface(liuKangBarra);

	//SDL_Surface* scorpionBarra = cargarSuperficieOptimizada("ima/bkg/scorpion.png");
	SDL_Surface* scorpionBarra = cargarSuperficieOptimizada("ima/bkg/scorpion.png");
	//SDL_SetColorKey(round, SDL_TRUE, SDL_MapRGB(round->format, 255, 255, 255));
	this->texturaScorpion = SDL_CreateTextureFromSurface(renderer, scorpionBarra);
	SDL_FreeSurface(scorpionBarra);
//----------------------------------------------------------------------------------

	//Se limpia la pantalla
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	Sensor* sensorPj1 = refMundo->getCuerpo(0)->getSensores()->at(0);
	Sensor* sensorPj2 = refMundo->getCuerpo(1)->getSensores()->at(0);

	// condicion de borde Personaje Uno
	bool PjUnoEstaEnBordeIzq = false;
	bool PjUnoEstaEnBordeDer = false;
	if (xPjUno + manejadorULog.darLongUnidades(sensorPj1->getPosicion().first + (sensorPj1->getAncho())) >= anchoVentana - camaraXLog)
		PjUnoEstaEnBordeDer = true;
	if (xPjUno + manejadorULog.darLongUnidades(sensorPj1->getPosicion().first) < -camaraXLog)
		PjUnoEstaEnBordeIzq = true;
	bool PjUnoEstaEnBorde = PjUnoEstaEnBordeIzq || PjUnoEstaEnBordeDer;

	// condicion de borde Personaje Dos
	bool PjDosEstaEnBordeIzq = false;
	bool PjDosEstaEnBordeDer = false;
	if (xPjDos + manejadorULog.darLongUnidades(sensorPj2->getPosicion().first + (sensorPj2->getAncho())) >= anchoVentana - camaraXLog)
		PjDosEstaEnBordeDer = true;
	if (xPjDos + manejadorULog.darLongUnidades(sensorPj2->getPosicion().first) < -camaraXLog)
		PjDosEstaEnBordeIzq = true;
	bool PjDosEstaEnBorde = PjDosEstaEnBordeIzq || PjDosEstaEnBordeDer;

	MOV_TIPO mov1 = refMundo->getCuerpo(0)->getControlador()->getMovimientos().back();
	MOV_TIPO mov2 = refMundo->getCuerpo(1)->getControlador()->getMovimientos().back();
	ESTADO estadoPj1 = refMundo->getCuerpo(0)->getEstado();
	ESTADO estadoPj2 = refMundo->getCuerpo(1)->getEstado();



	if ((PjUnoEstaEnBordeIzq && PjDosEstaEnBordeDer) || (PjDosEstaEnBordeIzq && PjUnoEstaEnBordeDer)) {
		refMundo->FrenarCuerpos();
	}

	if (PjUnoEstaEnBordeIzq && (mov1 == DER))
		refMundo->LiberarCuerpos();

	if (PjUnoEstaEnBordeDer && (mov1 == IZQ))
		refMundo->LiberarCuerpos();

	if (PjDosEstaEnBordeIzq && (mov2 == DER))
		refMundo->LiberarCuerpos();

	if (PjDosEstaEnBordeDer && (mov2 == IZQ))
		refMundo->LiberarCuerpos();

	if (PjUnoEstaEnBordeIzq && !(refMundo->getCuerpo(0)->EstaFrenado()))
		if (personajesVista[0]->getDeltaX() > 0)
			camaraXLog += personajesVista[0]->getDeltaX();
	if (PjDosEstaEnBordeIzq && !(refMundo->getCuerpo(1)->EstaFrenado()))
		if (personajesVista[1]->getDeltaX() > 0)
			camaraXLog += personajesVista[1]->getDeltaX();
	if (PjUnoEstaEnBordeDer && !(refMundo->getCuerpo(0)->EstaFrenado()))
		if (personajesVista[0]->getDeltaX() < 0)
			camaraXLog += personajesVista[0]->getDeltaX();
	if (PjDosEstaEnBordeDer && !(refMundo->getCuerpo(1)->EstaFrenado()))
		if (personajesVista[1]->getDeltaX() < 0)
			camaraXLog += personajesVista[1]->getDeltaX();



	// nacho: la camara queda contenida dentro del escenario
	if (camaraXLog > 0) camaraXLog = 0;
	if (camaraXLog < -anchoEscenario + anchoVentana) camaraXLog = -anchoEscenario + anchoVentana;
	//camaraXLog += personajesVista[0]->getDeltaX();

	//Vibracion de la camara
	if (vibracion){
		bool golpeado = false;
		/*for (int i = 0; i < personajesVista.size(); i++){
			if ((personajesVista.at(i)->getEstado().accion == PATADA_ALTA) && ){
			golpeado = true;
			break;
			}
			}*/
		//Este es el codigo que deberia ir en realidad pero todavia no hay gancho
		if (personajesVista.at(0)->getEstado().golpeado == GOLPEADO && personajesVista.at(0)->getEstado().accion != GUARDIA){
			if (personajesVista.at(1)->getEstado().accion == GANCHO){
				golpeado = true;
			}
		}
		else{
			if (personajesVista.at(1)->getEstado().golpeado == GOLPEADO && personajesVista.at(1)->getEstado().accion != GUARDIA){
				if (personajesVista.at(0)->getEstado().accion == GANCHO){
					golpeado = true;
				}
			}
		}

		if ((personajesVista.at(0)->getEstado().golpeado == GOLPEADO) || (personajesVista.at(1)->getEstado().golpeado == GOLPEADO)){
			AlfaInicial = AlfaInicial - AlfaAnterior;
			if (AlfaInicial < 128){
				AlfaInicial = 200;
			}
			alfa(AlfaInicial);
		}
		else
			alfa(128);
		/*		if (golpeado) vibraciones++;
				else vibraciones = 0;*/

		if (golpeado){
			retraso--;
			if (retraso == 0){
				retraso = VIBRACIONES;
				if (!estaVibrando){
					camaraXLog = camaraXLog + 5;
					estaVibrando = true;
				}
				else{
					estaVibrando = false;
					camaraXLog = camaraXLog - 5;
				}
			}
		}
	}


	if (!PjUnoEstaEnBorde && !PjDosEstaEnBorde)
		refMundo->LiberarCuerpos();

	//Dibujar menu 

	int  anchoVentanaPx = ventanaVista.getAnchoPx();
	if ((this->menuTimer.getTicks() >= 50) && (this->menuTimer.getTicks() <= 8100) && (this->enterMenu == 0))
	{

		this->dibujarMenu(anchoVentana, anchoVentanaPx, altoVentanaPx, anchoEscenario);
		SDL_RenderPresent(renderer);

		//Se limpia la pantalla

		//SDL_DestroyTexture(this->texturaMenu);
	}
	else
	{
		if ((this->menuTimer.getTicks() > 8100) && (this->menuTimer.getTicks() <= 11100))
			enterMenu = 1;
	}
	
	if ((this->enterSeleccionPersonaje == 0) &&(this->enterMenu == 1))
	{
		
		if (this->seleccionYaReproducida == false)  //Sonido de gong canal 3
		{
			Mix_Chunk *sonidoF8 = Mix_LoadWAV("./son/entradaSeleccion.wav");
			Mix_PlayChannel(3, sonidoF8, 0);
			this->seleccionYaReproducida = true;
		}
		
			this->dibujarSeleccionPersonaje(anchoVentana, anchoVentanaPx, altoVentanaPx, anchoEscenario);
			SDL_RenderPresent(renderer);
		}
		else
		{
			if (this->enterSeleccionPersonaje == 1)
			{   //Se esta reproduciendo el canal cero
				if (Mix_Playing(0) == 1)
				{
					Mix_FadeOutChannel(0,50);//Parar la musica Sobre canal 0 , con efecto fade 50mseg.
				}
				//Si la musica NO se esta reproduciendo
				if (Mix_PlayingMusic() == 0)
				{
					Mix_Music *musicaCombate = Mix_LoadMUS("./son/mortal64.mid");
					Mix_PlayMusic(musicaCombate, 0);
				}

				SDL_RenderClear(renderer);
				this->menuTimer.stop();
				// Dibuja las capas y el personaje
				Dibujar(personajesVista);

				//Dibuja las barras de vida
				DibujarBarrasDeVida(personajesVista);

				//Se actualiza la pantalla
				SDL_RenderPresent(renderer);
			}
			
		}
	

}

	

SDL_Surface* Vista::cargarSuperficieOptimizada(std::string dirImagen)
{	
	SDL_Surface* superficieOptimizada = NULL;

	//cargo original
	SDL_Surface* superficieOriginal = IMG_Load(dirImagen.c_str());
	if (superficieOriginal == NULL)
		Log::getInstancia().logearMensajeEnModo("No se pudo cargar imagen" + dirImagen, Log::MODO_ERROR);	
	else 
	{	//Optimiza superfice a pantalla
		superficieOptimizada = SDL_ConvertSurface(superficieOriginal, superficieOriginal->format, NULL);
		if (superficieOptimizada == NULL)
			Log::getInstancia().logearMensajeEnModo("No se pudo optimizar imagen" + dirImagen + SDL_GetError(), Log::MODO_ERROR);

		//libero la original
		SDL_FreeSurface(superficieOriginal);
	}

	return superficieOptimizada;
}

void Vista::OrdenarCapas()
{	
	std::vector<Capa*> capasOrdenadas;
	int i = 0;
	while ( capasVista.size() > 0) {
		int minimo = 0;
		for (size_t j = 1; j < capasVista.size(); j++){
			if (capasVista[j]->getZIndex() < capasVista[minimo]->getZIndex()) {
				minimo = j;				
			}
		}		
		capasOrdenadas.push_back(capasVista[minimo]);
		capasVista.erase(capasVista.begin() + minimo);		
	}
	
	capasVista.clear();
	capasVista = capasOrdenadas;
}
void Vista::dibujarMenu(float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario)
{
	SDL_Rect camaraMenu = { 0, 0, anchoVentanaPx, altoVentanaPx };
	SDL_RenderCopy(renderer, this->texturaMenu, NULL, &camaraMenu);

	//Dibujo el boton de la opcion 2 JUGADORES
	SDL_Rect playMode = { 150, 50, 500, 200 };
	SDL_RenderCopy(renderer, this->texturaPlayMode, NULL, &playMode);
	//Creo la superficie para escribir 
	SDL_Color bgcolor, fgcolor;
	SDL_Rect dosJugadores = { 200, 70, 400, 150 };

	//Tipo de letra
	TTF_SetFontStyle(this->fuente, TTF_STYLE_BOLD);
	// inicializa colores para la letra
	fgcolor.r = 200;
	fgcolor.g = 200;
	fgcolor.b = 10;
	// inicializa colores para el fondo(rojo)
	bgcolor.r = 255;
	bgcolor.g = 0;
	bgcolor.b = 0;
	//std::cout << "El tamaño de la fuente es " << TTF_FontHeight(this->fuente) << std::endl;
	//std::cout << "El ascendente de la fuente es " << TTF_FontAscent(this->fuente) << std::endl;
	//std::cout << "El descendente de la fuente es " << TTF_FontDescent(this->fuente) << std::endl;
	//std::cout << "La separación entre líneas es " << TTF_FontLineSkip(this->fuente) << std::endl;

	SDL_Surface * ttext = TTF_RenderText_Shaded(this->fuente, "2 jugadores", fgcolor, bgcolor);
	if (ttext == NULL)
	{
		std::cout << "Error en la carga de las letras";
	}

	// Usamos color rojo para la transparencia del fondo
	SDL_SetColorKey(ttext, SDL_TRUE, SDL_MapRGB(ttext->format, 255, 0, 0));

	//Se escriben las letras
	SDL_Texture * texturaP = SDL_CreateTextureFromSurface(renderer, ttext);
	SDL_FreeSurface(ttext);
	SDL_RenderCopy(renderer, texturaP, NULL, &dosJugadores);

	//Dibujo el boton de la opcion 1 JUGADOR
	SDL_Rect cpuMode = { 150, 250, 500, 200 };//y=100+200
	SDL_RenderCopy(renderer, this->texturaUnjugador, NULL, &cpuMode);
	SDL_Surface * ttext2 = TTF_RenderText_Shaded(this->fuente, "1 jugador", fgcolor, bgcolor);
	SDL_SetColorKey(ttext2, SDL_TRUE, SDL_MapRGB(ttext2->format, 255, 0, 0));

	SDL_Texture * texturaSingle = SDL_CreateTextureFromSurface(renderer, ttext2);
	SDL_FreeSurface(ttext2);
	//Camara de la letra 
	SDL_Rect unJugador = { 200, 270, 400, 150 }; //Relacion camara externa_interna =(+50,+20,-100,-50)
	SDL_RenderCopy(renderer, texturaSingle, NULL, &unJugador);

	//Dibujo el boton de la opcion training
	SDL_Rect TrainigMode = { 150, 450, 500, 200 };//y=100+200
	SDL_RenderCopy(renderer, this->texturaTrainig, NULL, &TrainigMode);

	SDL_Surface * ttext3 = TTF_RenderText_Shaded(this->fuente, "entrenamiento", fgcolor, bgcolor);
	SDL_SetColorKey(ttext3, SDL_TRUE, SDL_MapRGB(ttext3->format, 255, 0, 0));

	SDL_Texture * texturaEntrenamiento = SDL_CreateTextureFromSurface(renderer, ttext3);
	SDL_FreeSurface(ttext3);

	//Camara de la letra 
	SDL_Rect entrenamiento = { 200, 470, 400, 150 }; //Relacion camara externa_interna =(+50,+20,-100,-50)
	SDL_RenderCopy(renderer, texturaEntrenamiento, NULL, &entrenamiento);

	//Dibuja recuadro coordenadas:2 jugadores :150, 50, 500, 200 1 jugador: 150, 250, 500, 200 training:150, 450, 500, 200
	int x, w, v;
	x = 130;
	//y=30;//50
	w = 540;
	v = 240;

	SDL_Rect recuadroSeleccion = { x, this->y, w, v };
	SDL_RenderCopy(renderer, this->texturaRecuadro, NULL, &recuadroSeleccion);

	SDL_Event evento;
	Mix_Chunk *sonidoF7 = Mix_LoadWAV("./son/desplazamientoMenu.wav");
	
	// Esperamos a que ocurra un evento
	SDL_WaitEvent(&evento);
	//Si es tecla
	if (evento.type == SDL_KEYDOWN)
	{
		switch (evento.key.keysym.sym) {

		case SDLK_DOWN:
			if (this->y == 450)   //Si esta en el Ultimo boton vuelve al primero
			{
				this->y = 30;
				Mix_PlayChannel(1, sonidoF7, 0);
			}
			else
			{
				this->y = this->y + 200; //Baja un boton
				Mix_PlayChannel(1, sonidoF7, 0);
			}
			std::cout << "abajo";
			break;

		case SDLK_UP:
			if (this->y == 30)   //Si esta en el primer boton baja al ultimo
			{
				this->y = 450;
				Mix_PlayChannel(1, sonidoF7, 0);
			}
			else
			{
				this->y = this->y - 200; //Sube un boton
				Mix_PlayChannel(1, sonidoF7, 0);
			}

			std::cout << "arriba";
			break;

		case  SDLK_RETURN:

			//En base a la altura de la pantalla nos setea el modo de juego elegido
			//Se presiono enter
			this->enterMenu = 1;
			//Modo de juego elegido
			this->controladorDeModoDeJuego();
			break;
		default:
			;

		}
	}

	//Si es mouse
	else
	{    //movimiento de raton(coordenadas)
		if (evento.type == SDL_MOUSEMOTION)
		{
			std::cout << "X: " << evento.motion.x;
			std::cout << " - Y: " << evento.motion.y << std::endl;
		}
		else
		{
			if (evento.type == SDL_MOUSEBUTTONDOWN) {

				if (evento.button.type == SDL_MOUSEBUTTONDOWN) {
					std::cout << "X: " << evento.button.x   //Posicion x del boton
						<< " - Y: " << evento.button.y
						<< " Botón pulsado " << (int)evento.button.button << std::endl;//Posicion y del boton	

					if ((int)evento.button.button == 1)//Boton izquierdo
					{
						if ((evento.button.x >= 130) && (evento.button.x <= 650))  //Coordenadas del ancho de los botones
						{
							if ((evento.button.y >= 30) && (evento.button.y <= 250))//Primer boton
							{

								this->y = 30;
								this->enterMenu = 1;
								this->controladorDeModoDeJuego();
								//Mix_HaltMusic();
								Mix_PlayChannel(1, sonidoF7, 0);
							}
							else
							{
								if ((evento.button.y >= 250) && (evento.button.y <= 450))//segundo boton
								{
									this->y = 230;
									this->enterMenu = 1;
									this->controladorDeModoDeJuego();
									//Mix_HaltMusic();
									Mix_PlayChannel(1, sonidoF7, 0);
								}
								else
								{
									if ((evento.button.y >= 450) && (evento.button.y <= 650))//tercer boton
									{
										this->y = 430;
										this->enterMenu = 1;
										this->controladorDeModoDeJuego();
										//Mix_HaltMusic();
										Mix_PlayChannel(1, sonidoF7, 0);

									}
								}
							}

						}

					}

				}
			}
		}
	}
	if (this->enterMenu == 1){
	Mix_Chunk *sonido4 = Mix_LoadWAV("./son/Hahahaaa.wav");
	Mix_PlayChannel(1, sonido4, 0);
	//paramos la musica de fondo
	//Mix_HaltMusic();
	
	}
		
	//Nuevo recuadro	
	SDL_Rect recuadroSeleccion2 = { 130, this->y, 540, 240 };
	SDL_RenderCopy(renderer, this->texturaRecuadro, NULL, &recuadroSeleccion2);
	
}
void Vista::dibujarSeleccionPersonaje(float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario)
{  //Dibujo imagen de fondo
	SDL_Rect camaraSeleccion = { 0, 0, anchoVentanaPx, altoVentanaPx };
	SDL_RenderCopy(renderer, this->texturaSeleccionPersonajes, NULL, &camaraSeleccion);

	//Dibujo todos los personajes 
	SDL_Rect grillaPersonajes = { 150, 20, 500, 550 };
	SDL_RenderCopy(renderer, this->texturaGrillaPersonajes, NULL, &grillaPersonajes);

	//Dibuja recuadro player1 y=20 x=150 inicial
	// x=+125,y=185
	int w, v;
	w = 125;
	v = 185;

	SDL_Rect recuadroSeleccionPersonaje = { this->x, this->yPersonaje, w, v };
	SDL_RenderCopy(renderer, this->texturaRecuadroPersonajes, NULL, &recuadroSeleccionPersonaje);

	/*********************************************************************/
	/*      Modo 2 jugadores                                              */
	/*********************************************************************/
	if (this->modoActual == TWOPLAYER)
	{

		//Dibuja recuadro player2 y=20 x=525 inicial
		// x=+125,y=185
		int t, z;
		t = 125;
		z = 185;

		SDL_Rect recuadroSeleccionPersonajeDos = { this->xPersonaje2, this->yPersonaje2, t, z };
		SDL_RenderCopy(renderer, this->texturaRecuadroPersonajes, NULL, &recuadroSeleccionPersonajeDos);
	}

	//Captura de eventos 
	//primera fila 20 a 205 segunda fila 205 a 390 3era fila 575
	//primera columna 150 a 275 segunda columna 275 a 400 3ra fila 400 a 525, cuarta a 650
	SDL_Event evento;
	// Esperamos a que ocurra un evento
	SDL_WaitEvent(&evento);
	//Si es tecla
	if (evento.type == SDL_KEYDOWN)
	{
		switch (evento.key.keysym.sym) {

		case SDLK_DOWN:
			if (this->yPersonaje >= 390)   //Si esta en la ultima fila vuelve a la primer fila
			{
				this->yPersonaje = 20;
			}
			else
			{
				this->yPersonaje = this->yPersonaje + 185; //Baja una fila
			}
			std::cout << "abajo";
			break;

		case SDLK_UP:
			if (this->yPersonaje <= 20)   //Si esta en la primer fila baja a la ultima fila
			{
				this->yPersonaje = 390;
			}
			else
			{
				this->yPersonaje = this->yPersonaje - 185; //Sube una fila
			}

			std::cout << "arriba";
			break;
		case SDLK_RIGHT:
			if (this->x == 525)   //Si esta en la ultima columna pasa a la primera
			{
				this->x = 150;
			}
			else
			{
				this->x = this->x + 125;//Corre una columna
			}
			std::cout << "derecha";
			break;

		case SDLK_LEFT:

			if (this->x == 150)   //Si esta en la primer columna pasa a la ultima
			{
				this->x = 525;
			}
			else
			{
				this->x = this->x - 125;//Corre una columna
			}

			std::cout << "izquierda";
			break;
		case SDLK_ESCAPE:
			//Se presiono escape,vuelvo al pantalla de modo de juegos
			this->enterMenu = 0;
		case  SDLK_RETURN:

			//Se presiono enter
			this->enterSeleccionPersonaje = 1;
			//Personaje elejido
			//this->controladorDePersonajes();

			break;
		default:
			;

		}
	}

	//Si es mouse
	else
	{    //movimiento de raton(coordenadas)
		if (evento.type == SDL_MOUSEMOTION)
		{
			std::cout << "X: " << evento.motion.x;
			std::cout << " - Y: " << evento.motion.y << std::endl;
		}
		else
		{
			if (evento.type == SDL_MOUSEBUTTONDOWN) {

				if (evento.button.type == SDL_MOUSEBUTTONDOWN) {
					std::cout << "X: " << evento.button.x   //Posicion x del boton
						<< " - Y: " << evento.button.y
						<< " Botón pulsado " << (int)evento.button.button << std::endl;//Posicion y del boton	

					if ((int)evento.button.button == 1)//Boton izquierdo pulsado
					{
						if ((evento.button.x >= 150) && (evento.button.x <= 700))  //Coordenadas del ancho de grilla
						{
							if ((evento.button.y >= 20) && (evento.button.y <= 205))//Primera fila (liu kang)
							{
								this->yPersonaje = 20;
								enterSeleccionPersonaje = 1;
								//this->controladorDePersonajes();
								Mix_HaltMusic();
							}
							else
							{
								if ((evento.button.y >= 205) && (evento.button.y <= 390))//segundo boton
								{
									this->yPersonaje = 205;
									enterSeleccionPersonaje = 1;
									//this->controladorDeModoDeJuego();
									Mix_HaltMusic();
								}
								else
								{
									if ((evento.button.y >= 390) && (evento.button.y <= 575))//tercer boton
									{
										this->y = 390;
										enterSeleccionPersonaje = 1;
										//this->controladorDeModoDeJuego();
										Mix_HaltMusic();

									}
								}
							}

						}

					}

				}
			}
		}
	}

	//Actualiza el nuevo recuadro de player 1
	SDL_Rect recuadroSeleccionPlayer1 = { this->x, this->yPersonaje, 125, 185 };
	SDL_RenderCopy(renderer, this->texturaRecuadroPersonajes, NULL, &recuadroSeleccionPlayer1);
	if (enterSeleccionPersonaje == 1){
		Mix_Chunk *sonidoE = Mix_LoadWAV("./son/Excellent2.wav");
		Mix_PlayChannel(1, sonidoE, 0);
		
		SDL_RenderCopy(renderer, this->texturaSeleccionPersonajes2, NULL, &camaraSeleccion);
		SDL_RenderPresent(renderer);
		Mix_Chunk *sonidoFE = Mix_LoadWAV("./son/Burn.wav");
		Mix_PlayChannel(3, sonidoFE, 0); 
		SDL_Delay(1000);
		//paramos la musica de fondo
		Mix_HaltMusic();
	}
	


	}

	


void Vista::Dibujar(std::vector<Personaje*> personajesVista)
{
	Ventana ventanaVista = Parser::getInstancia().getVentana();

	float anchoVentana = ventanaVista.getAncho();
	int anchoVentanaPx = ventanaVista.getAnchoPx();
	int altoVentanaPx = ventanaVista.getAltoPx();
	float anchoEscenario = Parser::getInstancia().getEscenario().getAncho();

	DibujarCapasAnteriores(personajesVista, anchoVentana, anchoVentanaPx, altoVentanaPx, anchoEscenario);

	DibujarPersonajes(personajesVista);

	DibujarCapasPosteriores(personajesVista, anchoVentana, anchoVentanaPx, altoVentanaPx, anchoEscenario);

	//Dibuja imagenes de los personajes
	this->dibujarImagenesBarraVida(anchoVentanaPx, altoVentanaPx);
   
	this->DibujarEfectos(anchoVentana, anchoVentanaPx, altoVentanaPx,anchoEscenario);
	
}

void Vista::alfa(Uint8 alfa){
	AlfaVida = alfa;
}

void Vista::DibujarBarrasDeVida(std::vector<Personaje*> personajesVista)
{
	SDL_SetRenderTarget(renderer, texturaBarraDeVida);
	SDL_SetRenderDrawColor(renderer, 225, 224, 227, AlfaVida);
	SDL_SetTextureAlphaMod(texturaBarraDeVida, AlfaVida);

	int vidaPj1 = personajesVista.at(0)->getVida();
	int vidaPj2 = personajesVista.at(1)->getVida();

	int nuevoAnchoBarraDeVida1 = (vidaPj1 * anchoBarraDeVida1) / 100;
	int nuevoAnchoBarraDeVida2 = (vidaPj2 * anchoBarraDeVida2) / 100;

	int nuevoanchoImagenBarraDeVida1 = (vidaPj1 *anchoImagenBarraDeVida) / 100;
	int nuevoanchoImagenBarraDeVida2 = (vidaPj2 *anchoImagenBarraDeVida) / 100;

	barraDeVida1.w = nuevoAnchoBarraDeVida1;
	barraDeVida2.w = nuevoAnchoBarraDeVida2;

	barraDeVidaImagen1.w = nuevoanchoImagenBarraDeVida1;
	barraDeVidaImagen2.w = nuevoanchoImagenBarraDeVida2;
	barraDeVida1.x = posBarraDeVida1 + anchoBarraDeVida1 - nuevoAnchoBarraDeVida1;

	SDL_RenderCopyEx(renderer, texturaBarraDeVida, &barraDeVidaImagen1, &barraDeVida1, 0, NULL, SDL_FLIP_HORIZONTAL);
	SDL_RenderCopy(renderer, texturaBarraDeVida, &barraDeVidaImagen2, &barraDeVida2);
	SDL_SetRenderTarget(renderer, NULL);

	//Parte barra roja
	SDL_SetRenderTarget(renderer, texturaBarraDeVidaRoja);
	SDL_SetRenderDrawColor(renderer, 215, 12, 25, AlfaVida);
	SDL_SetTextureAlphaMod(texturaBarraDeVidaRoja, AlfaVida);

	barraRojaDeVida2.x = barraDeVida2.x + barraDeVida2.w;
	barraRojaDeVida1.w = anchoAnteriorBarra1 - nuevoAnchoBarraDeVida1;
	barraRojaDeVida2.w = anchoAnteriorBarra2 - nuevoAnchoBarraDeVida2;
	barraRojaDeVida1.x = barraDeVida1.x - barraRojaDeVida1.w;

	barraRojaDeVidaImagen1.x = barraDeVidaImagen1.x + barraDeVidaImagen1.w;
	barraRojaDeVidaImagen2.x = barraDeVidaImagen2.x + barraDeVidaImagen2.w;
	barraRojaDeVidaImagen1.w = anchoAnteriorBarraImagen1 - nuevoanchoImagenBarraDeVida1;
	barraRojaDeVidaImagen2.w = anchoAnteriorBarraImagen2 - nuevoanchoImagenBarraDeVida2;

	//Se setean atributos anteriores para el próximo cuadro.
	if (!(personajesVista.at(0)->getEstado().golpeado == GOLPEADO) && !(personajesVista.at(1)->getEstado().golpeado == GOLPEADO)){
	anchoAnteriorBarra1 = nuevoAnchoBarraDeVida1;
	anchoAnteriorBarra2 = nuevoAnchoBarraDeVida2;

	anchoAnteriorBarraImagen1 = nuevoanchoImagenBarraDeVida1;
	anchoAnteriorBarraImagen2 = nuevoanchoImagenBarraDeVida2;
	}

	SDL_RenderCopyEx(renderer, texturaBarraDeVidaRoja, &barraRojaDeVidaImagen1, &barraRojaDeVida1, 0, NULL, SDL_FLIP_HORIZONTAL);
	SDL_RenderCopy(renderer, texturaBarraDeVidaRoja, &barraRojaDeVidaImagen2, &barraRojaDeVida2);

	SDL_SetRenderTarget(renderer, NULL);
}


void Vista::DibujarCapasAnteriores(std::vector<Personaje*> personajesVista, float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario)
{
	SDL_Rect camara;
	camara = { 0, 0, anchoVentanaPx, altoVentanaPx };
	//Se cargan las capas anteriores al personaje
	for (size_t i = 0; i < capasVista.size(); i++)
	{
		if (capasVista.at(i)->getZIndex() <= personajesVista[0]->getZIndex()) {
			float anchoCapa = capasVista.at(i)->getAncho();
			camara.w = manejadorULog.darLongPixels(anchoCapa);
			// donde toma la camara a la capa parametrizado con el ancho del escenario	
			camara.x = manejadorULog.darLongPixels((camaraXLog)*(anchoCapa - anchoVentana) / (anchoEscenario - anchoVentana));

			SDL_RenderCopy(renderer, capasVista.at(i)->getTexturaSDL(), NULL, &camara);
		}
	}
}
void Vista::DibujarEfectos(float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario)
{
	SDL_Rect camaraFight;
	camaraFight = { (anchoVentanaPx / 3), (altoVentanaPx / 8), (anchoVentanaPx / 2), (altoVentanaPx) / 3 };

	camaraFight.w = manejadorULog.darLongPixels(100);

	// donde toma la camara a la capa parametrizado con el ancho del escenario
	camaraFight.x = manejadorULog.darLongPixels((camaraXLog)*(anchoVentana - 310) / (anchoEscenario - anchoVentana));

	//Si el cronometro de efectos es > 1 segundo y menor a 2 muestra Round.
	//Si es mayor a 2 segundos muestra fight
	//Si es mayor a 4 segundos detiene el cronometro y limpia pantalla
	if ((this->efectosTimer.getTicks() >= 10100) && (this->efectosTimer.getTicks() <=11100 ))
	{
		if (!this->roundYaReproducido)
		{
			Mix_Chunk *sonido = Mix_LoadWAV("./son/Round.wav");
			Mix_PlayChannel(2, sonido, 0);
			this->roundYaReproducido = true;
			
		}
		SDL_RenderCopy(renderer, this->texturaRound, NULL, &camaraFight);
	}
	else
	{
		if ((this->efectosTimer.getTicks() > 11000) && (this->efectosTimer.getTicks() <= 13000))
		{
			if (!this->fightYaReproducido){
			Mix_Chunk *sonido2 = Mix_LoadWAV("./son/Fight2.wav");
			Mix_PlayChannel(2, sonido2, 0);
			this->fightYaReproducido = true;
		    }
			SDL_DestroyTexture(this->texturaRound);
			SDL_RenderCopy(renderer, this->texturaFight, NULL, &camaraFight);

		}
		else
		{
			if (this->efectosTimer.getTicks() > 13000)
			{
				SDL_DestroyTexture(this->texturaFight);
				this->efectosTimer.stop();
			}
		}

	}
	
}



void Vista::dibujarImagenesBarraVida(int anchoVentanaPx, int altoVentanaPx)
{
	SDL_Rect camaraPersonaje1;
	camaraPersonaje1 = { 2, 15, anchoVentanaPx / 16, altoVentanaPx / 16 };//2,4,50,37.5   48x33,5
	SDL_RenderCopy(renderer, this->texturaScorpion, NULL, &camaraPersonaje1);

	SDL_Rect camaraPersonaje2;
	camaraPersonaje2 = { 750, 15, 50, 40 };
	//SDL_RenderCopy(renderer, this->texturaLiuKang, NULL, &camaraPersonaje2);
	SDL_RenderCopyEx(renderer, this->texturaLiuKang, NULL, &camaraPersonaje2, 0, NULL, SDL_FLIP_HORIZONTAL);
}

void Vista::DibujarCapasPosteriores(std::vector<Personaje*> personajesVista, float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario)
{
	SDL_Rect camara;
	camara = { 0, 0, anchoVentanaPx, altoVentanaPx };
	//Se cargan las capas posteriores al personaje
	for (size_t i = 0; i < capasVista.size(); i++)
	{
		if (capasVista.at(i)->getZIndex() > personajesVista[0]->getZIndex()) {
			float anchoCapa = capasVista.at(i)->getAncho();
			camara.w = manejadorULog.darLongPixels(anchoCapa);
			// donde toma la camara a la capa parametrizado con el ancho del escenario
			camara.x = manejadorULog.darLongPixels((camaraXLog)*(anchoCapa - anchoVentana) / (anchoEscenario - anchoVentana));
			SDL_RenderCopy(renderer, capasVista.at(i)->getTexturaSDL(), NULL, &camara);
		}
	}
}

void Vista::DibujarPersonajes(std::vector<Personaje*> personajesVista)
{
	Sensor* sensoresCuerpo1 = refMundo->getCuerpo(0)->getSensores()->at(0);
	Sensor* sensoresCuerpo2 = refMundo->getCuerpo(1)->getSensores()->at(0);

	float posMediaPj1 = personajesVista.at(0)->getPosicionUn().first + personajesVista.at(0)->getAncho()/2;
	float posMediaPj2 = personajesVista.at(1)->getPosicionUn().first + personajesVista.at(1)->getAncho() / 2;

	//Parámetro para ver si el jugador esta a izquierda o derecha.
	bool invertido = (posMediaPj1 > posMediaPj2);

	//Parametros del personaje 1
	int anchoPjUnoPx = manejadorULog.darLongPixels(personajesVista[0]->getAncho());
	int altoPjUnoPx = manejadorULog.darLongPixels(personajesVista[0]->getAlto(), Parser::getInstancia().getVentana().getAltoPx(), Parser::getInstancia().getEscenario().getAlto());
	int xPjUnoPx = personajesVista[0]->getPosicionPx().first;
	int yPjUnoPx = personajesVista[0]->getPosicionPx().second;
	float anchoPjUno = personajesVista[0]->getAncho();

	//Parametros del personaje 2
	int anchoPjDosPx = manejadorULog.darLongPixels(personajesVista[1]->getAncho());
	int altoPjDosPx = manejadorULog.darLongPixels(personajesVista[1]->getAlto(), Parser::getInstancia().getVentana().getAltoPx(), Parser::getInstancia().getEscenario().getAlto());
	int xPjDosPx = personajesVista[1]->getPosicionPx().first;
	int yPjDosPx = personajesVista[1]->getPosicionPx().second;
	float anchoPjDos = personajesVista[1]->getAncho();

	// Posicion x del personaje dentro de la camara
	float xLogPjUnoEnCamara = xPjUno + camaraXLog;
	SDL_Rect personajeUno;

	// Posicion x del personaje dentro de la camara
	float xLogPjDosEnCamara = xPjDos + camaraXLog ;
	SDL_Rect personajeDos;

	ESTADO estadoAux;
	estadoAux.movimiento = PARADO;
	SDL_Rect* cuadroBase = personajesVista[0]->getSprite()->listaDeCuadros(estadoAux)->at(0);
	float relacionAnchoUno = (float)anchoPjUnoPx / (float)cuadroBase->w;
	float relacionAltoUno = (float)altoPjUnoPx / (float)cuadroBase->h;
	personajeUno.x = manejadorULog.darLongPixels(xLogPjUnoEnCamara);
	personajeUno.y = yPjUnoPx;
	
	// ancho y alto lo calcula cuadro a cuadro
	ESTADO estadoDelPersonajeUno = personajesVista[0]->getEstado();

	float relacionAnchoDos = (float)anchoPjDosPx / (float)cuadroBase->w;
	float relacionAltoDos = (float)altoPjDosPx / (float)cuadroBase->h;
	personajeDos.x = manejadorULog.darLongPixels(xLogPjDosEnCamara);
	personajeDos.y = yPjDosPx;

	ESTADO estadoDelPersonajeDos = personajesVista[1]->getEstado();

	//Se carga la lista de cuadros que corresponde acorde al estado del personaje.
	listaDeCuadrosUno = personajesVista[0]->getSprite()->listaDeCuadros(estadoDelPersonajeUno);
	tiempoSecuenciaSpritesUno = personajesVista[0]->getSprite()->getConstantes(estadoDelPersonajeUno);


	if ((estadoAnteriorPj1.movimiento != estadoDelPersonajeUno.movimiento) || (estadoAnteriorPj1.accion != estadoDelPersonajeUno.accion) || (estadoAnteriorPj1.golpeado != estadoDelPersonajeUno.golpeado)){
		numeroDeCuadroUno = 0;
		estadoAnteriorPj1 = estadoDelPersonajeUno;
	}

	if ((estadoAnteriorPj2.movimiento != estadoDelPersonajeDos.movimiento) || (estadoAnteriorPj2.accion != estadoDelPersonajeDos.accion) || (estadoAnteriorPj2.golpeado != estadoDelPersonajeDos.golpeado)){
		numeroDeCuadroDos = 0;
		estadoAnteriorPj2 = estadoDelPersonajeDos;
	}
	
	if ((numeroDeCuadroUno) > (tiempoSecuenciaSpritesUno*listaDeCuadrosUno->size()))
		numeroDeCuadroUno = 0;

	if (0 >= ((listaDeCuadrosUno->size() - 1) - (numeroDeCuadroUno / tiempoSecuenciaSpritesUno)))
		numeroDeCuadroUno = 0;

	//Renderizar el sprite
	SDL_Rect* cuadroActualUno;
	if (invertido){
		cuadroActualUno = listaDeCuadrosUno->at((listaDeCuadrosUno->size() - 1) - (numeroDeCuadroUno / tiempoSecuenciaSpritesUno));
	}
	else{
		cuadroActualUno = listaDeCuadrosUno->at(numeroDeCuadroUno / (tiempoSecuenciaSpritesUno));
	}

	numeroDeCuadroUno++;

	personajeUno.w = (int)round(relacionAnchoUno*cuadroActualUno->w);
	personajeUno.h = (int)round(relacionAltoUno*cuadroActualUno->h);

	//Se carga la lista de cuadros que corresponde acorde al estado del personaje.
	listaDeCuadrosDos = personajesVista[1]->getSprite()->listaDeCuadros(estadoDelPersonajeDos);
	tiempoSecuenciaSpritesDos = personajesVista[1]->getSprite()->getConstantes(estadoDelPersonajeDos);

	if ((numeroDeCuadroDos) > (tiempoSecuenciaSpritesDos*listaDeCuadrosDos->size()))
		numeroDeCuadroDos = 0;
	
	if (0 >= ((listaDeCuadrosDos->size() - 1) - (numeroDeCuadroDos / tiempoSecuenciaSpritesDos)))
		numeroDeCuadroDos = 0;

	//Renderizar el sprite
	SDL_Rect* cuadroActualDos;
	if (!invertido){
		cuadroActualDos = listaDeCuadrosDos->at((listaDeCuadrosDos->size()-1) - (numeroDeCuadroDos / tiempoSecuenciaSpritesDos));
	}
	else{
		cuadroActualDos = listaDeCuadrosDos->at(numeroDeCuadroDos / (tiempoSecuenciaSpritesDos));
	}
	numeroDeCuadroDos++; 
	
	personajeDos.w = (int)round(relacionAnchoDos*cuadroActualDos->w);
	personajeDos.h = (int)round(relacionAltoDos*cuadroActualDos->h);

	SDL_Rect proyectilUno;
	SDL_Rect proyectilDos;

	//Se cargan posiciones de los proyectiles
	if (!(invertido))
		proyectilUno.x = personajeUno.x + refMundo->getProyectil(1)->getPosicion().first;
	else
		proyectilUno.x = personajeUno.x + manejadorULog.darLongPixels(personajesVista.at(0)->getAncho()) - refMundo->getProyectil(1)->getPosicion().first - refMundo->getProyectil(1)->getAncho();
	proyectilUno.y = personajeUno.y + refMundo->getProyectil(1)->getPosicion().second;	
	// nacho: obtiene el sprite del disparo, tomo el ultimo de los sprites del disparo
	SDL_Rect* cuadroProyectilUnoSprite = personajesVista.at(0)->getSprite()->listaDeCuadros(DISPARO_DEFAULT)->back();
	// nacho: ancho y alto del dibujo del sprite
	proyectilUno.w = (int)refMundo->getProyectil(1)->getAncho();
	proyectilUno.h = (int)refMundo->getProyectil(1)->getAlto();

	if (!(invertido))
		proyectilDos.x = personajeDos.x + manejadorULog.darLongPixels(personajesVista.at(1)->getAncho()) - refMundo->getProyectil(2)->getPosicion().first - refMundo->getProyectil(2)->getAncho();
	else
		proyectilDos.x = personajeDos.x + refMundo->getProyectil(2)->getPosicion().first;
	proyectilDos.y = personajeDos.y + refMundo->getProyectil(2)->getPosicion().second;
	// nacho: obtiene el sprite del disparo, tomo el ultimo de los sprites del disparo
	SDL_Rect* cuadroProyectilDosSprite = personajesVista.at(1)->getSprite()->listaDeCuadros(DISPARO_DEFAULT)->back();
	proyectilDos.w = (int)refMundo->getProyectil(2)->getAncho(); 
	proyectilDos.h = (int)refMundo->getProyectil(2)->getAlto(); 
	
	float auxPj1 = (int)round(((relacionAnchoUno*cuadroActualUno->w) - manejadorULog.darLongPixels(personajesVista.at(0)->getAncho())));
	float auxPj2 = (int)round(((relacionAnchoDos*cuadroActualDos->w) - manejadorULog.darLongPixels(personajesVista.at(1)->getAncho())));

	SDL_Rect PersonajeUnoMovimiento = personajeUno;
	SDL_Rect PersonajeDosMovimiento = personajeDos;
	PersonajeUnoMovimiento.x = personajeUno.x - auxPj1;
	PersonajeDosMovimiento.x = personajeDos.x - auxPj2;

	//Se cargan ambos acorde a su posición relativa
	if (invertido){
		SDL_RenderCopyEx(renderer, texturaSpriteUno, cuadroActualUno, &personajeUno, 0, NULL, SDL_FLIP_HORIZONTAL);
		// nacho: dibuja el proyectil si está activado
		if (refMundo->getProyectil(1)->estaActivo())
			SDL_RenderCopyEx(renderer, texturaSpriteUno, cuadroProyectilUnoSprite, &proyectilUno, 0, NULL, SDL_FLIP_HORIZONTAL);
		
		SDL_RenderCopy(renderer, texturaSpriteDos, cuadroActualDos, &PersonajeDosMovimiento);
		// nacho: dibuja el proyectil si está activado
		if (refMundo->getProyectil(2)->estaActivo())
			SDL_RenderCopy(renderer, texturaSpriteDos, cuadroProyectilDosSprite, &proyectilDos);
	}
	else{
		SDL_RenderCopy(renderer, texturaSpriteUno, cuadroActualUno, &PersonajeUnoMovimiento);
		// nacho: dibuja el proyectil si está activado
		if (refMundo->getProyectil(1)->estaActivo())
			SDL_RenderCopy(renderer, texturaSpriteUno, cuadroProyectilUnoSprite, &proyectilUno);

		SDL_RenderCopyEx(renderer, texturaSpriteDos, cuadroActualDos, &personajeDos, 0, NULL, SDL_FLIP_HORIZONTAL);
		// nacho: dibuja el proyectil si está activado
		if (refMundo->getProyectil(2)->estaActivo())
			SDL_RenderCopyEx(renderer, texturaSpriteDos, cuadroProyectilDosSprite, &proyectilDos, 0, NULL, SDL_FLIP_HORIZONTAL);
	}

	// nacho: tamaño sensores
	proyectilUno.w = (int)refMundo->getProyectil(1)->getAncho();
	proyectilUno.h = (int)refMundo->getProyectil(1)->getAlto();

	proyectilDos.w = (int)refMundo->getProyectil(2)->getAncho(); 
	proyectilDos.h = (int)refMundo->getProyectil(2)->getAlto(); 

	if (MODO_DEBUG_SDL){
		SDL_Rect r;
		SDL_Rect r2;
		std::vector<Sensor*>* sensoresCuerpo1 = refMundo->getCuerpo(0)->getSensores();
		std::vector<Sensor*>* sensoresCuerpo2 = refMundo->getCuerpo(1)->getSensores();

		Uint8 Alfa = 128;
		SDL_SetRenderTarget(renderer, texturaVerde);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, Alfa);
		SDL_SetTextureAlphaMod(texturaVerde, Alfa);

		for (unsigned i = 0; i<sensoresCuerpo1->size(); i++){
			if (!(invertido)){
				r.x = sensoresCuerpo1->at(i)->getPosicion().first + personajeUno.x;
			}
			else{
				r.x = personajeUno.x + manejadorULog.darLongPixels(personajesVista.at(0)->getAncho()) - sensoresCuerpo1->at(i)->getPosicion().first - sensoresCuerpo1->at(i)->getAncho();
			}
			r.y = sensoresCuerpo1->at(i)->getPosicion().second + personajeUno.y;
			r.w = sensoresCuerpo1->at(i)->getAncho();
			r.h = sensoresCuerpo1->at(i)->getAlto();
			SDL_RenderCopy(renderer, texturaVerde, NULL, &r);
		}
		for (unsigned i = 0; i < sensoresCuerpo2->size(); i++){
			if (!(invertido)){
				r2.x = personajeDos.x + manejadorULog.darLongPixels(personajesVista.at(1)->getAncho()) - sensoresCuerpo2->at(i)->getPosicion().first - sensoresCuerpo2->at(i)->getAncho();
			}
			else{
				r2.x = sensoresCuerpo2->at(i)->getPosicion().first + personajeDos.x;
			}
			r2.y = sensoresCuerpo2->at(i)->getPosicion().second + personajeDos.y;
			r2.w = sensoresCuerpo2->at(i)->getAncho();
			r2.h = sensoresCuerpo2->at(i)->getAlto();
			SDL_RenderCopy(renderer, texturaVerde, NULL, &r2);
		}
		SDL_RenderCopy(renderer, texturaVerde, NULL, &proyectilUno);
		SDL_RenderCopy(renderer, texturaVerde, NULL, &proyectilDos);

		SDL_SetRenderTarget(renderer, NULL);
	}

	if (this->refMundo->getToasty() == true)
	{
		if (!timerToasty.isStarted())
		{
			this->timerToasty.start();
		}
		else
		{
			if (this->timerToasty.getTicks() <= 800)
			{
				this->dibujarEfectoToasty();
			}
			else
			{
				timerToasty.stop();
				this->refMundo->setToasty(false);//Seteo la variable como false otra vez
			}
		}
	}
}

void Vista::dibujarEfectoToasty()
{
	//Se produce cuando liu kang le da un gancho a scorpion
	
	Personaje * personaje1 = Parser::getInstancia().getPelea()->getPersonaje1();
	Personaje * personaje2 = Parser::getInstancia().getPelea()->getPersonaje2();

	//float uno = Parser::getInstancia().getVentana().getAncho();

	/*float posMediaPj1 = personaje1->getPosicionUn().first + personaje1->getAncho() / 2;//scorpion
	float posMediaPj2 = personaje2->getPosicionUn().first + personaje2->getAncho() / 2;//liu

	//Parámetro para ver si liu kang esta a izquierdo o derecho.
	bool invertido = (posMediaPj1 > posMediaPj2);*/
	bool salidaPorElLado;
	
	float lugarDeSalida = personaje1->getPosicionPx().first;
	
	if (lugarDeSalida > 1500 )

	{
		SDL_Rect camaraToasty2 = { 0, 450, 150, 150 };//75,74
		SDL_RenderCopyEx(renderer, this->texturaToasty2, NULL, &camaraToasty2, 0, NULL, SDL_FLIP_HORIZONTAL);
		//SDL_RenderPresent(renderer);
	
	}
	else 
	{
		SDL_Rect camaraToasty = { 680, 450, 150, 150 };
		SDL_RenderCopy(renderer, this->texturaToasty1, NULL, &camaraToasty);
		//SDL_RenderPresent(renderer);
	}
	
}

void Vista::controladorDeModoDeJuego()
{
	// coordenadas de "y": 2 jugadores 30, 1 jugador 230 ,training:430
	if (this->y == 30)
	{
		this->modoActual = TWOPLAYER;
	}
	else
	{
		if (this->y == 230)
		{
			this->modoActual = ONEPLAYER; 
		}
		else
		{
			if (this->y == 430)
			{
				this->modoActual = PRACTICA;
			}
		}
	}
}
Personaje* Vista::controladorDePersonajes()
{
	Personaje *player = new Personaje();
	// 1er fila liukang
	if (this->y == 20)
	{
		 player = this->jugador1;
	}
	else
	{    //2da fila scorpion
		if (this->y == 205)
		{
			 player = this->jugador2;
		}
		else
		{    //3era fila subzero
			if (this->y == 390)
			{
				 player = this->jugador2;
			}
		}
	}
	return player;

}
void Vista::setModoJuegoActual(modoJuego nuevoModo)
{
	this->modoActual = nuevoModo;
}

Vista:: modoJuego Vista::getModoJuegoActual()
{
	return this->modoActual;
}

void Vista::habilitarVibracion(){
	vibracion = true;
}


void Vista::deshabilitarVibracion(){
	vibracion = false;
}


Vista::~Vista()
{
	TTF_CloseFont(this->fuente);
	SDL_DestroyTexture(texturaSpriteUno);
	SDL_DestroyTexture(texturaSpriteDos);
	SDL_DestroyTexture(texturaVerde);
	SDL_DestroyTexture(texturaBarraDeVida);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(ventana);	
    
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

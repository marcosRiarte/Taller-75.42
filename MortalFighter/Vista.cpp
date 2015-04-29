#include "stdafx.h"
#include "Vista.h"
#include "Mundo.h"
#include "Log.h"

Vista::Vista(Mundo* unMundo)
{	
	// Se inicia SDL_image

	IMG_Init(IMG_INIT_PNG);
	ventana = SDL_CreateWindow(TITULO_VENTANA, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Parser::getInstancia().getVentana().getAnchoPx(), Parser::getInstancia().getVentana().getAltoPx(), SDL_WINDOW_SHOWN);
		if (ventana == nullptr){
			std::string mensaje = "SDL_CreateWindow Error: ";
			const char* elError = SDL_GetError();
			mensaje += elError;
			Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_ERROR);
			SDL_Quit();
			return;
		}

		std::string icono(ICONO);
		SDL_Surface* iconoSurf = IMG_Load(icono.c_str());
		SDL_SetWindowIcon(ventana, iconoSurf);

		renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
			if (renderer == nullptr){
				SDL_DestroyWindow(ventana);
				std::string mensaje = "SDL_CreateRenderer Error: ";
				const char* elError = SDL_GetError();
				mensaje += elError;
				Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_ERROR);
				SDL_Quit();
				return;
			}			

		for (size_t i = 0; i < Parser::getInstancia().getCapas().size(); i++) 
		{
			std::string imgFondo(Parser::getInstancia().getCapas().at(i)->getImagenFondo());

			SDL_Texture *tex = IMG_LoadTexture(renderer, imgFondo.c_str());

			if (tex == nullptr){				
				std::string mensaje = "SDL_CreateTextureFromSurface Error: ";
				const char* elError = SDL_GetError();
				mensaje += elError;
				Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_ERROR);
				return;
			}

			Parser::getInstancia().getCapas().at(i)->setTexturaSDL(tex);			
		}

		// inicializo la camara en el centro del escenario
		camaraXLog = -Parser::getInstancia().getEscenario().getAncho()/2
			+ Parser::getInstancia().getVentana().getAncho()/2;

		//Creo el número de cuadros en 0,
		numeroDeCuadroUno = 0;
		//y la lista de cuadros puntero a null
		listaDeCuadrosUno = nullptr;

		//Creo el número de cuadros en 0,
		numeroDeCuadroDos = 0;
		//y la lista de cuadros puntero a null
		listaDeCuadrosDos = nullptr;

		//Se cargan los sprites
		elSprite = new Sprite();
		
		//Dirección de la imagen de Sprites
		dirImgPersonaje = Parser::getInstancia().getPersonajes().at(0)->getSprite();

		//Carga la imagen desde la ruta especificada
		SuperficieUno = IMG_Load(dirImgPersonaje.c_str());
		SuperficieDos = IMG_Load(dirImgPersonaje.c_str());

		//Seteo del color
		//SDL_SetColorKey(Superficie, SDL_TRUE, SDL_MapRGB(Superficie->format, 0, 0xFF, 0xFF));


		//Creación de la textura sobre la superficie
		texturaSpriteUno = SDL_CreateTextureFromSurface(renderer, SuperficieUno);
		texturaSpriteDos = SDL_CreateTextureFromSurface(renderer, SuperficieDos);

		capasVista = Parser::getInstancia().getCapas();
		//Ordeno las capas por su zindex para ser dibujadas
		OrdenarCapas();

		refMundo = unMundo;
}


void Vista::actualizar(){

	// referencias más utilizadas al actualizar la vista
	std::vector<Personaje*> personajesVista = Parser::getInstancia().getPersonajes();
	Ventana ventanaVista = Parser::getInstancia().getVentana();	

	//Parametros de la ventana

	float anchoVentana = ventanaVista.getAncho();
	int altoVentanaPx = ventanaVista.getAltoPx();

	//Parametros del personaje	
	xPjUno = personajesVista[0]->getPosicionUn().first;
	float anchoPjUno = personajesVista[0]->getAncho();
	xPjDos = personajesVista[1]->getPosicionUn().first;
	float anchoPjDos = personajesVista[1]->getAncho();

	float anchoEscenario = Parser::getInstancia().getEscenario().getAncho();

	// Correcion al desplazamiento del personaje que no sobrepase el
	// escenario con su ancho.
	xPjUno *= anchoEscenario / (anchoEscenario + anchoPjUno +4);

	// Correcion al desplazamiento del personaje que no sobrepase el
	// escenario con su ancho.
	xPjDos *= anchoEscenario / (anchoEscenario + anchoPjDos + 4);

	//Se limpia la pantalla
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	// condicion de borde Personaje Uno
	bool PjUnoEstaEnBordeIzq = false;
	bool PjUnoEstaEnBordeDer = false;
	if (xPjUno + anchoPjUno > anchoVentana - camaraXLog)
		PjUnoEstaEnBordeDer = true;
	if (xPjUno < -camaraXLog)
		PjUnoEstaEnBordeIzq = true;
	bool PjUnoEstaEnBorde = PjUnoEstaEnBordeIzq || PjUnoEstaEnBordeDer;

	// condicion de borde Personaje Dos
	bool PjDosEstaEnBordeIzq = false;
	bool PjDosEstaEnBordeDer = false;
	if (xPjDos + anchoPjDos > anchoVentana - camaraXLog)
		PjDosEstaEnBordeDer = true;
	if (xPjDos < -camaraXLog)
		PjDosEstaEnBordeIzq = true;	
	bool PjDosEstaEnBorde = PjDosEstaEnBordeIzq || PjDosEstaEnBordeDer;

	MOV_TIPO mov1 = refMundo->getCuerpo(0)->getControlador()->getMovimientos().at(0);
	MOV_TIPO mov2 = refMundo->getCuerpo(1)->getControlador()->getMovimientos().at(0);

	if ((PjUnoEstaEnBordeIzq && PjDosEstaEnBordeDer) || (PjDosEstaEnBordeIzq && PjUnoEstaEnBordeDer)) {
		refMundo->FrenarCuerpos();

		if (PjUnoEstaEnBordeIzq && (mov1 == DER))
			refMundo->LiberarCuerpos();

		if (PjUnoEstaEnBordeDer && (mov1 == IZQ))
			refMundo->LiberarCuerpos();

		if (PjDosEstaEnBordeIzq && (mov2 == DER))
			refMundo->LiberarCuerpos();

		if (PjDosEstaEnBordeDer && (mov2 == IZQ))
			refMundo->LiberarCuerpos();
	}
	

	if (PjUnoEstaEnBorde && !PjDosEstaEnBorde) {
		camaraXLog += personajesVista[0]->getDeltaX();		
	}
	if (!PjUnoEstaEnBorde && PjDosEstaEnBorde) {
		camaraXLog += personajesVista[1]->getDeltaX();		
	}

	if (PjUnoEstaEnBordeIzq && PjDosEstaEnBordeIzq){ 
		if ((mov1 == IZQ) && (mov2 == IZQ))
			camaraXLog += personajesVista[0]->getDeltaX();
		else if (mov2 == IZQ)
			camaraXLog += personajesVista[1]->getDeltaX();
		else if (mov1 == IZQ)
			camaraXLog += personajesVista[0]->getDeltaX();
	}

	if (PjUnoEstaEnBordeDer && PjDosEstaEnBordeDer){
		if ((mov1 == DER) && (mov2 == DER))
			camaraXLog += personajesVista[0]->getDeltaX();
		else if (mov2 == DER)
			camaraXLog += personajesVista[1]->getDeltaX();
		else if (mov1 == DER)
			camaraXLog += personajesVista[0]->getDeltaX();
	}

	if (PjUnoEstaEnBordeDer && PjDosEstaEnBordeDer){
		if (mov1 == IZQ)
			camaraXLog += personajesVista[1]->getDeltaX();
	}

		//camaraXLog += personajesVista[0]->getDeltaX();

	if (!PjUnoEstaEnBorde && !PjDosEstaEnBorde)
		refMundo->LiberarCuerpos();
	
	// Dibuja las capas y el personaje
	Dibujar(personajesVista);


	//Se actualiza la pantalla
	SDL_RenderPresent(renderer);
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


std::string Vista::GetEstadoDelPersonaje(ESTADO estadoPersonaje, Personaje* personajeVista){
	std::string estadoDelPersonaje;

	if ((estadoPersonaje == ESTADO::IZQ_IZQ) || (estadoPersonaje == ESTADO::DER_DER)){
		if (("DER" == personajeVista->getOrientacion()))
			estadoDelPersonaje = personajeVista->getCaminarParaAdelante();
		else
			estadoDelPersonaje = personajeVista->getCaminarParaAtras();
	}

	if ((estadoPersonaje == ESTADO::DER_IZQ) || (estadoPersonaje == ESTADO::IZQ_DER)){
		if (("DER" == personajeVista->getOrientacion()))
			estadoDelPersonaje = personajeVista->getCaminarParaAtras();
		else
			estadoDelPersonaje = personajeVista->getCaminarParaAdelante();
	}

	if ((estadoPersonaje == ESTADO::SALTODER_DER) || (estadoPersonaje == ESTADO::SALTODER_IZQ) || (estadoPersonaje == ESTADO::SALTOIZQ_IZQ)){
		if (("DER" == personajeVista->getOrientacion()))
			estadoDelPersonaje = personajeVista->getSaltoDiagonal();
		else
			estadoDelPersonaje = "SaltoDiagonalIzq";
	}

	if (estadoPersonaje == ESTADO::SALTOIZQ_DER){
		if (("DER" == personajeVista->getOrientacion()))
			estadoDelPersonaje = "SaltoDiagonalIzq";
		else
			estadoDelPersonaje = personajeVista->getSaltoDiagonal();
	}

	if ((estadoPersonaje == ESTADO::ARRIBA_IZQ) || (estadoPersonaje == ESTADO::ARRIBA_DER)){
		estadoDelPersonaje = personajeVista->getSalto();
	}

	/*if ((estadoPersonaje == ESTADO::ABAJO_IZQ) || (estadoPersonaje == ESTADO::ABAJO_DER)){
	estadoDelPersonaje = personajeVista.getCaida();
	}*/
	if ((estadoPersonaje == ESTADO::QUIETODER) || (estadoPersonaje == ESTADO::QUIETOIZQ)) {
		estadoDelPersonaje = personajeVista->getQuieto();
	}

	return estadoDelPersonaje;
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
	float xLogPjDosEnCamara = xPjDos + camaraXLog;
	SDL_Rect personajeDos;

	SDL_Rect* cuadroBase = elSprite->listaDeCuadros("Quieto")->at(0);
	float relacionAnchoUno = (float)anchoPjUnoPx / (float)cuadroBase->w;
	float relacionAltoUno = (float)altoPjUnoPx / (float)cuadroBase->h;
	personajeUno.x = manejadorULog.darLongPixels(xLogPjUnoEnCamara);
	personajeUno.y = yPjUnoPx;	
	// ancho y alto lo calcula cuadro a cuadro
	std::string estadoDelPersonajeUno = GetEstadoDelPersonaje(personajesVista[0]->getEstado(), personajesVista[0]);

	float relacionAnchoDos = (float)anchoPjDosPx / (float)cuadroBase->w;
	float relacionAltoDos = (float)altoPjDosPx / (float)cuadroBase->h;
	personajeDos.x = manejadorULog.darLongPixels(xLogPjDosEnCamara);
	personajeDos.y = yPjDosPx;	
	std::string estadoDelPersonajeDos = GetEstadoDelPersonaje(personajesVista[1]->getEstado(), personajesVista[1]);

	//Se carga la lista de cuadros que corresponde acorde al estado del personaje.
	listaDeCuadrosUno = elSprite->listaDeCuadros(estadoDelPersonajeUno);
	numeroDeCuadroUno++;

	if ((4 * numeroDeCuadroUno / (listaDeCuadrosUno->size()))> (listaDeCuadrosUno->size() - 1))
		numeroDeCuadroUno = 0;



	//Renderizar el sprite
	SDL_Rect* cuadroActualUno;

	if (personajesVista.at(0)->getPosicionPx().first > personajesVista.at(1)->getPosicionPx().first){
		cuadroActualUno = listaDeCuadrosUno->at((listaDeCuadrosUno->size()-1)-(4 * numeroDeCuadroUno / (listaDeCuadrosUno->size())));
	}
	else{
		cuadroActualUno = listaDeCuadrosUno->at(4 * numeroDeCuadroUno / (listaDeCuadrosUno->size()));
	}

	personajeUno.w = (int)round(relacionAnchoUno*cuadroActualUno->w);
	personajeUno.h = (int)round(relacionAltoUno*cuadroActualUno->h);

	//Se carga la lista de cuadros que corresponde acorde al estado del personaje.
	listaDeCuadrosDos = elSprite->listaDeCuadros(estadoDelPersonajeDos);
	numeroDeCuadroDos++;

	if ((4 * numeroDeCuadroDos / (listaDeCuadrosDos->size()))> (listaDeCuadrosDos->size() - 1))
		numeroDeCuadroDos = 0;

	//Renderizar el sprite
	SDL_Rect* cuadroActualDos;

	if (personajesVista.at(1)->getPosicionPx().first > personajesVista.at(0)->getPosicionPx().first){
		cuadroActualDos = listaDeCuadrosDos->at((listaDeCuadrosDos->size() - 1) - (4 * numeroDeCuadroDos / (listaDeCuadrosDos->size())));
	}
	else{
		cuadroActualDos = listaDeCuadrosDos->at(4 * numeroDeCuadroDos / (listaDeCuadrosDos->size()));
	}

	personajeDos.w = (int)round(relacionAnchoDos*cuadroActualDos->w);
	personajeDos.h = (int)round(relacionAltoDos*cuadroActualDos->h);

	//Se cargan ambos acorde a su posición relativa
	if (personajesVista.at(0)->getPosicionPx().first > personajesVista.at(1)->getPosicionPx().first){
		SDL_RenderCopyEx(renderer, texturaSpriteUno, cuadroActualUno, &personajeUno, 0, NULL, SDL_FLIP_HORIZONTAL);
		SDL_RenderCopy(renderer, texturaSpriteDos, cuadroActualDos, &personajeDos);
	}
	else{
		SDL_RenderCopy(renderer, texturaSpriteUno, cuadroActualUno, &personajeUno);
		SDL_RenderCopyEx(renderer, texturaSpriteDos, cuadroActualDos, &personajeDos, 0, NULL, SDL_FLIP_HORIZONTAL);
	}
}


Vista::~Vista()
{	
	SDL_FreeSurface(SuperficieUno);
	SDL_FreeSurface(SuperficieDos);
	SDL_DestroyTexture(texturaSpriteUno);
	SDL_DestroyTexture(texturaSpriteDos);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(ventana);
	delete elSprite;

	IMG_Quit();
	SDL_Quit();
}

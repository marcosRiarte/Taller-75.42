#include "stdafx.h"
#include "Vista.h"
#include "Mundo.h"
#include "Log.h"

Vista::Vista()
{	
	// Se inicia SDL_image

	IMG_Init(IMG_INIT_PNG);
		ventana = SDL_CreateWindow("Mortal Fighter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Parser::getInstancia().getVentana().getAnchoPx(), Parser::getInstancia().getVentana().getAltoPx(), SDL_WINDOW_SHOWN);
		if (ventana == nullptr){
			std::string mensaje = "SDL_CreateWindow Error: ";
			const char* elError = SDL_GetError();
			mensaje += elError;
			Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_ERROR);
			SDL_Quit();
			return;
		}

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

		// inicializo la camara en cero
		camaraXLog = 0.0f;

		//Creo el número de cuadros en 0,
		numeroDeCuadro = 0;
		//y la lista de cuadros puntero a null
		listaDeCuadros = nullptr;

		//Se cargan los sprites
		elSprite = new Sprite();



		//Dirección de la imagen de Sprites
		dirImgPersonaje = Parser::getInstancia().getPersonaje().getSprite();

		//Carga la imagen desde la ruta especificada
		Superficie = IMG_Load(dirImgPersonaje.c_str());

		//Seteo del color
		SDL_SetColorKey(Superficie, SDL_TRUE, SDL_MapRGB(Superficie->format, 0, 0xFF, 0xFF));


		//Creación de la textura sobre la superficie
		texturaSprite = SDL_CreateTextureFromSurface(renderer, Superficie);

}


void Vista::actualizar(MOV_TIPO movimiento, ESTADO estadoPersonaje){

	// referencias más utilizadas al actualizar la vista
	Personaje personajeVista = Parser::getInstancia().getPersonaje();
	Ventana ventanaVista = Parser::getInstancia().getVentana();
	capasVista = Parser::getInstancia().getCapas();

	//Parametros de la ventana
	int anchoVentanaPx = ventanaVista.getAnchoPx();
	int altoVentanaPx = ventanaVista.getAltoPx();
	float anchoVentana = ventanaVista.getAncho();

	//Parametros del personaje
	int anchoPjPx = manejadorULog.darLongPixels(personajeVista.getAncho());
	int anchoPj = personajeVista.getAncho();
	int altoPjPx = manejadorULog.darLongPixels(personajeVista.getAlto());
	float xPjUn = personajeVista.getPosicionUn().first;
	int xPjPx = personajeVista.getPosicionPx().first;
	int yPjPx = personajeVista.getPosicionPx().second;

	SDL_Rect camara;
	camara = { 0, 0, anchoVentanaPx, altoVentanaPx };

	float anchoEscenario = Parser::getInstancia().getEscenario().getAncho();

	//Se limpia la pantalla
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	// condicion de borde
	if ((xPjUn + anchoPj > anchoVentana - camaraXLog) || (xPjUn < -camaraXLog))
		camaraXLog += personajeVista.getDeltaX();

	// Posicion x del personaje dentro de la camara
	float xLogPjEnCamara = xPjUn + camaraXLog;
	SDL_Rect personaje;

	personaje.x=manejadorULog.darLongPixels(xLogPjEnCamara);
	personaje.y = yPjPx;
	personaje.w = anchoPjPx;
	personaje.h = altoPjPx;
	
	//Se cargan las capas anteriores al personaje
	for (int i = 0; i <= personajeVista.getZIndex(); i++)
	{
		float anchoCapa = capasVista.at(i)->getAncho();
		camara.w = manejadorULog.darLongPixels(anchoCapa);
		// donde toma la camara a la capa parametrizado con el ancho del escenario	
		camara.x = manejadorULog.darLongPixels((camaraXLog)*(anchoCapa - anchoVentana) / anchoEscenario);
		
		SDL_RenderCopy(renderer, capasVista.at(i)->getTexturaSDL(), NULL, &camara);
	}
	
	//Se carga la lista de cuadros que corresponde acorde al estado del personaje.
	listaDeCuadros = elSprite->listaDeCuadros(estadoPersonaje);

	//Renderizar el sprite
	SDL_Rect* cuadroActual = listaDeCuadros->at(numeroDeCuadro / (2*listaDeCuadros->size()));

	//Se carga el personaje
	if ((estadoPersonaje == ESTADO::ABAJO_IZQ) || (estadoPersonaje == ESTADO::ARRIBA_IZQ) || (estadoPersonaje == ESTADO::DER_IZQ) || (estadoPersonaje == ESTADO::IZQ_IZQ) || (estadoPersonaje == ESTADO::QUIETOIZQ) || (estadoPersonaje == ESTADO::SALTODER_IZQ) || (estadoPersonaje == ESTADO::SALTOIZQ_IZQ)){
	SDL_RenderCopyEx(renderer, texturaSprite, cuadroActual, &personaje,0,NULL,SDL_FLIP_HORIZONTAL);
	}
	else{
		SDL_RenderCopy(renderer, texturaSprite, cuadroActual, &personaje);
	}
	
	//Se cargan las capas posteriores al personaje
	if ((personajeVista.getZIndex() + 1) < capasVista.size())
		for (int i = personajeVista.getZIndex() + 1; i < capasVista.size(); i++)
	{
		float anchoCapa = capasVista.at(i)->getAncho();
		camara.w = manejadorULog.darLongPixels(anchoCapa);
		// donde toma la camara a la capa parametrizado con el ancho del escenario
		camara.x = manejadorULog.darLongPixels((camaraXLog)*(anchoCapa - anchoVentana) / anchoEscenario);
		SDL_RenderCopy(renderer, capasVista.at(i)->getTexturaSDL(), NULL, &camara);
	}

	//Se actualiza la pantalla
	SDL_RenderPresent(renderer);

	if ((estadoPersonaje == ESTADO::QUIETODER) || (estadoPersonaje == ESTADO::QUIETOIZQ))
		numeroDeCuadro=0;

	if ((estadoPersonaje == ESTADO::DER_DER) || (estadoPersonaje == ESTADO::DER_IZQ) || (estadoPersonaje == ESTADO::IZQ_DER) || (estadoPersonaje == ESTADO::IZQ_IZQ)){
		/*
		//Siguiente cuadro
		++numeroDeCuadro;
		//Ciclado de la animación
		if (numeroDeCuadro / 24 >= 24) {
		*/
		numeroDeCuadro = 0;
		//}
	}
	if ((estadoPersonaje == ESTADO::ARRIBA_IZQ) || (estadoPersonaje == ESTADO::ARRIBA_DER) || (estadoPersonaje == ESTADO::SALTODER_DER) || (estadoPersonaje == ESTADO::SALTODER_IZQ) || (estadoPersonaje == ESTADO::SALTOIZQ_DER) || (estadoPersonaje == ESTADO::SALTOIZQ_IZQ)){
		/*//Siguiente cuadro
		++numeroDeCuadro;
		//Ciclado de la animación
		if (numeroDeCuadro / 6 >= 6) {
		*/
			numeroDeCuadro = 0;
		//}
	}

	if ((estadoPersonaje == ESTADO::ABAJO_IZQ) || (estadoPersonaje == ESTADO::ABAJO_DER))
		numeroDeCuadro = 0;

}

Vista::~Vista()
{	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(ventana);

	IMG_Quit();
	SDL_Quit();
}

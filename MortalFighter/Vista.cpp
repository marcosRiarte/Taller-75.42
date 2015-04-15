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
		//SDL_SetColorKey(Superficie, SDL_TRUE, SDL_MapRGB(Superficie->format, 0, 0xFF, 0xFF));


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
	float anchoPj = personajeVista.getAncho();
	int altoPjPx = manejadorULog.darLongPixels(personajeVista.getAlto());
	float xPjUn = personajeVista.getPosicionUn().first;	
	int xPjPx = personajeVista.getPosicionPx().first;
	int yPjPx = personajeVista.getPosicionPx().second;

	SDL_Rect camara;
	camara = { 0, 0, anchoVentanaPx, altoVentanaPx };

	float anchoEscenario = Parser::getInstancia().getEscenario().getAncho();
	// Correcion al desplazamiento del personaje que no sobrepase el
	// escenario con su ancho.
	xPjUn *= anchoEscenario / (anchoEscenario + anchoPj +4);

	//Se limpia la pantalla
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	// condicion de borde
	if ((xPjUn + anchoPj > anchoVentana - camaraXLog) || (xPjUn < -camaraXLog))
		camaraXLog += personajeVista.getDeltaX();		

	// Posicion x del personaje dentro de la camara
	float xLogPjEnCamara = xPjUn + camaraXLog;
	SDL_Rect personaje;

	personaje.x = manejadorULog.darLongPixels(xLogPjEnCamara);
	personaje.y = yPjPx;
	personaje.w = anchoPjPx;
	personaje.h = altoPjPx;

	//Se cargan las capas anteriores al personaje
	for (int i = 0; i < capasVista.size(); i++)
	{
		if (capasVista.at(i)->getZIndex() < personajeVista.getZIndex()) {
			float anchoCapa = capasVista.at(i)->getAncho();
			camara.w = manejadorULog.darLongPixels(anchoCapa);
			// donde toma la camara a la capa parametrizado con el ancho del escenario	
			camara.x = manejadorULog.darLongPixels((camaraXLog)*(anchoCapa - anchoVentana) / (anchoEscenario - anchoVentana));

			SDL_RenderCopy(renderer, capasVista.at(i)->getTexturaSDL(), NULL, &camara);
		}
	}

	std::string estadoDelPersonaje;
	if ((estadoPersonaje == ESTADO::IZQ_IZQ) || (estadoPersonaje == ESTADO::DER_DER)){
		estadoDelPersonaje = personajeVista.getCaminarParaAdelante();
	}
	if ((estadoPersonaje == ESTADO::DER_IZQ) || (estadoPersonaje == ESTADO::IZQ_DER)){
		estadoDelPersonaje = personajeVista.getCaminarParaAtras();
	}

	if ((estadoPersonaje == ESTADO::SALTODER_DER) || (estadoPersonaje == ESTADO::SALTODER_IZQ) || (estadoPersonaje == ESTADO::SALTOIZQ_DER) || (estadoPersonaje == ESTADO::SALTOIZQ_IZQ)){
		estadoDelPersonaje = personajeVista.getSaltoDiagonal();
	}
	if ((estadoPersonaje == ESTADO::ARRIBA_IZQ) || (estadoPersonaje == ESTADO::ARRIBA_DER)){
		estadoDelPersonaje = personajeVista.getSalto();
	}

	/*if ((estadoPersonaje == ESTADO::ABAJO_IZQ) || (estadoPersonaje == ESTADO::ABAJO_DER)){
		estadoDelPersonaje = personajeVista.getCaida();
	}*/
	if ((estadoPersonaje == ESTADO::QUIETODER) || (estadoPersonaje == ESTADO::QUIETOIZQ)) {
		estadoDelPersonaje = personajeVista.getQuieto();
	}

	//Se carga la lista de cuadros que corresponde acorde al estado del personaje.
	listaDeCuadros = elSprite->listaDeCuadros(estadoDelPersonaje);
	numeroDeCuadro++;

	if ((4 * numeroDeCuadro / (listaDeCuadros->size()))> (listaDeCuadros->size() - 1))
		numeroDeCuadro = 0;

	//Renderizar el sprite
		SDL_Rect* cuadroActual = listaDeCuadros->at(4*numeroDeCuadro / (listaDeCuadros->size()));
		

		//Se carga el personaje
		if (("IZQ" == Parser::getInstancia().getPersonaje().getOrientacion())){
		SDL_RenderCopyEx(renderer, texturaSprite, cuadroActual, &personaje, 0, NULL, SDL_FLIP_HORIZONTAL);
		}
		else{
		SDL_RenderCopy(renderer, texturaSprite, cuadroActual, &personaje);
		}

	//Se cargan las capas posteriores al personaje
		for (int i = 0; i < capasVista.size(); i++)
		{
			if (capasVista.at(i)->getZIndex() > personajeVista.getZIndex()) {
				float anchoCapa = capasVista.at(i)->getAncho();
				camara.w = manejadorULog.darLongPixels(anchoCapa);
				// donde toma la camara a la capa parametrizado con el ancho del escenario
				camara.x = manejadorULog.darLongPixels((camaraXLog)*(anchoCapa - anchoVentana) / (anchoEscenario - anchoVentana));
				SDL_RenderCopy(renderer, capasVista.at(i)->getTexturaSDL(), NULL, &camara);
			}
		}

	//Se actualiza la pantalla
	SDL_RenderPresent(renderer);


}

Vista::~Vista()
{	
	SDL_FreeSurface(Superficie);
	SDL_DestroyTexture(texturaSprite);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(ventana);
	delete elSprite;

	IMG_Quit();
	SDL_Quit();
}

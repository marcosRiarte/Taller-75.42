#include "stdafx.h"
#include "Vista.h"
#include "Mundo.h"

Vista::Vista()
{	
	// Se inicia SDL_image

	IMG_Init(IMG_INIT_PNG);
		ventana = SDL_CreateWindow("Mortal Fighter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Parser::getInstancia().getVentana().getAnchoPx(), Parser::getInstancia().getVentana().getAltoPx(), SDL_WINDOW_SHOWN);
		if (ventana == nullptr){
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return;
		}

		renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
			if (renderer == nullptr){
				SDL_DestroyWindow(ventana);
				std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
				SDL_Quit();
				return;
			}			

		for (size_t i = 0; i < Parser::getInstancia().getCapas().size(); i++) 
		{
			std::string imgFondo(Parser::getInstancia().getCapas().at(i)->getImagenFondo());

			SDL_Texture *tex = IMG_LoadTexture(renderer, imgFondo.c_str());

			if (tex == nullptr){				
				std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;					
				return;
			}

			Parser::getInstancia().getCapas().at(i)->setTexturaSDL(tex);			
		}

		// inicializo la camara en cero
		camaraXLog = 0.0f;
}


void Vista::actualizar(MOV_TIPO movimiento){

	// poner sprites...
	std::string dirImgPersonaje = Parser::getInstancia().getPersonaje().getSprites();
	SDL_Texture *imgPersonaje = IMG_LoadTexture(renderer, dirImgPersonaje.c_str());	

	// Parametros de la ventana
	int anchoVentanaPx = Parser::getInstancia().getVentana().getAnchoPx();
	int altoVentanaPx = Parser::getInstancia().getVentana().getAltoPx();
	float anchoVentana = Parser::getInstancia().getVentana().getAncho();

	// Parametros del personaje
	int anchoPjPx = manejadorULog.darLongPixels(Parser::getInstancia().getPersonaje().getAncho());
	int anchoPj = Parser::getInstancia().getPersonaje().getAncho();
	int altoPjPx = manejadorULog.darLongPixels(Parser::getInstancia().getPersonaje().getAlto());	
	float xPjUn = Parser::getInstancia().getPersonaje().getPosicionUn().first;
	int yPjPx = Parser::getInstancia().getPersonaje().getPosicionPx().second;

	SDL_Rect camara;
	camara = { 0, 0, anchoVentanaPx, altoVentanaPx };

	float anchoEscenario = Parser::getInstancia().getEscenario().getAncho();	
	
	//Se limpia la pantalla
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);	

	// condicion de borde
	if ((xPjUn + anchoPj > anchoVentana - camaraXLog) && (movimiento == DER || movimiento == QUIETO))
		camaraXLog -= anchoPj/2;
	if ((xPjUn < -camaraXLog) && movimiento == IZQ)
		camaraXLog += anchoPj/2;

	// Posicion x del personaje dentro de la camara
	float xLogPjEnCamara = xPjUn + camaraXLog;
	SDL_Rect personaje;
	personaje.x = manejadorULog.darLongPixels(xLogPjEnCamara);
	personaje.y = yPjPx;
	personaje.w = anchoPjPx;
	personaje.h = altoPjPx;
	
	//Se cargan las capas anteriores al personaje
	for (int i = 0; i <= Parser::getInstancia().getPersonaje().getZIndex(); i++)
	{
		float anchoCapa = Parser::getInstancia().getCapas().at(i)->getAncho();
		camara.w = manejadorULog.darLongPixels(anchoCapa);
		// donde toma la camara a la capa parametrizado con el ancho del escenario	
		camara.x = manejadorULog.darLongPixels((camaraXLog)*(anchoCapa - anchoVentana) / anchoEscenario);
		
		SDL_RenderCopy(renderer, Parser::getInstancia().getCapas().at(i)->getTexturaSDL(), NULL, &camara);
	}
	
	//Se carga el personaje
	SDL_RenderCopy(renderer, imgPersonaje, NULL, &personaje);


	//Se cargan las capas posteriores al personaje
	if ((Parser::getInstancia().getPersonaje().getZIndex() + 1) < Parser::getInstancia().getCapas().size())
		for (int i = Parser::getInstancia().getPersonaje().getZIndex() + 1; i < Parser::getInstancia().getCapas().size(); i++)
	{
		float anchoCapa = Parser::getInstancia().getCapas().at(i)->getAncho();
		camara.w = manejadorULog.darLongPixels(anchoCapa);
		// donde toma la camara a la capa parametrizado con el ancho del escenario
		camara.x = manejadorULog.darLongPixels((camaraXLog)*(anchoCapa - anchoVentana) / anchoEscenario);
		SDL_RenderCopy(renderer, Parser::getInstancia().getCapas().at(i)->getTexturaSDL(), NULL, &camara);
	}

	//Se actualiza la pantalla
	SDL_RenderPresent(renderer);
}

Vista::~Vista()
{	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(ventana);

	IMG_Quit();
	SDL_Quit();
}

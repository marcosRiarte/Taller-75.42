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

			
			anchoCapaMasLarga = 0;

		for (size_t i = 0; i < Parser::getInstancia().getCapas().size(); i++) 
		{
			std::string imgFondo(Parser::getInstancia().getCapas().at(i)->getImagenFondo());

			SDL_Texture *tex = IMG_LoadTexture(renderer, imgFondo.c_str());

			if (tex == nullptr){				
				std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;					
				return;
			}

			Parser::getInstancia().getCapas().at(i)->setTexturaSDL(tex);

			
			// busco máximo ancho de capa
			float anchoCapaActual = Parser::getInstancia().getCapas().at(i)->getAncho();
			if (anchoCapaActual > anchoCapaMasLarga)
				anchoCapaMasLarga = anchoCapaActual;

			//actualizar();		
			
		}

}


void Vista::actualizar(MOV_TIPO movimiento){

	//Revisar todo, poner sprites...
	std::string dirImgPersonaje = Parser::getInstancia().getPersonaje().getSprites();
	SDL_Texture *imgPersonaje = IMG_LoadTexture(renderer, dirImgPersonaje.c_str());

	SDL_Rect camara;

	//Parametros de la ventana
	int anchoVentanaPx = Parser::getInstancia().getVentana().getAnchoPx();
	int altoVentanaPx = Parser::getInstancia().getVentana().getAltoPx();

	int anchoPjPx = manejadorULog.darLongPixels(Parser::getInstancia().getPersonaje().getAncho());
	int altoPjPx = manejadorULog.darLongPixels(Parser::getInstancia().getPersonaje().getAlto());
	int xPjPx = Parser::getInstancia().getPersonaje().getPosicionPx().first;
	float xPjUn = Parser::getInstancia().getPersonaje().getPosicionUn().first;
	int yPjPx = Parser::getInstancia().getPersonaje().getPosicionPx().second;

	camara = { 0, 0, anchoVentanaPx, altoVentanaPx };

	int anchoEscenario = manejadorULog.darLongPixels(Parser::getInstancia().getEscenario().getAncho());
	int altoEscenario = manejadorULog.darLongPixels(Parser::getInstancia().getEscenario().getAlto());

	if (camara.x < 0) {
		camara.x = 0;
	}
	/*if (camara.y > 0) {
	camara.y = 0;
	}*/

	bool llegoAlBorde = false;
	if (xPjPx + anchoPjPx / 2 > anchoVentanaPx)
		llegoAlBorde = true;

	SDL_Rect personaje;
	personaje.x = xPjPx;
	personaje.y = yPjPx;
	personaje.w = anchoPjPx;
	personaje.h = altoPjPx;

	
	if (llegoAlBorde)
	{
		//if (movimiento == DER || movimiento == QUIETO)
		personaje.x = anchoVentanaPx - anchoPjPx;

		//if (movimiento == IZQ)
			//personaje.x = anchoVentanaPx - 2;
	}
	

	//Se limpia la pantalla
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	
	//Se cargan las capas anteriores al personaje
	for (int i = 0; i <= Parser::getInstancia().getPersonaje().getZIndex(); i++)
	{
		camara.w = manejadorULog.darLongPixels(Parser::getInstancia().getCapas().at(i)->getAncho());
		// Si el personaje está en el borde Desplazo capa dependiendo del ancho
		if (llegoAlBorde)
			camara.x = (anchoVentanaPx - xPjPx)*(camara.w / manejadorULog.darLongPixels(anchoCapaMasLarga));
		
		SDL_RenderCopy(renderer, Parser::getInstancia().getCapas().at(i)->getTexturaSDL(), NULL, &camara);
	}
	
	//Se carga el personaje
	SDL_RenderCopy(renderer, imgPersonaje, NULL, &personaje);


	//Se cargan las capas posteriores al personaje
	if ((Parser::getInstancia().getPersonaje().getZIndex() + 1) < Parser::getInstancia().getCapas().size())
		for (int i = Parser::getInstancia().getPersonaje().getZIndex() + 1; i < Parser::getInstancia().getCapas().size(); i++)
	{
		camara.w = manejadorULog.darLongPixels(Parser::getInstancia().getCapas().at(i)->getAncho());
		// Si el personaje está en el borde Desplazo capa dependiendo del ancho
		if (llegoAlBorde)
			camara.x = (anchoVentanaPx - xPjPx)*(camara.w / manejadorULog.darLongPixels(anchoCapaMasLarga));
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

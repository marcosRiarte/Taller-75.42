#include "stdafx.h"
#include "Vista.h"

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

			capasDeTextura.push_back(tex);

			actualizar();			
		}

}


void Vista::actualizar(){

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
	int yPjPx = Parser::getInstancia().getPersonaje().getPosicionPx().second;

	camara = { 0, 0, anchoPjPx, altoPjPx };

	int anchoEscenario = manejadorULog.darLongPixels(Parser::getInstancia().getEscenario().getAncho());
	int altoEscenario = manejadorULog.darLongPixels(Parser::getInstancia().getEscenario().getAlto());

	//Personaje Centrado
	camara.x = (xPjPx + (anchoPjPx / 2)) - anchoVentanaPx / 2;
	camara.y = (yPjPx + (altoPjPx / 2)) - altoVentanaPx / 2;

	//Mantener la camara en los limites
	if (camara.x < 0) {
		camara.x = 0;
	}
	if (camara.y < 0) {
		camara.y = 0;
	}
	if (camara.x > anchoEscenario - camara.w) {
		camara.x = anchoEscenario - camara.w;
	}
	if (camara.y > altoEscenario - camara.h) {
		camara.y = altoEscenario - camara.h;
	}

	SDL_Rect personaje;
	personaje.x = xPjPx - camara.x;
	personaje.y = yPjPx - camara.y;
	personaje.w = anchoPjPx;
	personaje.h = altoPjPx;

	//Se limpia la pantalla
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	
	//Se cargan las capas
	std::list<SDL_Texture*>::iterator it;
	for (it = capasDeTextura.begin(); it != capasDeTextura.end(); ++it)
	{
		SDL_RenderCopy(renderer, *it, &camara, NULL);
	}
	
	//Se carga el personaje
	SDL_RenderCopy(renderer, imgPersonaje, NULL, &personaje);

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

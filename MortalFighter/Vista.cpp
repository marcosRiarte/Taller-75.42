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
	SDL_RenderClear(renderer);

	std::list<SDL_Texture*>::iterator it;
	for (it = capasDeTextura.begin(); it != capasDeTextura.end(); ++it)
	{
		SDL_RenderCopy(renderer, *it, NULL, NULL);
	}

	//Revisar todo, poner sprites...
	std::string dirImgPersonaje = Parser::getInstancia().getPersonaje().getSprites();
	SDL_Texture *imgPersonaje = IMG_LoadTexture(renderer, dirImgPersonaje.c_str());
	
	SDL_Rect rect1;
	rect1.x = Parser::getInstancia().getPersonaje().getPosicionPx().first;
	rect1.y = Parser::getInstancia().getPersonaje().getPosicionPx().second;
	float anchoPersonaje = Parser::getInstancia().getPersonaje().getAncho();
	float altoPersonaje = Parser::getInstancia().getPersonaje().getAlto();
	rect1.w = manejadorULog.darLongPixels(anchoPersonaje);
	rect1.h = manejadorULog.darLongPixels(altoPersonaje);


	SDL_RenderCopy(renderer, imgPersonaje, NULL, &rect1);
	
	
	SDL_RenderPresent(renderer);

	SDL_RenderClear(renderer);
	
}

Vista::~Vista()
{	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(ventana);

	IMG_Quit();
	SDL_Quit();
}

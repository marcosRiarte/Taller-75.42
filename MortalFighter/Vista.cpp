#include "stdafx.h"
#include "Vista.h"


Vista::Vista()
{
	/*************************************************************/
	/* SDL ya tiene que estar inicializado						 */
	/*************************************************************/

	ventana = SDL_CreateWindow("Mortal Fighter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Parser::getInstancia().getVentana().getAnchoPx(), Parser::getInstancia().getVentana().getAltoPx(), SDL_WINDOW_SHOWN);
	if (ventana == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;

	renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if (renderer == nullptr){
		SDL_DestroyWindow(ventana);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}
	for (size_t i = 0; i < Parser::getInstancia().getCapas().size(); i++) {
		IMG_LoadTexture(renderer, Parser::getInstancia().getCapas[i].getImagenFondo());
	}
			
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return;
	}
	IMG_Init(IMG_INIT_PNG);
	}

	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_Delay(2000);

	//SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(ventana);

	IMG_Quit();
	SDL_Quit();

}


Vista::~Vista()
{
}

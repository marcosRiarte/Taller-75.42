// MortalFighter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{

	/*************************************************************/
	/* Parte jsoncpp											 */
	/*************************************************************/
	Json::Value raiz;
	Json::Reader reader(Json::Features::strictMode());

	std::string nombreArchivo("prueba.json");

	std::ifstream prueba(nombreArchivo, std::ifstream::binary);

	//chequea que exista el archivo y se pudo abrir
	if (!prueba.is_open())
		return 1;

	bool parseoExitoso = reader.parse(prueba, raiz, true);

	if (!parseoExitoso) {
		std::string mensaje = "Fallo el parseo, se carga json por defecto" + reader.getFormattedErrorMessages();
		const char * c = mensaje.c_str();
		std::ifstream prueba("pruebaDefecto.json", std::ifstream::binary);
		bool parseoExitoso = reader.parse(prueba, raiz, true);
	}

	Json::Value un_Escenario;
	un_Escenario = raiz["escenario"];
	std::string imagen_fondo(un_Escenario.get("imagen_fondo", "hello.bmp").asString());

	std::cout << imagen_fondo << std::endl;

	prueba.close();


	/*************************************************************/
	/* Parte SDL												 */
	/*************************************************************/

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	std::string imagePath = "hello.bmp";
	SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
	if (bmp == nullptr){
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr){
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, tex, NULL, NULL);
	SDL_RenderPresent(ren);

	SDL_Delay(2000);

	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	SDL_Quit();



	return 0;
}


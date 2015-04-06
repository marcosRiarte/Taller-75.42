#include "stdafx.h"
#include "Sprites.h"
#include "Controlador.h"

Sprites::Sprites(std::string spritesPersonaje)
{
	path = spritesPersonaje;
}
//TODO corregir
void Sprites:: determinarClips()
{
	int iW = 100, iH = 100;
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;

	//Setup the clips for our image
	SDL_Rect clips[4];
	for (int i = 0; i < 4; ++i){
		clips[i].x = i / 2 * iW;
		clips[i].y = i % 2 * iH;
		clips[i].w = iW;
		clips[i].h = iH;
}

int Sprites::seleccionarClips(MOV_TIPO movimiento)
{
	int useClip = 0;
		//Uso el dato del movimiento para determinar que clip dibujar
			switch (movimiento)
			{
			case QUIETO:
				useClip = 0;
				break;
			case DER:
				useClip = 1;
				break;
			case IZQ:
				useClip = 2;			
				break;
			case ARRIBA:
				useClip = 3;			
				break;
			case SALTOIZQ:
				useClip = 4;
				break;
			case SALTODER:
				useClip = 5;
				break;
			case CERRAR:
				quit = true;
				break;
			default:
				break;
			}
			return useClip;
		}
	
//TODO REVISAR 
void Sprites:: dibujarClip()
{
	SDL_RenderClear(renderer);
	renderTexture(image, renderer, x, y, &clips[useClip]);
	SDL_RenderPresent(renderer);
}
void Sprites ::setPath (std::string nuevoPath)
{
	path = nuevoPath;
}
std::string Sprites::getPath()
{
	return path;
}
Sprites::~Sprites()
{
}

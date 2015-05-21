#include "MatizColor.h"

MatizColor::MatizColor(SDL_Surface* superficieNueva)
{
	superficie = superficieNueva;
}


SDL_Surface* MatizColor::desplazarMatiz(double hInicial, double hFinal, double desplazamiento)
{	
	int ancho = superficie->w;
	int alto = superficie->h;
	Uint8 rojo, verde, azul, alfa;
	double croma = 0;
	int minRGBRef;
	Uint8* punteroPixel;


	if (SDL_MUSTLOCK(superficie))
		SDL_LockSurface(superficie);

	for (int x = 0; x < ancho; x++)
		for (int y = 0; y < alto; y++)
		{

			Uint32 pixelXY = obtenerPixel(x, y, &punteroPixel);

			// tomo los valores rojo, verde, azul, alfa
			SDL_GetRGBA(pixelXY, superficie->format, &rojo, &verde, &azul, &alfa);

			if (alfa > ALFA_MIN) {
				// calculo el matiz
				double hOriginal = obtenerMatiz(pixelXY, rojo, verde, azul, &croma, &minRGBRef);

				// cambiar el matiz, dependiendo de las condiciones iniciales y finales
				setMatizSelectivo(&pixelXY, desplazamiento, hOriginal, hInicial, hFinal, rojo, verde, azul, croma, &minRGBRef);
				*((Uint32*)punteroPixel) = pixelXY;
			}


		}

	if (SDL_MUSTLOCK(superficie))
		SDL_UnlockSurface(superficie);

	return superficie;

}

double MatizColor::obtenerMatiz(Uint32 pixel, Uint8 rojo, Uint8 verde, Uint8 azul, double* croma, int* minRGBRef)
{
	int maxRGB = maximo(rojo, verde, azul);
	int minRGB = minimo(rojo, verde, azul);
	*croma = (double)(maxRGB - minRGB);
	*minRGBRef = minRGB;

	if (*croma == 0) return -1;

	if (maxRGB == rojo)
		return 60.0f * (restoReal(((verde - azul) / *croma),  6));

	if (maxRGB == verde)
		return 60.0f * (((azul - rojo) / *croma) + 2);		

	if (maxRGB == azul)
		return 60.0f * (((rojo - verde) / *croma) + 4);

	
	return 0;
}

Uint32 MatizColor::obtenerPixel(int x, int y, Uint8** punteroPixel)
{
	int bpp = superficie->format->BytesPerPixel;	
	*punteroPixel = (Uint8 *)superficie->pixels + y * superficie->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return **punteroPixel;
		break;

	case 2:
		return *(Uint16 *)*punteroPixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return *punteroPixel[0] << 16 | *punteroPixel[1] << 8 | *punteroPixel[2];
		else
			return *punteroPixel[0] | *punteroPixel[1] << 8 | *punteroPixel[2] << 16;
		break;

	case 4:
		return *(Uint32 *)*punteroPixel;
		break;

	default:
		return 0;      
	}
}

void MatizColor::setMatizSelectivo(Uint32* pixel, double desplazamiento, double hOriginal, double hInicial, double hFinal, Uint8 rojo, Uint8 verde, Uint8 azul, double croma, int *minRGBRef)
{
	// salteo los casos fuera del rango dado
	if ((hOriginal < hInicial) || (hOriginal > hFinal))
		return;

	setMatiz(pixel, desplazamiento, hOriginal, rojo, verde, azul, croma, minRGBRef);
}


void MatizColor::setMatiz(Uint32* pixel, double desplazamiento, double hOriginal, Uint8 rojo, Uint8 verde, Uint8 azul, double croma, int *minRGBRef)
{
	double hDec = (restoReal(hOriginal + desplazamiento, 360)) / 60.0f;

	int intermedio = (int)round(croma * (1 - abs(restoReal(hDec, 2) - 1)));
	int cromaInt = (int)round(croma);

	if ((hOriginal == -1) || (hDec < 0)) return;

	if (hDec < 1)
	{
		*pixel = SDL_MapRGB(superficie->format, cromaInt + *minRGBRef, intermedio + *minRGBRef, *minRGBRef);
		return;
	}
	if (hDec < 2)
	{
		*pixel = SDL_MapRGB(superficie->format, intermedio + *minRGBRef, cromaInt + *minRGBRef, *minRGBRef);
		return;
	}
	if (hDec < 3)
	{
		*pixel = SDL_MapRGB(superficie->format, *minRGBRef, cromaInt + *minRGBRef, intermedio + *minRGBRef);
		return;
	}
	if (hDec < 4)
	{
		*pixel = SDL_MapRGB(superficie->format, *minRGBRef, intermedio + *minRGBRef, cromaInt + *minRGBRef);
		return;
	}
	if (hDec < 5)
	{
		*pixel = SDL_MapRGB(superficie->format, intermedio + *minRGBRef, *minRGBRef, cromaInt + *minRGBRef);
		return;
	}
	if (hDec < 6)
	{
		*pixel = SDL_MapRGB(superficie->format, cromaInt + *minRGBRef, *minRGBRef, intermedio + *minRGBRef);
		return;
	}

}
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
	double HObtenido = H_INDEF;

	if (*croma == 0) 
		return HObtenido;

	if (maxRGB == rojo)
		HObtenido = 60.0f * (restoReal(((verde - azul) / *croma), 6));

	else if (maxRGB == verde)
		HObtenido = 60.0f * (((azul - rojo) / *croma) + 2);

	else if (maxRGB == azul)
		HObtenido = 60.0f * (((rojo - verde) / *croma) + 4);

	if (HObtenido > 360)		
		HObtenido = restoReal(HObtenido, 360);
	else if (HObtenido < 0)
		//lo ubica dentro del rango[0, -360), negativo , y le suma 360 para que quede
		// en el rango [0, 360), positivo
		HObtenido = 360 + restoReal(HObtenido, 360);
	
	return HObtenido;
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
	if (hFinal < hInicial){
		if ((hOriginal < hInicial) && (hOriginal > hFinal))
			return;
	}
	else
		if ((hOriginal < hInicial) || (hOriginal > hFinal))
			return;

	setMatiz(pixel, desplazamiento, hOriginal, rojo, verde, azul, croma, minRGBRef);
}



void MatizColor::setMatiz(Uint32* pixel, double desplazamiento, double hOriginal, Uint8 rojo, Uint8 verde, Uint8 azul, double croma, int *minRGBRef)
{
	double hDec = (restoReal(hOriginal + desplazamiento, 360)) / 60.0f;

	int intermedio = (int)round(croma * (1 - abs(restoReal(hDec, 2) - 1)));
	int cromaInt = (int)round(croma);

	Uint8 color1 = Uint8(cromaInt + *minRGBRef);	
	Uint8 color2 = Uint8(intermedio + *minRGBRef);
	Uint8 color3 = Uint8(*minRGBRef);



	if ((hOriginal == H_INDEF) || (hDec < 0)) return;

	if (hDec < 1)
	{
		*pixel = SDL_MapRGB(superficie->format, color1, color2, color3);
		return;
	}
	if (hDec < 2)
	{
		*pixel = SDL_MapRGB(superficie->format, color2, color1, color3);
		return;
	}
	if (hDec < 3)
	{
		*pixel = SDL_MapRGB(superficie->format, color3, color1, color2);
		return;
	}
	if (hDec < 4)
	{
		*pixel = SDL_MapRGB(superficie->format, color3, color2, color1);
		return;
	}
	if (hDec < 5)
	{
		*pixel = SDL_MapRGB(superficie->format, color2, color3, color1);
		return;
	}
	if (hDec < 6)
	{
		*pixel = SDL_MapRGB(superficie->format, color1, color3, color2);
		return;
	}

}
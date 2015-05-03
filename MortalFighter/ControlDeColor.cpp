#include "stdafx.h"
#include "ControlDeColor.h"

//Pagina 133 de tutorial sdl
ControlDeColor::ControlDeColor(SDL_Surface* Superficie)
{
}

/*Sustituye el color del píxel (x, y) de la superficie surface por el color que recibe en el parámtro pixel*/
void ControlDeColor::PutPixel(SDL_Surface *superficie, int x, int y, Uint32 pixel)
{
	// Obtenemos la profundidad de color

	int bpp = superficie->format->BytesPerPixel;


	// Obtenemos la posición del píxel a sustituir

	Uint8 *p = (Uint8 *)superficie->pixels + y * superficie->pitch + x*bpp;


	// Según la profundidad de color

	switch (bpp) {
	case 1: // 8 bits (256 colores)
		*p = pixel;
		break;

	case 2: // 16 bits (65536 colores o HigColor)
		*(Uint16 *)p = pixel;
		break;

	case 3: // 24 bits (True Color)
		// Depende de la naturaleza del sistema (puede ser Big Endian o Little Endian)

		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {

			// Calculamos cada una de las componentes de color ,3 bytes, 3 posiciones					
			p[R] = (pixel >> 16) & 0xFF;
			p[G] = (pixel >> 8) & 0xFF;
			p[B] = pixel & 0xFF;

		}
		else {
			// Calculamos cada una de las componentes de color, 3 bytes, 3 posiciones

			p[R] = pixel & 0xFF;
			p[G] = (pixel >> 8) & 0xFF;
			p[B] = (pixel >> 16) & 0xFF;

		}
		break;

	case 4: // 32 bits (True Color + Alpha)

		*(Uint32 *)p = pixel;
		break;

	}
}


// devuelve el color del píxel de la posición (x, y) de la superficie
Uint32 ControlDeColor::GetPixel(SDL_Surface *superficie, int x, int y)
{
	// Obtenemos la profunidad de color
	int bpp = superficie->format->BytesPerPixel;
	// Obtenemos la posición del píxel a consultar

	Uint8 *p = (Uint8 *)superficie->pixels + \
		y * superficie->pitch + x * bpp;
	// Según sea la profundidad de color

	switch (bpp) {

	case 1: // 256 colores

		return *p;

	case 2: // 65536 colores

		return *(Uint16 *)p;

	case 3: // True Color

		// Según la naturaleza del sistema

		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)

			// OR entre los distintos componentes del color

			return p[R] << 16 | p[G] << 8 | p[B];

		else

			// OR entre los distintos componentes del color

			return p[R] | p[G] << 8 | p[B] << 16;

	case 4: // True Color + Alpha

		return *(Uint32 *)p;

	default:
		return 0;

	}

}
//Convierte la superficie de formato RGB a HSV , devuelve 0 si todo ok, sino devuelve -1
int ControlDeColor::HSVtoRGB()
{
	Uint8 *rojo = new Uint8();
	Uint8 *verde = new Uint8();
	Uint8 *azul = new Uint8();

	return 0;
}
//Convierte la superficie de formato HSV a RGB , devuelve el valor de H , si es invalido devuelve -1
//Rango de valore va de 0 a 255
double ControlDeColor::RGBtoHSV()
{
	double H = -1;
	const int MAX = 255;
	const int MIN = 0;

	if (MAX == MIN) {
		return H = -1;
	}
	else
		if ((R == MAX) && (G >= B))
		{
			H = 60 + ((G - B) / (MAX - MIN)) + 0;  //TRANSFORMAR A GRADOS
		}
	if ((R == MAX) && (G < B))
	{
		H = 60 + ((G - B) / (MAX - MIN)) + 360;
	}
	if (G == MAX){
		H = 60 + ((B - R) / (MAX - MIN)) + 120;
	}
	if (B == MAX){
		H = 60 + ((R - G) / (MAX - MIN)) + 240;
	}
	return H;

}
float  ControlDeColor::radianesAGrados(float anguloRad)
{
	float anguloGrad = (anguloRad / M_PI)*180.0;
	while (anguloGrad <= 0) {
		anguloGrad += 360;
	}
	while (anguloGrad > 360) {
		anguloGrad -= 360;
	}
	return anguloGrad;
}
float  ControlDeColor::gradosARadianes(float anguloGrad)
{
	return (anguloGrad / 180.0)*M_PI;
}

ControlDeColor::~ControlDeColor()
{
}

#pragma once

#define ALFA_MIN 50
#define H_INDEF 20000

class MatizColor {
public:
	MatizColor(SDL_Surface* superficieNueva);

	// devuelve la superficie con los colores entre matiz hInicial y hFinal desplazados segun
	// la cantidad desplazamiento
	SDL_Surface* desplazarMatiz(double hInicial, double hFinal, double desplazamiento);


private:
	SDL_Surface* superficie;

	Uint32 obtenerPixel(int x, int y, Uint8** punteroPixel);
	double obtenerMatiz(Uint32 pixel, Uint8 rojo, Uint8 verde, Uint8 azul, double* croma, int* minRGBRef);
	void setMatizSelectivo(Uint32* pixel, double desplazamiento, double hOriginal, double hInicial, double hFinal, Uint8 rojo, Uint8 verde, Uint8 azul, double croma, int *minRGBRef);	
	void setMatiz(Uint32* pixel, double desplazamiento, double hOriginal, Uint8 rojo, Uint8 verde, Uint8 azul, double croma, int *minRGBRef);

public:
	inline static int maximo(int x, int y, int z)
	{
		if ((x > y) && (x > z))
			return x;
		if ((y > x) && (y > z))
			return y;
		// sino
		return z;
	}

	inline static int minimo(int x, int y, int z)
	{
		if ((x < y) && (x < z))
			return x;
		if ((y < x) && (y < z))
			return y;
		// sino
		return z;
	}

	inline static double restoReal(double x, double y)
	{
		if (y == 0) return 0;

		return (x - y*trunc(x/y));
	}

};
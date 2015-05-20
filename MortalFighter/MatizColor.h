#pragma once

#define ALFA_MIN 50

class MatizColor {
public:
	MatizColor(SDL_Surface* superficieNueva);

	// devuelve la superficie con los colores entre matiz hInicial y hFinal desplazados segun
	// la cantidad desplazamiento
	SDL_Surface* desplazarMatiz(float hInicial, float hFinal, float desplazamiento);


private:
	SDL_Surface* superficie;

	Uint32 obtenerPixel(int x, int y, Uint8** punteroPixel);
	float obtenerMatiz(Uint32 pixel, Uint8 rojo, Uint8 verde, Uint8 azul, float* croma, int* minRGBRef);
	void setMatizSelectivo(Uint32* pixel, float desplazamiento, float hOriginal, float hInicial, float hFinal, Uint8 rojo, Uint8 verde, Uint8 azul, float croma, int *minRGBRef);
	void setMatiz(Uint32* pixel, float desplazamiento, float hOriginal, Uint8 rojo, Uint8 verde, Uint8 azul, float croma, int *minRGBRef);

	inline int maximo(int x, int y, int z)
	{
		if ((x > y) && (x > z))
			return x;
		if ((y > x) && (y > z))
			return y;
		// sino
		return z;
	}

	inline int minimo(int x, int y, int z)
	{
		if ((x < y) && (x < z))
			return x;
		if ((y < x) && (y < z))
			return y;
		// sino
		return z;
	}

	inline float restoReal(float x, float y)
	{
		if (y == 0) return 0;

		return (x - y*trunc(x/y));
	}

};
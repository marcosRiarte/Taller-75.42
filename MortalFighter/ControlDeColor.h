#pragma once
#include <Math.h>
enum colores { R, G, B };
class ControlDeColor
{
public:
	ControlDeColor(SDL_Surface*);
	SDL_Surface * getSuperficie();
	double reductorDeVueltas(double h);
	float radianesAGrados(float anguloRad);
	float gradosARadianes(float anguloGrad);
	int maximoEntreRGB(int, int, int);
	int minimoEntreRGB(int, int, int);
	void PutPixel(SDL_Surface *superficie, int x, int y, Uint32 pixel);
	Uint32 GetPixel(SDL_Surface *superficie, int x, int y);
	double RGBtoHSV(int, int, int, SDL_Surface *, int x, int y);
	double obtenerSaturacion(int, int, int); //Devuelve la componete S
	double obtenerBrillo(int red, int green, int blue); //Devuelve la componete V
	std::vector<int> HSVtoRGB(double H, int pixelX, int pixelY, double S, double V);
	Uint8 * getRojo();
	Uint8 * getVerde();
	Uint8 * getAzul();
	Uint8 * getAlpha();
	~ControlDeColor();

private:
	SDL_Surface *superficie;
	Uint8 *rojo = new Uint8();
	Uint8 *verde = new Uint8();
	Uint8 *azul = new Uint8();
	Uint8 *alpha = new Uint8();
};




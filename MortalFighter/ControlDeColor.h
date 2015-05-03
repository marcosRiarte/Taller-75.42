#pragma once
#include <Math.h>
enum colores { R, G, B };
class ControlDeColor
{
public:
	ControlDeColor(SDL_Surface*);
	float radianesAGrados(float anguloRad);
	float gradosARadianes(float anguloGrad);
	void PutPixel(SDL_Surface *superficie, int x, int y, Uint32 pixel);
	Uint32 GetPixel(SDL_Surface *superficie, int x, int y);
	double RGBtoHSV();
	int HSVtoRGB();
	~ControlDeColor();
};




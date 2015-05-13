#include "stdafx.h"
#include "ControlDeColor.h"
#include <Math.h>

ControlDeColor::ControlDeColor(SDL_Surface* superficie)
{
	this->superficie = superficie;
}

ControlDeColor::ControlDeColor()
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

// devuelve el color del píxel de la posición (x, y) de la superficie en un formato de BPF 32Bits s/s,
//si devuelve 0, el formato no es reconocido.
Uint32 ControlDeColor::GetPixel(SDL_Surface *superficie, int x, int y)
{
	// Obtenemos la profunidad de color
	int bpp = superficie->format->BytesPerPixel;
	// Obtenemos la posición del píxel a consultar
	//Uint32 colorPixel2= SDL_MapRGB
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
std::vector<int> ControlDeColor::HSVtoRGB(double H, double S, double V)
{

	std::vector<int> nuevoColor;
	int R, G, B, A;

	if (H > 360){
		std::cout << "Fallo la conversion de RGBA a HSV";
	}
	if (H == -1)
	{
		std::cout << "Fallo la conversion de la H";
	}
	double Hi = H / 60;
	double dos = 2;
	double c = V * S;
	double f = remainder(dos, Hi) - 1;  //(H / 60º) mod 2 - 1|
	double X = c * (1 - (abs(f)));  //Ver sie abs es el modulo
	double m = V - c;

	//Si es RGBA
	if ((Hi >= 0) && (Hi < 1))     //Remplazar por un case
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			A = (int)*(this->alpha);  //A
			R = c + m;                //R
			G = X + m;          //G
			B = m;                  //B
		}
		else{

			B = m;                      //B
			G = (int)X + m;             //G 
			R = (int)c + m;             //R
			A = (int)*(this->alpha); //A
		}
	}
	if ((Hi >= 1) && (Hi < 2))
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{

			A = (int)*(this->alpha);     //A
			R = (int)X + m;              //R
			G = (int)c + m;             //G
			B = m;                     //B
		}
		else
		{
			B = m;                  //B
			G = (int)c + m;         //G
			R = (int)X + m;         //R
			A = (int)*(this->alpha); //A
		}
	}

	if ((Hi >= 2) && (Hi < 3))
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			A = (int)*(this->alpha); //A
			R = m;             //R
			G = c + m;             //G
			B = (int)X + m;        //B
		}
		else
		{
			B = (int)X + m;       //B
			G = (int)c + m;        //G        
			R = m;              //R     
			A = (int)*(this->alpha); //A          
		}
	}

	if ((Hi >= 3) && (Hi < 4))
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			A = (int)*(this->alpha);
			R = m;
			G = (int)X + m;
			B = (int)c + m;
		}
		else
		{
			B = (int)c + m;
			G = (int)X + m;
			R = m;
			A = (int)*(this->alpha);
		}
	}

	if ((Hi >= 4) && (Hi < 5))
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			A = (int)*(this->alpha);
			R = (int)X + m;
			G = m;
			B = (int)c + m;
		}
		else
		{
			B = (int)c + m;
			G = m;
			R = (int)X + m;
			A = (int)*(this->alpha);
		}
	}

	if ((Hi >= 5) && (Hi < 6))
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			A = (int)*(this->alpha);
			R = (int)c + m;
			G = m;
			B = (int)X + m;
		}
		else
		{
			B = (int)X + m;
			G = m;
			R = (int)c + m;
			A = (int)*(this->alpha);
		}
	}
	
	nuevoColor.push_back(R);
	nuevoColor.push_back(G);
	nuevoColor.push_back(B);
	nuevoColor.push_back(A);
	return nuevoColor;
}

//Convierte la superficie de formato RGB a HSV , devuelve el valor de H transformada , si es invalido devuelve -1
//Rango de valore va de 0 a 255
double ControlDeColor::RGBtoHSV(int h_inicio, int h_final, int desplazamiento, SDL_Surface *superficie, int x, int y)
{
	double H = -1;
	double Hi = -1;


	//Lee un pixel ,calcula H y si H esta en el rango valido le aplica la tranSformacion.

	Uint32 colorPixel = ControlDeColor::GetPixel(superficie, x, y);//Color encriptado en 4 bytes de un pixel

	//Levanto en cada puntero(rojo,verde ,azul,alpha) el valor en 8 bits de cada uno
	SDL_GetRGBA(colorPixel, superficie->format, this->rojo, this->verde, this->azul, this->alpha);

	int red = (int)*(this->rojo); //Casteo el valor como un entero debe estar entre 255 y 0 
	int green = (int)*(this->verde);
	int blue = (int)*(this->azul);

	//Calculo el maximo entre los 3 compoentes del color
	int M = ControlDeColor::maximoEntreRGB(red, green, blue);
	int m = ControlDeColor::minimoEntreRGB(red, green, blue);
	int c = M - m;
	double seis = 6;

	//Si la diferencia c es 0 entonces H no esta definido
	if (c == 0)
	{
		H = 0;
	}
	else{
		double resta = green - blue;
		Hi = resta / c;

		if (M == red)
		{
			H = 60 * (remainder(Hi, seis));
		}
		if (M == green)
		{
			H = 60 * (((blue - red) / c) + 2);
		}
		if (M == blue)
		{
			H = 60 * (((red - green) / c) + 4);
		}
	}//Fin del else

	if ((H >= h_inicio) && (H <= h_final))
	{
		H = H + desplazamiento;
	}
	else
	{
		H = -1;
	}
	//Corrijo si el resultado es mayor a 360 grados
	H = this->reductorDeVueltas(H);
	return H;
}

double ControlDeColor::reductorDeVueltas(double h)
{
	double H = h;
	if (h > 360)
	{
		H = ((h / 360) - trunc(h / 360)) * 360;   //Ver si es el TRUNC QUE NESCESITO->( DIVISON - PARTE ENTERA) = PARTE DECIMAL
	}

	return H;
}

//Devuelve la componete S de HSV
double ControlDeColor::obtenerSaturacion(int red, int green, int blue)
{
	double S = -1;
	double maximo = this->maximoEntreRGB(red, green, blue);
	double minimo = this->minimoEntreRGB(red, green, blue);

	double resta = maximo - minimo;

	if (maximo == 0)
	{
		S = 0;
	}
	else
	{

		S = resta / maximo;
	}
	return S;
}

//Devuelve la componete V de HSV
double ControlDeColor::obtenerBrillo(int red, int green, int blue)
{
	double V = this->maximoEntreRGB(red, green, blue);

	return V;
}

int ControlDeColor::maximoEntreRGB(int red, int green, int blue)
{
	int max = -1;

	if ((red >= green) && (red >= blue))
	{
		max = red;
	}
	if ((green >= red) && (green >= blue))
	{
		max = green;
	}

	if ((blue >= red) && (blue >= green))
	{
		max = blue;
	}
	return max;
}
int ControlDeColor::minimoEntreRGB(int red, int blue, int green)
{
	int min = -1;

	if ((red <= green) && (red <= blue))
	{
		min = red;
	}
	if ((green <= red) && (green <= blue))
	{
		min = green;
	}

	if ((blue <= red) && (blue <= green))
	{
		min = blue;
	}
	return min;
}
Uint8* ControlDeColor::getRojo()
{
	return this->rojo;
}

Uint8* ControlDeColor::getVerde()
{
	return this->verde;
}

Uint8* ControlDeColor::getAzul()
{
	return this->azul;
}

Uint8* ControlDeColor::getAlpha()
{
	return this->alpha;
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

SDL_Surface* ControlDeColor::getSuperficie()
{
	return this->superficie;
}

ControlDeColor::~ControlDeColor()
{
	//Borra los punteros de los colores
	delete rojo;
	delete verde;
	delete azul;
	delete alpha;
}




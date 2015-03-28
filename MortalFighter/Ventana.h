#pragma once
class Ventana
{
public:
	Ventana(int unAnchoPx, int unAltoPx, float unAncho);
	~Ventana();
private:
	int anchoPx, altoPx;
	float ancho;
};


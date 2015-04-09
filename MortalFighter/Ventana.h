#pragma once
class Ventana
{
public:
	Ventana(int unAnchoPx, int unAltoPx, float unAncho);
	int getAnchoPx() const;
	int getAltoPx() const;
	float getAncho() const;

	~Ventana();
private:
	int anchoPx, altoPx;
	float ancho;
};


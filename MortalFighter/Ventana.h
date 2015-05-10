#pragma once
class Ventana
{
public:
	Ventana(int unAnchoPx, int unAltoPx, float unAncho);
	int getAnchoPx() const;
	int getAltoPx() const;
	float getAncho() const;
	void setAnchoPx(int unAnchoPx);
	void setAltoPx(int unAltoPx);
	void setAncho(float unAncho);

	~Ventana();
private:
	int anchoPx, altoPx;
	float ancho;
};


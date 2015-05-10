#pragma once

class Escenario
{
public:
	Escenario(float anchoEscenario, float altoEscenario, float yPisoEscenario);
	float getAncho() const;
	float getAlto() const;
	float getYPiso() const;
	void setAncho(float unAncho);
	void setAlto(float unAlto);
	void setYPiso(float unyPiso);

	~Escenario();
private:
	float ancho, alto, yPiso;
};


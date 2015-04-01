#pragma once

class Escenario
{
public:
	Escenario(float anchoEscenario, float altoEscenario, float yPisoEscenario);
	float getAncho() const;
	float getAlto() const;
	float getYPiso() const;

	~Escenario();
private:
	float ancho, alto, yPiso;
};


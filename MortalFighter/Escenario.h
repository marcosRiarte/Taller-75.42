#pragma once
class Escenario
{
public:
	Escenario(float anchoEscenario, float altoEscenario, float yPisoEscenario);
	float getAncho() const;
	~Escenario();
private:
	float ancho, alto, yPiso;
};


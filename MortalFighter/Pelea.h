#pragma once
class Pelea
{
public:
	Pelea();
	void setPersonaje1(Personaje* unPersonaje);
	void setPersonaje2(Personaje* unPersonaje);
	Personaje* getPersonaje1();
	Personaje* getPersonaje2();
	~Pelea();

private:
	Personaje* personaje1;
	Personaje* personaje2;
};

